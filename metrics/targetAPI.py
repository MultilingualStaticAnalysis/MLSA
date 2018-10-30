#!/usr/bin/env python

import csv
import os

#global variables
targets = {}
APIcount = {}
targetDict = {}
callee = {}
caller = {}
targetnames = "target_files.txt"
#targetnames = "target_files.txt"
for path in os.environ['PATH'].split(':'):
	if "mlsa/metrics" in path:
		targetnames = path+'/'+targetnames
		break
csvfile = "includes.csv"
statfile = "includeStats.txt"
totalfiles = 0.0
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
    with open(targetnames) as tn:
        reader = csv.reader(tn)
        for row in reader:
            targets[row[API_NAME]] = []
            targetDict[row[API_NAME]] = [row[API_CALLER], row[API_CALLEE]]
            if row[API_CALLER] not in APIcount:
                APIcount[row[API_CALLER]] = {row[API_CALLEE]:0}
            if row[API_CALLEE] not in APIcount[row[API_CALLER]]:
                APIcount[row[API_CALLER]][row[API_CALLEE]] = 0



def collectTargets(csvfile):
    totalfiles = 0.0
    with open(csvfile) as c:
        reader = csv.reader(c)
        for row in reader:
            totalfiles += 1
            if len(row) > CSV_INCLUDE:
                for t in targets:
                    if t in row[CSV_INCLUDE]:
                        targets[t].append(row[CSV_PROGRAM])



def countAPIs():
    global MLfiles
    for k, v in targets.iteritems():
        targets[k] = set(v)
        MLfiles += len(targets[k])
        for t in targets[k]:
            APIcount[targetDict[k][TARGET_CALLER]][targetDict[k][TARGET_CALLEE]] += 1




def writeStats(statfile):
    for key, val in APIcount.iteritems():
        caller[key] = 0
        for k, v in val.iteritems():
            if k not in callee:
                callee[k] = 0
            if v > 0:
                caller[key] += v
                callee[k] += v

    with open(statfile, "a+") as s:
        s.write("INTEROPERABILITY APIs\n")
        for k, v in targets.iteritems():
            if v:
            
                s.write(k+"   \t("+targetDict[k][0]+" calls "+targetDict[k][1]+"):\t\t"+str(len(v))+"\n")
           #prints the list of the multilingual programs
           #Date:10/23/18
           #Name:Saba           
                l=str(v)[5:-2]
                n=l.split(",")
                m=list(n)
                for elem in m:
                    s.write(str(elem)+"\n")
           #---------------
        s.write("\n")
        for a, b in APIcount.iteritems():
            for c, d in b.iteritems():
                if d > 0:
                    s.write(a+" calls "+c+":\ttotal: "+str(d)+"\t%all ML: "+str(d/MLfiles)+"\n")




 
def main(csvfile, statfile):

	initializeTargets()
	collectTargets(csvfile)
	countAPIs()
	writeStats(statfile)
	#printStats()
