# MLSA Multilingual Software Analysis
# This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
# jsSA.py takes in a JavaScript file and generates a JSON ast file from that JavaScript file. jsFunCall is called with the ast file passed to it, and creates a csv file of all the call graphs in the JavaScript program. pyViaJs.py is called with that csv file, and results in a new csv file where any Python files called in the JavaScript program are substituted in for the appropriate API. That resulting csv file is then returned.
# Author: Anne Marie Bogar
# Date: June 15, 2017
# this code can be copied or used and is without warrenty or support, but this header needs to be copied along with the program FU2017
# Input: JavaScript file
# Output: csv file
#		call_id(int),class(string),scope(string),function_name(string),argument1(string),argument2(string)...
# for arguments, all literals are encased in <> (ex: <5>) and all variables have their line number attached (ex: var-6)
# function calls that are arguments of another function call have their id next to () in csv line of the other function call
#               ex: 6,GLOBAL,file.js,function1,function2()4

import os
import sys
import json
import testing2
import testing3

#global variables
error = "MLSA: jsSA; "

def main(jsfile, param2=False):
    global error

    if '.js' not in jsfile[-3:]:
        sys.exit(error+'file passed is not JavaScript')

    #ex: file.js_ast.json
    astfile = jsfile+'_ast.json'
    #ex: file.js_func.csv
    csvfile = jsfile+'_func.csv'
    #ex: file.js_rda.csv
    rdafile = jsfile+'_rda.csv'
    #ready for mergeFunCall
    editedCsv = jsfile+'_edfunc.csv'

    #generate ast
    os.system("js24 -e \"print(JSON.stringify(Reflect.parse(read('"+jsfile+"'))));\" > "+astfile)

    #jsFunCall generates a function call csv file (csvfile)
    testing3.main(astfile, jsfile, csvfile)
    #jsRDA generates an rda csv file (rdafile)
    #jsRDA.main(astfile, jsfile, rdafile)
    #pyViaJs generates another function call csv file but with Python file substitution
    testing2.main(csvfile, jsfile, editedCsv)

    #clean-up intermediate files
    #os.system("rm "+astfile)
    #os.system("rm "+csvfile)
    #os.system("rm "+rdafile)

    return editedCsv

#if len(sys.argv) != 2:
#    sys.exit(error+"2 arguments needed")

#main(sys.argv[1])
