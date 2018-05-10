#!/usr/bin/env python
# MLSA Multilingual Software Analysis
# This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
# pyViaJs.py takes in the csv generated from jsFunCall.py. The program checks through the csv file to determine if a Python program has been called from the JavaScript program (through JQuery's ajax function). If so, the Python file name is found and replaces the API ($.ajax()) in the csv file
# Author: Anne Marie Bogar
# Date: June 7, 2017
# this code can be copied or used and is without warrenty or support, but this header needs to be copied along with the program FU2017
# Input: csv file
#		call_id(int),class(string),scope(string),function_name(string),argument1(string),argument2(string)...
# Output: csv file
#		call_id(int),class(string),scope(string),function_name(string),argument1(string),argument2(string)...
# for arguments, all literals are encased in <> (ex: <5>) and all variables have their line number attached (ex: var-6)
# function calls that are arguments of another function call have their id next to () in csv line of the other function call
#               ex: 6,GLOBAL,file.py,function1,function2()4

import sys
import csv

#global variables
error = "MLSA: pyViaJs.py; " #beginning of error statement for all error messages in the program
LAST_ELEMENT = -1
CSV_FUNCTION = 3
PY_SUFFIX = -4
JS_SUFFIX = -3
FIRST_ELEMENT = 0
VAR = 1

#---------------------------Updater Class------------------------------#
class Updater:
    def __init__(self, f, jsfile):
        #rda has not yet been added for JavaScript files
        self.path = ''
        if '/' in jsfile:
            j = jsfile.split('/')
            self.path = '/'.join(j[:-1])+'/'
        self.calls = []
        self.calls = []
        reader = csv.reader(f)
        #analyze each line in the csv file
        for row in reader:
            self.searchCsv(row)

    #writes updated version of csv to the new csv file
    def updateCsv(self, f):
        writer = csv.writer(f)
        writer.writerows(self.calls)

    #searches through the csv to find any APIs that call Python programs
    def searchCsv(self, row):
        pyfile = []
        #this code is meant specifically for $.ajax() - more if-statements can be added for additional APIs 
        #row[3] is where the function name of the call is found in the csv file
        if len(row) > CSV_FUNCTION:
            if 'OBJ.ajax' in row[CSV_FUNCTION]:
                pyfile = self.findPY(row)
        else:
            sys.exit(error+"Incorrect syntax in csv file")
        #if the python file name is found, the python file will replace the API function name in the csv file
        #ex: 0,class,scope,OBJ.ajax,{type-6:<POST>|url-7:<~/file.py>|data-8:{param-8:<text>}|dataType-9:<text>}
        #    0,class,scope,file.py
        if pyfile:
            #takes first 3 columns of the csv file (id,class,scope)
            newRow = row[:CSV_FUNCTION]
            for p in pyfile:
                #adds line to csv file with first 3 rows and the Python file name at the end
                self.calls.append(list(newRow)) #list() creates a copy of newRow
                if '/' not in p:
                    p = self.path+p
                self.calls[LAST_ELEMENT].append(p)
        #if pyfile list is empty, API was not found
        #add the original row to the new csv file
        else:
            self.calls.append(row)

    #this function is written specifically for JQuery's ajax function due to how it disects the argument
    #similar functions can be written for other APIs that are specific to the arguments for those APIs
    def findPY(self, line):
        #pyfile can only have one value for now, but when rda is added, there could be more potential values
        pyfile = []
        for l in line:
            #in $.ajax(), the Python file name is found by the keyword url (ajax has a dictionary argument)
            if 'url-' in l:
                #dictionary elements are separated by | in the csv file
                d = l.split('|')
                for e in d:
                    if 'url-' in e:
                        #dictionary element syntax - key:value
                        #url is the key, the Python file name is the value
                        f = e.split(':')
                        #value must be a string (inside <>) and must end with .py for it to be a Python file
                        if '<' in f[VAR][FIRST_ELEMENT] and '>' in f[VAR][LAST_ELEMENT] and '.py' in f[VAR][PY_SUFFIX:]:
                            f[VAR] = f[VAR][1:LAST_ELEMENT] #remove <>
                            g = f[VAR].split('/') #remove all / (because url has /)
                            pyfile = [g[LAST_ELEMENT]] #file name is found after the last /
                        #if the value of url is not a Python file or not a string (could be a variable), send error message
                        else:
                            pyfile = ["ERROR_Python_File_Cannot_Be_Discerned"]
                            print error+"Python file called cannot be determined"
        return pyfile
#------------------------------------------------------------------------#


def main(inputCsv, jsfile, outputCsv):
    global error

    #check if csv file contains content from a JavaScript program
    if '.js' not in jsfile[JS_SUFFIX:]:
        sys.exit(error+"csv file not a JavaScript call graph")

    #read from input csv file and update csv if APIs found
    try:
        with open(inputCsv, 'r') as csvfile:
            updater = Updater(csvfile, jsfile);
    except IOError:
        sys.exit(error+inputCsv+" does not exist")

    #write updated csv to new csv file
    try:
        with open(outputCsv, 'w') as newcsv:
            updater.updateCsv(newcsv)
    except IOError:
        sys.exit(error+"problem writing new csv file")
