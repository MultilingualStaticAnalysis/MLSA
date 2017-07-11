#!/usr/bin/env python
# MLSA Multilingual Software Analysis
# This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
# cSA.py takes in a C or C++ file and generates a text ast file from that C/C++ file. cFunCall is called with the ast file passed to it, and creates a csv file of all the call graphs in the C/C++ program. pyViaC.py is called with that csv file, and results in a new csv file where any Python files called in the C/C++ program are substituted in for the appropriate API. That resulting csv file is then returned.
# Author: Anne Marie Bogar
# Date: June 13, 2017
# this code can be copied or used and is without warrenty or support, but this header needs to be copied along with the program FU2017
# Input: command line, a list of files and folders
# Output: all the CSV files fomr mlcg and one _finalcall.csv with the name
# of the first file argument specified which has the complete call graph

import sys
import os
import cSA
import pySA
import jsSA
import mergeFunCall
import generateDOT

ERROR = "MLSA: mlcg; "
files = []
csvfiles = []

if len(sys.argv) < 2:
    sys.exit(ERROR+"arguments needed")

sys.argv.pop(0)
title = sys.argv[0]
systemFuncs = title+'_funcs.csv'
cgCsv = title+'_callgraph.csv'
cgDot = title+'_callgraph.dot'
cgPs = title+'_callgraph.ps'
cgPdf = title+'_callgraph.pdf'

if not os.path.isfile(systemFuncs):
    try:
        with open(systemFuncs, 'w'):
            pass
    except IOError:
        sys.exit(ERROR+'cannot create function csv file')

for arg in sys.argv:
    if os.path.isdir(arg):
        print "retrieving files from "+arg+"..."
        files = files+sorted([os.path.join(arg, f) for f in os.listdir(arg) if os.path.isfile(os.path.join(arg, f))])
    elif os.path.isfile(arg):
        files.append(arg)
    else:
        sys.exit(ERROR+"argument passed is not a file or directory: "+arg)

# all Python programs called in this program should detect their own errors and use sys.exit() to end the program if an error occurs
# mlcg.py should not handle other programs' errors

#need to make main function for these
for f in files:
    fileType = f.split('.')[-1]
    if fileType == 'c' or fileType == 'cpp':
        print "processing C/C++ file "+f+"..."
        csvfiles.append(cSA.main(f, systemFuncs))
    elif fileType == 'py':
        print "processing Python file "+f+"..."
        csvfiles.append(pySA.main(f, systemFuncs))
    elif fileType == 'js':
        print "processing JavaScript file "+f+"..."
        csvfiles.append(jsSA.main(f, systemFuncs))
    else:
        pass

#need to make main function for these
if csvfiles:
    print "merging csv files..."
    mergeFunCall.main(csvfiles, systemFuncs, cgCsv)
    print "creating DOT file..."
    generateDOT.main(cgCsv, title, cgDot)
    print "generating call graph..."
    os.system("dot -Tps2 "+cgDot+" -o "+cgPs)
    os.system("ps2pdf "+cgPs+" "+cgPdf)
    print "the callgraph can be found in "+cgPdf
else:
    sys.exit(ERROR+"no language-specific callgraphs found")
