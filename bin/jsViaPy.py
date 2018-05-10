#!/usr/bin/env python
# MLSA Multilingual Software Analysis
# This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
# jsViaPy.py takes in the csv generated from pyFunCall.py. The program checks through the csv file to determine if a JavaScript program has been called from the Python program (through PyV8's eval function). If so, the Python file name is found and replaces the API (PyV8's eval()) in the csv file
# Author: Anne Marie Bogar
# Date: July 10, 2017
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
error = "MLSA: jsViaPy.py; " #beginning of error statement for all error messages in the program
LAST_ELEMENT = -1
CSV_ARGUMENTS = 4
CSV_FUNCTION = 3
CSV_CALL_ID = 0
JS_SUFFIX = -4
PY_SUFFIX = -3

class Updater:
    def __init__(self, f, pyfile):
        #rda has not yet been added for Python files
        self.path = ''
        if '/' in pyfile:
            p = pyfile.split('/')
            self.path = '/'.join(p[:LAST_ELEMENT])+'/'
        self.calls = []
        #copy of csv file for Updater
        self.csv = []
        reader = csv.reader(f)
        #recreate csv file in self.csv
        for row in reader:
            self.csv.append(list(row))
        for n, line in enumerate(self.csv):
            self.searchCsv(line, n)

    #writes updated version of csv to the new csv file
    def updateCsv(self, f):
        writer = csv.writer(f)
        writer.writerows(self.calls)

    #searches through the csv to find any APIs that call JavaScript programs
    def searchCsv(self, row, n):
        jsfile = []
        #this code is meant specifically for PyV8.eval() - more if-statements can be added for additional APIs 
        #row[3] is where the function name of the call is found in the csv file
        if len(row) > 3:
            if 'OBJ.eval' in row[3]:
                #n = call id of the specific call being passed
                jsfile = self.findJS(n, row)
        else:
            sys.exit(error+"Incorrect syntax in csv file")
        #if the python file name is found, the python file will replace the API function name in the csv file
        #ex: 0,class,scope,OBJ.eval,OBJ.read()3
        #    0,class,scope,file.js
        if jsfile:
            #takes first 3 columns of the csv file (id,class,scope)
            newRow = row[:3]
            for j in jsfile:
                #adds line to csv file with first 3 rows and the Python file name at the end
                self.calls.append(list(newRow)) #list() creates a copy of newRow
                if '/' not in j:
                    j = self.path+j
                self.calls[LAST_ELEMENT].append(j)
        #if jsfile list is empty, API was not found
        #add the original row to the new csv file
        else:
            self.calls.append(row)
    
    #this function is written specifically for PyV8's eval function due to how it disects the argument
    #Due to the program's inability to determine the exact identification of objects that call member functions, the function call must be written this exact way for the analysis to work:
    #      PyV8.JSContext().eval(open("file.js").read())
    #similar functions can be written for other APIs that are specific to the arguments for those APIs
    def findJS(self, n, row):
        #for now jsfile can only have one value, but when rda is added, there could be multiple potential values
        jsfile = []
        #if the eval function belongs to PyV8, OBJ.JSContext function should be found in the line above OBJ.eval in the csv file
        #the name of the function called is found in the 4th column (hence self.csv[n-1][3])
        if '.JSContext' in self.csv[n-1][CSV_FUNCTION]:
            for x in xrange(4, len(row)):
                #read() should be an argument of OBJ.eval
                if 'read()' in row[x]:
                    #because read is a function call, it has it's call id attached to the end (ex: read()6) which can be used to find the function call in the csv file
                    m = row[x].split(')')[LAST_ELEMENT]
                    for i, c in enumerate(self.csv):
                        #find the read() call from OBJ.eval in the csv file using call id
                        if m == str(c[CSV_CALL_ID]):
                            #open() should be found in the line above read() in the csv file
                            if 'open' in self.csv[i-1][CSV_FUNCTION]:
                                #check if the argument is a string, and if it is a JavaScript file
                                #arguments start at column 5 in the csv file
                                if '<' in self.csv[i-1][CSV_ARGUMENTS] and '>' in self.csv[i-1][CSV_ARGUMENTS] and '.js' in self.csv[i-1][CSV_ARGUMENTS][JS_SUFFIX:]:
                                    jsfile = [self.csv[i-1][CSV_ARGUMENTS][1:-1]]
                            #if the value is not a JavaScript file or not a string (could be a variable), send error message
                                else:
                                    jsfile = ["ERROR_JavaScript_File_Cannot_Be_Discerned"]
                                    print error+"JavaScript file called cannot be determined"
        return jsfile

#####################################################
def main(inputCsv, pyfile, outputCsv):
    global error

    #check if csv file contains content from a Python program
    if '.py' not in pyfile[PY_SUFFIX:]:
        sys.exit(error+"csv file not a Python call graph")
    
    #read from input csv file and update csv if APIs found
    try:
        with open(inputCsv, 'r') as csvfile:
            updater = Updater(csvfile, pyfile);
    except IOError:
        sys.exit(error+inputCsv+" does not exist")

    #write updated csv to new csv file
    try:
        with open(outputCsv, 'w') as newcsv:
            updater.updateCsv(newcsv)
    except IOError:
        sys.exit(error+"problem writing new csv file")
