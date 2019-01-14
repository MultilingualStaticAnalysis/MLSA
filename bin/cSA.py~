#!/usr/bin/env python
# MLSA Multilingual Software Analysis
# This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
# cSA.py takes in a C or C++ file and generates a text ast file from that C/C++ file. cFunCall is called with the ast file passed to it,
#       and creates a csv file of all the call graphs in the C/C++ program. pyViaC.py is called with that csv file, 
#       and results in a new csv file where any Python files called in the C/C++ program are substituted in for the appropriate API. 
#       That resulting csv file is then returned.
# Author: Anne Marie Bogar
# Date: May 9, 2018
# this code can be copied or used and is without warrenty or support, but this header needs to be copied along with the program FU2017
# Input: Python file
# Output: csv file
#		call_id(int),class(string),scope(string),function_name(string),argument1(string),argument2(string)...
# for arguments, all literals are encased in <> (ex: <5>) and all variables have their line number attached (ex: var-6)
# function calls that are arguments of another function call have their id next to () in csv line of the other function call
#               ex: 6,GLOBAL,file.c,function1,function2()4

import os
import sys
import pyViaC
import cFunCall2
import cRDAGroup

#global variables
error = "MLSA: cSA; "

def main(cfile, funcfile):
    global error

    if '.c' not in cfile[-2:] and '.cpp' not in cfile[-4:]:
        sys.exit(error+'file passed is not C or C++')

    #ex: file.c_ast.txt
    astfile = cfile+'_ast.txt'
    #ex: file.c_func.csv
    csvfile = cfile+'_call.csv'
    #ex: file.c_rda.csv
    rdafile = cfile+'_rda.csv'
    #ready for mergeFunCall
    finalCsv = cfile+'_finalcall.csv'

    #generate ast
    os.system('clang-check-3.8 -ast-dump --extra-arg-before="-std=c++11" ' + cfile + ' --extra-arg="-fno-color-diagnostics" -- > ' + astfile)
    #jj='clang-check-3.8 -ast-dump --extra-arg-before="-std=c++11" ' + cfile + ' --extra-arg="-fno-color-diagnostics" -- > ' + astfile
    #print(jj)
    # cFunCall2 generates a function call csv file (csvfile)
    cFunCall2.main(astfile, cfile, csvfile, funcfile)
    #cRDA generates an rda csv file (rdafile)
    cRDAGroup.main(astfile, cfile, rdafile)
    #pyViaC generates another function call csv file but with Python file substitution
    pyViaC.main(csvfile, cfile, rdafile, finalCsv)

    #clean-up intermediate files
    #os.system("rm "+astfile)
    #os.system("rm "+csvfile)
    #os.system("rm "+rdafile)
    
    return finalCsv

# **use for debugging purposes
#if len(sys.argv) != 2:
#    sys.exit(error+"2 arguments needed")

#main(sys.argv[1])
