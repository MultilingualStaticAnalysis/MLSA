import sys
import os
import csv
import commands
from copy import deepcopy

#global variables
ERROR = "MLSA; IG Stat Counter: "
files = []
mlsa = {}
dox = {}

#INDICES
LAST_ELEMENT = -1
#Island Grammar Indices
ISLAND_GRAMMAR_CALLS = 1
ISLAND_GRAMMAR_STATUS = 0
#Call Indices
CALL_ID = 0
CALL_SCOPE = 1
CALL_NAME = 2
CALL_ARG = 3

def treeToGraph(calls, astfile, dic):
    for c in calls:
        argcount = len(c)-3
        if c[CALL_NAME] not in dic[astfile.split("/")[-1].split("_")[0]]:
            dic[astfile.split("/")[-1].split("_")[0]][c[CALL_NAME]] = argcount

def collectCalls(converter, astfile, dic):
    calls = []
    i = commands.getstatusoutput("~/11-2-17/mlsa/IG/"+converter+" < "+astfile)
    if i[ISLAND_GRAMMAR_STATUS] == 0 and i[ISLAND_GRAMMAR_CALLS] != "" and "syntax error" not in i[ISLAND_GRAMMAR_CALLS]:
        c = i[ISLAND_GRAMMAR_CALLS].split('\n')
        for d in c:
			#id,scope,name,args...
            calls.append(d.split(','))
        treeToGraph(calls, astfile, dic)
    if "syntax error" in i[ISLAND_GRAMMAR_CALLS]:
        print "syntax error"

def printStats():
    for key, value in dox.iteritems():
        if key in mlsa:
            print key
            print "  Doxygen"
            for k, v in value.iteritems():
                print "   - "+k, v
            print "  MLSA"
            for k, v in mlsa[key].iteritems():
                print "   - "+k, v

#####################################################################

if len(sys.argv) < 2:
    sys.exit(ERROR+"1 argument needed")

sys.argv.pop(0)

for arg in sys.argv:
    if os.path.isdir(arg):
        print "retrieving files from "+arg+"..."
        files = files+sorted([os.path.join(arg, f) for f in os.listdir(arg) if os.path.isfile(os.path.join(arg, f))])
    elif os.path.isfile(arg):
        files.append(arg)
    else:
        sys.exit(ERROR+"argument passed is not a file or directory: "+arg)

for f in files:
    if "_MLSA.dot" in f:
        mlsa[f.split("/")[-1].split("_")[0]] = {}
        collectCalls("MLSAConvert", f, mlsa)
    elif "_Dox.dot" in f:
        dox[f.split("/")[-1].split("_")[0]] = {}
        collectCalls("DoxConvert", f, dox)
    else:
        pass

printStats()