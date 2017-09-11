import csv
import os
import sys
class csv_reader():
    
    def read_file(self, csv_file):
        cwd = os.path.abspath(os.getcwd())
        csv_file = os.path.join(cwd, csv_file)
        csv.Dialect=csv.excel
        try:
            csv_file = csv.reader(open(csv_file,'rU'), delimiter= ';')
        except IOError as e:
            print('Error:', e)
        self.Liste = list(csv_file)
        return self.Liste
        
    def get_colIndexByName(self, name, liste, row = 0):
        '''returns index of the first found column name'''
        #index = [i for i, text in enumerate(liste) if name in text]
        #print(liste)
        index = liste[row].index(name)
        return index
    def get_values(self, index, liste):
        tmp = []
        for i in range(0, len(liste)):
            try:
                tmp.append(float(liste[i][index]))
            except:
                print('Can not convert "', liste[i][index], '" to float. Not adding to list.')
        return tmp