#!/usr/bin/env python
# MLSA Multilingual Software Analysis
# This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
# pySA.py takes in a Python file and generates a JSON ast file from the Python file. pyFunCall is called with the ast file passed to it, and creates a csv file of all the call graphs in the Python program. jsViaPy.py is called with that csv file, and results in a new csv file where any JavaScript files called in the Python program are substituted in for the appropriate API. That resulting csv file is then returned.
# Author: Anne Marie Bogar
# Date: June 13, 2017
# this code can be copied or used and is without warrenty or support, but this header needs to be copied along with the program FU2017
# Input: Python file
# Output: csv file
#		call_id(int),class(string),scope(string),function_name(string),argument1(string),argument2(string)...
# for arguments, all literals are encased in <> (ex: <5>) and all variables have their line number attached (ex: var-6)
# function calls that are arguments of another function call have their id next to () in csv line of the other function call
#               ex: 6,GLOBAL,file.py,function1,function2()4

import os
import sys
import json
from ast2json import ast2json
import ast
import pyFunCall
import jsViaPy

#global variables
error = "MLSA: pySA; "

def main(pyfile, funcfile):
    global error

    if '.py' not in pyfile[-3:]:
        sys.exit(error+'file passed is not Python')

    #ex: file.py_ast.json
    astfile = pyfile+'_ast.json'
    #ex: file.py_call.csv
    csvfile = pyfile+'_call.csv'
    #ex: file.py_rda.csv
    rdafile = pyfile+'_rda.csv'
    #ready for mergeFunCall
    finalCsv = pyfile+'_finalcall.csv'
    
    if not os.path.isfile(funcfile):
        try:
            with open(funcfile, 'w'):
                pass
        except IOError:
            sys.exit(error+'cannot create function csv file')

    #generate ast
    try:
        with open(astfile, "w") as f:
            pyAst = ast2json(ast.parse(open(pyfile).read()))
            f.write(json.dumps(pyAst, indent=4))
    except IOError:
        sys.exit(error+astfile+" does not exist")

    #pyFunCall generates a function call csv file (csvfile)
    pyFunCall.main(astfile, pyfile, csvfile, funcfile)
    #pyRDA generates an rda csv file (rdafile)
    #pyRDA.main(astfile, pyfile, rdafile)
    #jsViaPy generates another function call csv file but with JavaScript file substitution
    jsViaPy.main(csvfile, pyfile, finalCsv)

    #clean-up intermediate files
    #os.system("rm "+astfile)
    #os.system("rm "+csvfile)
    #os.system("rm "+rdafile)

    return finalCsv

#if len(sys.argv) != 2:
#    sys.exit(error+"2 arguments needed")

#main(sys.argv[1], 'testing_func.csv')
