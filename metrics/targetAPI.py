#!/usr/bin/env python
# MLSA Multilingual Software Analysis
# This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
# targetAPI.py prints out all the files that include the certain libraries listed in target_files.txt
# Author: Anne Marie Bogar
# Date: November 13, 2017
# this code can be copied or used and is without warrenty or support, but this header needs to be copied along with the program FU2017
# Input: csv file
#		program_type(int),program_name(string),included_program_name(string)
# Output: dot file
# 

import csv
import os

#global variables
targets = {}
csvfile = os.getcwd()+"/includes.csv"
targetnames = "target_files.txt"
for path in os.environ['PATH'].split(':'):
	if "mlsa/metrics" in path:
		targetnames = path+'/'+targetnames
csvfile = os.getcwd()+"/includes.csv"
#CSV Indices
CSV_TYPE = 0
CSV_PROGRAM = 1
CSV_INCLUDE = 2


with open(targetnames) as tn:
	templist = tn.read().splitlines()
	for t in templist:
		targets[t] = []

with open(csvfile) as c:
	reader = csv.reader(c)
	for row in reader:
		if len(row) > CSV_INCLUDE:
			for t in targets:
				if t in row[CSV_INCLUDE]:
					targets[t].append(row[CSV_PROGRAM])

for k, v in targets.iteritems():
	if v:
		print k
		for i, prog in enumerate(v):
			print "\t"+str(i+1)+")", prog
		print "-----------------------------------"