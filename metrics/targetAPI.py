#!/usr/bin/env python
# MLSA Multilingual Software Analysis
# This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
# targetAPI.py prints out all the files that include the certain libraries listed in target_files.txt
# Author: Anne Marie Bogar
# Date: December 4, 2017
# this code can be copied or used and is without warrenty or support, but this header needs to be copied along with the program FU2017
# Input: csv file
#		program_type(int),program_name(string),included_program_name(string)
# Output: dot file
# 

import csv
import os

#global variables  
ERROR = "MLSA; targetAPI.py; "                                                                                                                                                                                         
targets = {}
APIcount = {}
targetDict = {}
targetnames = "target_files.txt"
for path in os.environ['PATH'].split(':'):
	if "mlsa/metrics" in path:
		targetnames = path+'/'+targetnames
		break
MLfiles = 0.0
#CSV Indices                                                                                                                                                                                                
CSV_TYPE = 0
CSV_PROGRAM = 1
CSV_INCLUDE = 2
#API Indices                                                                                                                                                                                                
API_NAME = 0
API_CALLER = 1
API_CALLEE = 2
#targetDict Indices                                                                                                                                                                                         
TARGET_CALLER = 0
TARGET_CALLEE = 1

def initializeTargets():
    global targets, APIcount, targetDict
    try:
        with open(targetnames) as tn:
            reader = csv.reader(tn)
            for row in reader:
                targets[row[API_NAME]] = [] #create key with API's name
                targetDict[row[API_NAME]] = [row[API_CALLER], row[API_CALLEE]] #create key with API name and value with caller language and callee language
                if row[API_CALLER] not in APIcount:
                    APIcount[row[API_CALLER]] = {row[API_CALLEE]:0} #create key with caller language that has a dictionary with key callee language and value of 0
                    if row[API_CALLEE] not in APIcount[row[API_CALLER]]:
                        APIcount[row[API_CALLER]][row[API_CALLEE]] = 0 #in caller lanugage key, add a callee language key with value of 0
    except IOError:
        sys.exit(ERROR+targetnames+" does not exist")

def collectTargets(csvfile):
    global targets
    try:
        with open(csvfile) as c:
            reader = csv.reader(c)
            for row in reader:
                if len(row) > CSV_INCLUDE:
                    for t in targets:
                        if t in row[CSV_INCLUDE]:
                            targets[t].append(row[CSV_PROGRAM])
    except IOError:
        sys.exit(ERROR+csvfile+" does not exist")

def countAPIs():
    global targets, APIcount, MLfiles
    for k, v in targets.iteritems():
        targets[k] = set(v)
        MLfiles += len(targets[k])
        for t in targets[k]:
            APIcount[targetDict[k][TARGET_CALLER]][targetDict[k][TARGET_CALLEE]] += 1

def writeStats(statfile):
    try:
        with open(statfile, "a+") as s:
            s.write("INTEROPERABILITY APIs\n")
            for k, v in targets.iteritems():
                if v:
                    s.write(k+"   \t("+targetDict[k][0]+" calls "+targetDict[k][1]+"):\t\t"+str(len(v))+"\n")
            s.write("\n")
            for a, b in APIcount.iteritems():
                for c, d in b.iteritems():
                    if d > 0:
                        s.write(a+" calls "+c+":\ttotal: "+str(d)+"\t%all ML: "+str(d/MLfiles)+"\n")
    except IOError:
        sys.exit(ERROR+statfile+" does not exist")

def printStats():
	for k, v in targets.iteritems():                                                                                                                                                                           
	    if v:                                                                                                                                                                                                  
	        print k                                                                                                                                                                                            
	        for i, prog in enumerate(v):                                                                                                                                                                       
	            print "\t"+str(i+1)+")", prog                                                                                                                                                                  
	        print "-----------------------------------" 

##################################################################

def main(csvfile, statfile):

	initializeTargets()
	collectTargets(csvfile)
	countAPIs()
	writeStats(statfile)
	#printStats()

#csvfile = os.getcwd()+"/includes.csv"
#statfile = os.getcwd()+"/includeStats.txt"
#main(csvfile, statfile)
