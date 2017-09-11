#!/usr/bin/env python3
# -*- coding: utf-8 -*-
from PyQt5 import QtGui, QtCore, QtWidgets, uic
import sys
from daq_client import DAQ_Client
from daq import Ui_daq_client

#values = daq_client.get_daq_value('192.168.178.10', 8892)
#print(values)
#def main():

class daq_gui(QtWidgets.QMainWindow):
    def __init__(self):
        QtWidgets.QDialog.__init__(self)
        self.ui = uic.loadUi("daq.ui", self)

        #Slots
        self.ui.bt_get_data.clicked.connect(self.getdata)
        self.ui.bt_exit.clicked.connect(self.exit)


    def getdata(self):
        ip = "192.168.178.10"
        port = 8892
        ip_port = self.ui.set_ip.text()
        #ip = (str(ip_port))[:find(":")]
        #port = (str(ip_port))[find(":"):]
        #print(ip, port)
        client = DAQ_Client(ip, port)
        client.connect()
        data = client.data()

        self.txt_name0.setText(data[0][1])
        self.data0.display(data[0][2])
        self.txt_unit0.setText(data[0][3])

        self.txt_name1.setText(data[1][1])
        self.data1.display(data[1][2])
        self.txt_unit1.setText(data[1][3])

        self.txt_name2.setText(data[2][1])
        self.data2.display(data[2][2])
        self.txt_unit2.setText(data[2][3])

        self.txt_name3.setText(data[3][1])
        self.data3.display(data[3][2])
        self.txt_unit3.setText(data[3][3])
        client.disconnect()

    def exit(self):
        self.close()

if __name__ == '__main__':

    app = QtWidgets.QApplication(sys.argv)
    daq_gui = daq_gui()
    daq_gui.show()
    sys.exit(app.exec_())
