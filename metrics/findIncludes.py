#!/usr/bin/env python
# MLSA Multilingual Software Analysis
# This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
# findIncludes.py prints out a list of all the included files and libraries, along with their corresponding file. The file uses the island grammars cinclude, pyimport, and jsimport.
# Author: Anne Marie Bogar
# Date: November 13, 2017
# this code can be copied or used and is without warrenty or support, but this header needs to be copied along with the program FU2017
# Output: csv file
# 		program_type(int),program_name(string),included_program_name(string)

import sys
import os
import commands
import csv
import operator
import config

#global variables
ERROR = "MLSA; findIncludes.py: "
dirs = []
includes = []
files = []
countIncludes = {}
#csvfile = os.getcwd()+"/includes.csv"
#statfile = os.getcwd()+"/includeStats.txt"
extensions = {"git":0, "executable file":0}
#CSV Indices
CSV_TYPE_ID = 0
CSV_PROGRAM = 1
CSV_INCLUDE = 2
#Specific Element Indices
LAST_ELEMENT = -1
FIRST_ELEMENT = 0
#Island Grammar Indices
ISLAND_GRAMMAR_INCLUDES = 1
ISLAND_GRAMMAR_STATUS = 0

#retursively iterate through the directories to find all directories and add all files to list
def recurseDirs(d):
	global dirs
	tempdirs = sorted([os.path.join(d, f) for f in os.listdir(d) if os.path.isdir(os.path.join(d, f))])
	dirs = dirs+tempdirs
	for t in tempdirs:
		if not os.path.islink(t): #makes sure not a link -> this will create an endless loop
			recurseDirs(t)

#run all Include/Import/Require Island Grammars on appropriate programs
def logIncludes(f, n, grammars):
	global countIncludes, includes
	i = []
	countIncludes[f] = 0
	for g in grammars:
		i = commands.getstatusoutput(g+" < \""+f+"\"")
		if i[ISLAND_GRAMMAR_STATUS] == 0 and i[ISLAND_GRAMMAR_INCLUDES] != "" and "syntax error" not in i[ISLAND_GRAMMAR_INCLUDES]:
			ins = i[ISLAND_GRAMMAR_INCLUDES].split('\n')
			for h in ins:
				if h != "":
					includes.append([n, f, h])
		if "syntax error" in i[ISLAND_GRAMMAR_INCLUDES]:
			print(f)

#calculate the statistics for each programming language
def calculateStats():
	#stats = {program_extension:[list of number of included files for each program]}
	for k, v in config.stats.iteritems():
		if k not in extensions: #if k is not a program language in the specific folder
			config.stats[k] = [0, 0, 0]
		else:
			maxi = 0
			mini = 100
			count = 0.0
			for n in v:
				if n > maxi:
					maxi = n
				if n <= mini:
					mini = n
				count += n
			config.stats[k] = [maxi, mini, (count/extensions[k])]

#write statistics to a text file
def writeStats(statfile):
	global extensions, countIncludes, files
	numprograms = len(countIncludes)*1.0 #make it a float and not an int
	numfiles = len(files)
	calculateStats()
	#progtypes = list of lanugages to be analyzed
	#stats = {program_extension:[max_number_of_included_files_in_one_program, min_number_of_included_files, average_number_of_included_files]}
	try:
		with open(statfile, 'w') as s:
			#write total number of programs in each language
			s.write("FILES\n")
			s.write("num files:\t"+str(numfiles)+"\n")
			ex = reversed(sorted(extensions.items(), key=operator.itemgetter(1)))
			for k, v in ex:
				s.write("num "+k+":\t"+str(v)+"\n")
			s.write("\n-------------------------------------------\n\n")
			s.write("PERCENTAGES\n")
			#write percentage of each language type to the whole codebase
			for p in config.progtypes:
				if p in extensions:
					s.write(p+":\t"+str((extensions[p]/numprograms))+"\n")
			s.write("\n-------------------------------------------\n\n")
			s.write("STATS\n")
			#write the statistics (min, max, avg) for each language that can be parsed by IG -> C/C++, H/HPP, Python, JavaScript
			for k, v in config.stats.iteritems():
				if k in extensions:
					s.write(k+"\n\ttotal files:\t"+str(extensions[k])+"\n\tmax inlcudes:\t"+str(v[0])+"\n\tmin includes:\t"+str(v[1])+"\n\tavg includes:\t"+str(v[2])+"\n")
			s.write("\n-------------------------------------------\n\n")
	except IOError:
		sys.exit(ERROR+statfile+" does not exist")

###########################################################

def main(csvfile, statfile, args=[]):
	global dirs, includes, countIncludes, files, extensions
	
	if not args:
		dirs.append(os.getcwd())
	else:
		for a in args:
			dirs.append(a)
	
	#add all the directories in the codebase
	recurseDirs(dirs[FIRST_ELEMENT])
	
	#add all the files in the directories
	for d in dirs:
		if os.path.isdir(d):
			files = files+sorted([os.path.join(d, f) for f in os.listdir(d) if os.path.isfile(os.path.join(d, f))])
		elif os.path.isfile(d):
			files.append(d)
		else:
			sys.exit("argument passed is not a file or directory "+d)

	#progtypes = list of lanugages to be analyzed
	#idDict = {language_extension:id}
	#substituteDict = {alternate_extension:main_extension}
	#grammarDict = {language_extension:island_grammar_program}
	#count how many of each language in the codebase
	for f in files:
		ext = f.split('.')[LAST_ELEMENT]
		if "git/" in ext:
			extensions["git"] += 1
		elif "/home/" in ext:
			extensions["executable file"] += 1
		else:
			if ext in config.substituteDict: #sometimes multiple extensions for one language
				ext = config.substituteDict[ext]
			if ext not in extensions:
				extensions[ext] = 0
			extensions[ext] += 1
			if ext in config.progtypes:
				#calls IG to count the included files in each program
				logIncludes(f, config.idDict[ext], config.grammarDict[ext])
	
	#count include num for each programming language
	for i in includes:
		if i[CSV_INCLUDE] != "":
			countIncludes[i[CSV_PROGRAM]] += 1

	#idDict = {language_extension:id}
	#substituteDict = {alternate_extension:main_extension}
	#stats = {program_extension:[list of number of included files for each program]}
	for f, n in countIncludes.iteritems():
		ext = f.split('.')[LAST_ELEMENT]
		if ext in config.substituteDict:
			ext = config.substituteDict[ext] #sometimes multiple extensions for one language
		if n == 0:
			includes.append([config.idDict[ext], f, ""]) #count the program even if no includes
		config.stats[ext].append(n)

	#write include stats to file
	writeStats(statfile)

	#write info for each include to csv file
	try:
		with open(csvfile, 'w') as csvFile:
			writer = csv.writer(csvFile)
			writer.writerows(includes)
	except IOError:
		sys.exit(ERROR+csvfile+" does not exist")

#main(csvfile, statfile)
