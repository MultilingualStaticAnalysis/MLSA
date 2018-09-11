#!/usr/bin/env python
# MLSA Multilingual Software Analysis
# This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
# mldg.py (Multilingual Dependency Graph) finds all the included file names in each program in a directory and creates a dependency graph
# Author: Anne Marie Bogar
# Date: May 10, 2018
# this code can be copied or used and is without warrenty or support, but this header needs to be copied along with the program FU2017
# Output: csv file
# 		program_type(int),program_name(string),included_program_name(string)

import sys
import os
import findIncludes
import targetAPI
import generateIncludeDOT
import createPDF

#global variables
ERROR = "MLSA; mlig.py: "
d = os.getcwd() #local directory
csvfile = d+"/includes.csv" #csv file name
statfile = d+"/includeStats.txt" #statistics file name
dotfile = d+'/includes.dot' #dot file name
pdffile = d+"/includes.pdf" #pdf file name
psfile = d+"/includes.ps" #ps file name

#get includes and prints stats
findIncludes.main(csvfile, statfile)
#create dot file for includes
targetAPI.main(csvfile, statfile)
generateIncludeDOT.main(csvfile, d, dotfile)
#create pdf graph of includes
createPDF.main(dotfile, psfile, pdffile)