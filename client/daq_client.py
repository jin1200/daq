#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import argparse
import socket
import sys

from csv_reader import csv_reader


class DAQ_Client():
    def __init__(self, ip, port):
        self.ip = ip
        self.port = port

    def connect(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((self.ip, self.port))

    def disconnect(self):
        self.sock.detach()

    def set_ip_port(self, ip, port):
        self.ip = ip
        self.port = port

    def send(self, msg):
        self.connect()
        self.sock.sendall(msg.encode())

    def response(self):
        response = self.sock.recv(4096)
        self.disconnect()
        return response.decode()

    def data(self):
        self.send("DATA\r\n")
        req = self.response()
        config = self.parse_data(req)
        return config

    def print_config(self, config):
        for channel in config:
            print('Channel: {}, Name: {},  Wert: {} {}'.format(
                channel[0], channel[1], channel[2], channel[3]))

    def parse_data(self, data):
        channels = []
        data = data.replace('"', '')
        tmp = data.split("\r\n")
        for channel in tmp:
            channels.append(channel.split(';'))
        tmp = []
        channels = channels[:4]
        for channel in channels:
            if ('null' not in channel):
                channel[0] = int(channel[0])
                channel[1] = str(channel[1])
                channel.append(str(channel[2][channel[2].find(' ') + 1:]))
                channel[2] = float(channel[2][:channel[2].find(' ') - 1])
            if ('null' in channel):
                channel.append('null')
        return channels

    def daq_configure_channel(self, channel_id, friendly_name, unit, lut, m,
                              b):
        msg = "KONFIG\r\n{};\"{}\";\"{}\";{};{};{}\r\n".format(
            channel_id, friendly_name, unit, lut, m, b)
        self.send(msg)
        req = self.response()
        if 'OK' in req:
            return 'Config übernommen'
        return 'Config fail'

    def daq_configure_lut(self, filename):
        reader = csv_reader()
        csv = reader.read_file(filename)
        lut_id = reader.get_values(
            reader.get_colIndexByName('lut_id', csv), csv)
        index = reader.get_values(reader.get_colIndexByName('index', csv), csv)
        adc_value = reader.get_values(
            reader.get_colIndexByName('adc_value', csv), csv)
        y_value = reader.get_values(
            reader.get_colIndexByName('y_value', csv), csv)
        msg = 'LUT\r\n'
        for i in range(0, len(index)):
            msg += "{};{};{};{}\r\n".format(lut_id[0], index[i], adc_value[i],
                                            y_value[i])
            if (sys.getsizeof(msg) > 1280):
                self.send(msg)
                req = self.response()
                if 'OK' not in response:
                    break
                msg = 'LUT\r\n'
        print(msg)
        self.send(msg)
        req = self.response()
        if 'OK' in req:
            return 'LUT OK'
        return 'LUT failed'


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    group = parser.add_mutually_exclusive_group()
    group.add_argument(
        '-r',
        '--read',
        action='store_true',
        help='requests data telegram from server')
    group.add_argument(
        '-w', '--write', action='store_true', help='loads config to server')
    group.add_argument(
        '-l', '--lut', action='store_true', help='loads config to server')

    ip_config = parser.add_argument_group()
    ip_config.add_argument(
        'ip', action='store', type=str, help='Server IPv4 Addr')
    ip_config.add_argument(
        'port', action='store', type=int, help='Server Port Addr')

    config = parser.add_argument_group()
    config.add_argument(
        '-ch', '--channel', action='store', help='Channel to Configure. 0-3')
    config.add_argument(
        '-n', '--name', action='store', help='Channel Name. String <17')
    config.add_argument(
        '-u', '--unit', action='store', help='LUT 1, LINEAR 0 ')
    config.add_argument(
        '-t', '--type0', action='store', help='LUT 1, LINEAR 0 ')

    parser.add_argument(
        '-m',
        '--steigung',
        action='store',
        type=float,
        help='m for linear calc')
    parser.add_argument(
        '-b', '--yWert', action='store', type=float, help='b for linear calc')
    parser.add_argument(
        '-f', '--file0', type=str, help='.csv file with calculated lut')

    args = parser.parse_args()
    server_ip = args.ip
    server_port = args.port

    daq_client = DAQ_Client(server_ip, server_port)

    if (args.write):
        response = daq_client.daq_configure_channel(args.channel, args.name, args.unit, args.type0, args.steigung, args.yWert)
        print(response)

    if (args.lut):
        response = daq_client.daq_configure_lut(args.file0)
        print(response)

    if (args.read):
        config = daq_client.data()
        daq_client.print_config(config)
