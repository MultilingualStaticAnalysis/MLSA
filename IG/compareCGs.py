import os
import sys
import commands
from copy import deepcopy


ERROR = 'MLSA: compareCGs; '
#Island Grammar Indices
ISLAND_GRAMMAR_CSV = 1
ISLAND_GRAMMAR_STATUS = 0
#CSV Indices
CSV_ID = 0
CSV_SCOPE = 1
CSV_CALL = 2

def getCSV(ig, dot):
	retval = []
	i = commands.getstatusoutput(ig+" < "+dot)
	if i[ISLAND_GRAMMAR_STATUS] == 0 and i[ISLAND_GRAMMAR_CSV] != "" and "syntax error" not in i[ISLAND_GRAMMAR_CSV]:
		c = i[ISLAND_GRAMMAR_CSV].split('\n')
		for d in c:
			#id,scope,name,args...
			retval.append(d.split(','))
	if "syntax error" in i[ISLAND_GRAMMAR_CSV]:
		print "syntax error"
	return retval

def compareCSV(first, second):
	retval = []
	for f in first:
		add = True
		for s in second:
			if f[CSV_SCOPE] == s[CSV_SCOPE] and f[CSV_CALL] == s[CSV_CALL]:
				add = False
		if add == True:
			retval.append(deepcopy(f))
	return retval

def main(doxDot, mlsaDot):
	path = "IG/"
	for x in os.environ['PATH'].split(':'):
		if "mlsa/bin" in x:
			path = x[:-3]+path
			break
	print path

	doxCsv = getCSV(path+"DoxConvert", doxDot)
	mlsaCsv = getCSV(path+"MLSAConvert", mlsaDot)
	notCaughtDox = compareCSV(doxCsv, mlsaCsv)
	notCaughtMLSA = compareCSV(mlsaCsv, doxCsv)
	argcount = 0
	for m in mlsaCsv:
		argcount += len(m)-3
	print str(argcount)
	print "\nMLSA missed", len(notCaughtDox), "calls in Doxygen's callgraph"
	for d in notCaughtDox:
		print d
	print "\nDoxygen missed", len(notCaughtMLSA), "calls in MLSA's callgraph"
	for m in notCaughtMLSA:
		print m
	#with open("compStats.txt", "w") as f:
	#	f.write("number of calls caught by Doxygen: "+str(len(doxCsv))+"\n")
	#	f.write("number of calls caught by MLSA: "+str(len(mlsaCsv))+"\n")
	#	f.write("number of arguments caught by MLSA: "+str(argcount)+"\n")


if len(sys.argv) < 3:
    sys.exit(ERROR+"arguments needed: Dox dot file first, MLSA dot file second")
main(sys.argv[1], sys.argv[2])