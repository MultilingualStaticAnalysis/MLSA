#
# MLSA project
#
# Filters a text pipe and reduces any pathname/filename strings
# to just filename
#
#diff <(python pathfilter.py file1.csv) <(python pathfilter.py file2.csv)

import os
import sys

error = "MLSA: filterpaths; "
filename = sys.argv[1]

try:
    with open(filename) as infile:
        lines = infile.read().split("\n");
        for line in lines:
            cols = line.split(",")
            numCols = len(cols)
            colNum=1
            printline=""
            for col in cols:
                potentialPath = col.find("/")
                if (potentialPath!=-1):
                    pathList = col.split("/")
                    printline = printline+pathList[-1]
                else:
                    printline = printline+col
                colNum = colNum+1
                if (colNum<=numCols):
                    printline = printline+","
            if (printline!=""):
                print printline
except IOError:
        sys.exit(error+filename+" does not exist")
