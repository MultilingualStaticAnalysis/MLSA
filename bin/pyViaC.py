#!/usr/bin/env python
# MLSA Multilingual Software Analysis
# This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
# pyViaC.py takes in the csv generated from functionChecker.py. The program checks through the csv file to determine if a python program has been called from the C program (through PyRun_SimpleFile). If so, the Python file name is found and replaces the API (PyRun_SimpleFile) in the csv file
# Author: Anne Marie Bogar
# Date: July 11, 2017
# this code can be copied or used and is without warrenty or support, but this header needs to be copied along with the program FU2017
# Input: csv file
#		call_id(int),class(string),scope(string),function_name(string),argument1(string),argument2(string)...
# Output: csv file
#		call_id(int),class(string),scope(string),function_name(string),argument1(string),argument2(string)...
# for arguments, all literals are encased in <> (ex: <5>) and all variables have their line number attached (ex: var-6)
# function calls that are arguments of another function call have their id next to () in csv line of the other function call
#               ex: 6,GLOBAL,file.py,function1,function2()4

### This probably needs to be redone for the new RDA

import sys
import csv

#global variables
error = "MLSA: pyViaC.py; " #beginning of error statement for all error messages in the program
RDA_ID = 0
PY_SUFFIX = -4
C_SUFFIX = -2
CPP_SUFFIX = -4
SECOND_ARG = 5
LAST_ELEMENT = -1
FIRST_ELEMENT = 0
CSV_FUNCTION = 3
VAR = 0
CALL_ID = 1

class Updater:
    def __init__(self, f, rdafile, cfile):
        #csv file name for reaching definition analysis (if needed)
        self.rdfile = rdafile
        self.path = ''
        if '/' in cfile:
            c = cfile.split('/')
            self.path = '/'.join(c[:-1])+'/'
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
        #this code is meant specifically for PyRun_SimpleFile - more if-statements can be added for additional APIs 
        if len(row) > CSV_FUNCTION:
            if 'PyRun_SimpleFile' in row[CSV_FUNCTION]:
                pyfile = self.findPY(row)
        else:
            sys.exit(error+"Incorrect syntax in csv file")
        #if the python file name is found, the python file will replace the API function name in the csv file
        #ex: 0,class,scope,PyRun_SimpleFile,FILE*,<file.py>
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
    
    #this function is written specifically for PyRun_SimpleFile due to the number of arguments it contains
    #this function can also be used for any API where the second argument represents the Python file
    #similar functions can be written for other APIs that use specific argument numbers for those APIs
    def findPY(self, line):
        #if rda is needed, there may be more than one Python file - therefore, pyfile is a list
        pyfile = []
        if len(line) > SECOND_ARG:
            #PyRun_SimpleFile csv syntax - id,class,scope,PyRun_SimpleFile,FILE*,<file.py>
            #checks to see if second argument is a string with .py at the end
            if '<' in line[SECOND_ARG][FIRST_ELEMENT] and '>' in line[SECOND_ARG][LAST_ELEMENT] and '.py' in line[SECOND_ARG][PY_SUFFIX:]:
                pyfile = [line[SECOND_ARG].strip()[1:-1]]
            #the second argument in the API is a variable - rda needed
            else:
                pyfile = self.reachingDef(line[SECOND_ARG])
                #if pyfile is sent back empty, the Python file name could not be fount - send error message
                if not pyfile:
                    pyfile = ["ERROR_Python_File_Cannot_Be_Discerned"]
                    print error+"Python file called cannot be determined"
        else:
            print error+"Incorrect syntax for API"
        return pyfile

    #searches through the corresponding rda csv file to find the value of the variable in the API that represents the Python file name
    def reachingDef(self, var):
        #lineFlag = False
        #there could be more than one potential value of the Python file name in rda
        potentialValues = []
        #splits variable name from line number (ex: var-6)
        v = var.split('-')
        #if there is no line number at the end of the variable name, the argument is most likely a binary operation/unary operation/lambda/function call
        if len(v) > CALL_ID:
            variable = v[VAR]
            callID = v[CALL_ID]
            try:
                #rda csv file syntax:   lineNumber,variableName,varaibleValue,variableName,variableValue...
                with open(self.rdfile, 'r') as f:
                    reader = csv.reader(f)
                    for row in reader:
                        #looks for corresponding line number
                        #if lineFlag == True:
                        #    lineFlag = False
			if row[RDA_ID] == callID:
                            for i, r in enumerate(row):
                                #looks for corresponding variable name
                                if r == variable:
                                    #the value of the variable will be in the next column
                                    #check to see if the value is a Python file
                                    if '.py' in row[i+1][PY_SUFFIX:]:
                                        potentialValues.append(row[i+1].strip('"'))
                        #for PyRun_SimpleFile, the cFunCall program assigns the variable to the line before the call actually happens (problem in the AST) -> need to search the next line
                        #if row[RDA_LINENO] == lineNum:
                        #    lineFlag = True
            except Exception as err:
                print err
                sys.exit(error+"problem reading "+self.rdfile)
        return potentialValues
        

#####################################################

def main(inputCsv, cfile, rdafile, outputCsv):
    global error

    #check if csv file contains content from a C/C++ program 
    if '.c' not in cfile[C_SUFFIX:] and '.cpp' not in cfile[CPP_SUFFIX:]:
        sys.exit(error+"csv file not a C/C++ call graph")

    #read from input csv file and update csv if APIs found
    try:
        with open(inputCsv, 'r') as csvfile:
            updater = Updater(csvfile, rdafile, cfile)
    except IOError:
        sys.exit(error+inputCsv+" does not exist")

    #write updated csv to new csv file
    try:
        with open(outputCsv, 'w') as newcsvfile:
            updater.updateCsv(newcsvfile)
    except IOError:
        sys.exit(error+"problem writing new csv file")

#check to see if exactly one argument was passed to the program
#if len(sys.argv) != 2:
#    sys.exit(error+"c file argument required")

#main(sys.argv[1]+'_func.csv', sys.argv[1], sys.argv[1]+'_edfunc.csv')
