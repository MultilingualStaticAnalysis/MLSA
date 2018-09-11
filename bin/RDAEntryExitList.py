#!/usr/bin/env python
# MLSA Multilingual Software Analysis
# This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
# <This program generates and solves the entry/exit lists for a given program>
# Author: <Sunand Raghupathi>
# Date: <6/28/17>
# This code can be copied or used and is without warrenty or support, but this header needs to be coppied along with the program FU2017
# Input: The control flow graph (in the form of a python list), the killGenLists (in a python list), and the name of the RDA csv file to be written
# Output: a csv file for the RDA in the form: <line number, varName, varValue, varName, varValue, etc..>


from RDAKillGen import prettyPrint
import random
import csv





workList = []

workSet = ()


def getFV(killGenList):
	#prettyPrint(killGenList)

	FV = []
	subFV1 = ()
	subFV2 = ()
	duplicate  = 0

	for index in killGenList:
		duplicate = 0
		scope = index[1]
		#print 'broh', scope	
		varID = index[2]['Gen'][0]
		for i in FV:
			if varID == i:
				duplicate = 1

		if (duplicate == 0):
			subFV1 = (varID, scope)
			FV.append(subFV1)


	FVset = set(FV)

	#print FVset
	return FVset


def getGV(killGenList):
	GV = []
	for i in killGenList:
		if i[1][1] == '-1':
			GV.append(i)
	return GV

#returns initial line number
def getInit(controlFlow):

	init = []
	for index in controlFlow:
		if (index[1] == ['']):
			init.append(index[0])

	return init

def checkGlobLocation(controlFlow, statement, globVar):
	#Get index of each
	for indexCount, index in enumerate(controlFlow):
		if statement == index[0]:
			statementIndex = indexCount
		if globVar[0] == index[0]:
			globVarIndex = indexCount
	if statementIndex > globVarIndex:
		return True
	else:
		return False



#Get entry set for a given line number, control flow graph, and kill/gen list
def getEntry(statement, controlFlow, FV, GV):

	#Definition of entry (for RDA):
	
	#if the line number of interest is not arrived at by any other line -
	# - (the start of a function, etc..) then it is composed of the names of the variables
	# that have the scope of that function, with a question mark indicating their unknown values
	# along with the names of the global variables that have already taken values with those values
	
	#if the line number is anything else, then it composed of the exit lists for all lines that could have
	# entered the line of interest

	entry = ('RDentry', statement)
	entrySet = []
	subSet1 = []
	subSet2 = []
	GVused = []

	
	for index in controlFlow:
		varFlag = False
		if index[0] == statement:
			if index[0] in getInit(controlFlow):
			
				for var in FV:
					#print var
					#var[1][0] and var[1][1] represent the boundaries of the scope
					
					if ((index[0] == var[1][2])):
						var2 = (var[0], '?')
						varFlag = True 
						subSet1.append(var2)
						entrySet = [entry, [subSet1], set()]

				globCheck = False

				
				for globVar in GV[::-1]:

					
					#Must replace this:
					if checkGlobLocation(controlFlow, index[0], globVar):
						varName = globVar[2]['Gen'][0]	
						if varName not in GVused:
							varVal = globVar[2]['Gen'][1]
							subSet1.append((varName, varVal))
							GVused.append(varName)
							globCheck = True
								
				#To prevent infinite loops, since we look for empty sets when solving
				if (globCheck == False) and varFlag == False:
					subSet1.append(('?','?'))
				entrySet = [entry, [subSet1], set()]


			else:
				for count1 in index[1]:
					temp = ('RDexit', count1)
					subSet1.append(temp)

				entrySet = [entry, [subSet1], set()]


	#print entrySet
	return entrySet
	

def getExit(statement, controlFlow, killGenList):
	#Definition for exit (RDA):
	
	#if the line of interest has an assignment,
	# then the list is composed of the entry list for the line
	# number of interest, the kill list for that assignment, and the
	# gen list for that assignment in that order.
	# The order tells us that we Union the entry list, difference the kill list, 
	# then union the gen list. 

	exit = ('RDexit', statement)
	entry = ('RDentry', statement)
	subSet1 = []
	exitSet = []
	
	varFlag = False

	for index in killGenList:
		if index[0] == statement:
			varFlag = True
			kill = index[2]['Kill']
			gen = index[2]['Gen']
			subSet1 = [[entry], kill, gen]
			exitSet = [exit, subSet1, set()]

	if varFlag == False:
		subSet2 = []
		subSet2.append(entry)
		exitSet = [exit, [subSet2], set()]


	return exitSet



def getEntryExitList(controlFlow, killGenList):
	Final = []
	#Gets list of global variables
	GV = getGV(killGenList)
	#Gets list of all variables
	FV = getFV(killGenList)
	
	#For every line in the program (represented by the control flow by index[0]), initialize
	#both the entry list and the exit list
	for index in controlFlow:
		Final.append(getEntry(index[0], controlFlow, FV, GV))
	for index in controlFlow:
		Final.append(getExit(index[0], controlFlow, killGenList))

	return Final






#Checks if substitutions are complete
#return 0 if false, return 1 if true, 
def checkSubs(entryExitList):
	check = 1

	for index in entryExitList:	
		if ('RDexit' in index[1][0] or 'RDentry' in index[1][0]):
			check = 0

	return check



def substitution(lineNumber, entryExitList):

	#The set contains the solutions

	line = lineNumber - 1
	subFlag = False
	killGenFlag = True
	'''
	print '--------------------------------------------------------------'
	print 'Operating on:'
	print entryExitList[line]
	print ''
	print ''
	'''

	for index1 in entryExitList[line][1][0]:
		for index2 in index1:
			if index2 == 'RDentry' or index2 == 'RDexit':
				subFlag = True


	if (subFlag):
		#turn into for loop to iterate through
		
		length = len(entryExitList[line][1][0])
		#If more than 1 substitution needs to be made, length > 1
		substituted = 0

	
		tempList = []
		tempList2 = []
		substituted = 0
		for j in entryExitList[line][1][0]:
			tempList2 = [j, substituted]
		
			tempList.append(tempList2)
		
		#print 'PRINTING TEMPLIST #############################'
		#print tempList
		#print '###############################################'

		#range(0, length)
		#entryExitList[line][1][0]
		for i in entryExitList[line][1][0]:	
			#randomize which element to search, while accounting for the ones that have already been searched
			r = random.randint(0, length-1)
			while tempList[r][1] != 0:
				r = random.randint(0, length-1)





			searchLine = tempList[r][0]
			tempList[r][1] = 1
			'''
			print 'Search for line:'
			print searchLine
			print ''
			'''
			for index in entryExitList:
				found = False
				if index[0] == searchLine:
					found = True
					'''
					print ''
					print 'Found line:'
					print index
					print ''
					print ''
					'''
					#Check if set is empty. In other words, check if there is a lack of information
					if len(index[2]) == 0:
						killGenFlag = False

						
						if entryExitList[line] not in workList:
							workList.append(entryExitList[line])

						workList.append(index)
						


					else:
						for index1 in index[2]:
							entryExitList[line][2].add(index1)

				
			

		#Difference and Unioning
		if (killGenFlag):
			if (len(entryExitList[line][1]) > 1):
				for i in entryExitList[line][1][1]:
					entryExitList[line][2].discard(i)
				entryExitList[line][2].add(entryExitList[line][1][2])

		
	#If RDentry or RDexit is not present, just add the contents to the set
	else:
		for index in entryExitList[line][1][0]:
			entryExitList[line][2].add(index)


	return killGenFlag
	

def getLineNumber(element, entryExitList):
	count = 0

	for index in entryExitList:
		count = count + 1
		if (index == element):
			break
		
		

	return count

					 


#prettyPrint(entryExitList)


def solveWorkList(entryExitList):

	#removeDuplicates()
	length = len(workList)
	if length != 0:
		#flag = removeDuplicates()
		#if flag == 1:
		#	print 'Flag'	
		
		'''
		print 'PRINTING WORKLIST'
		print '*******************************'
		prettyPrint(workList)
		'''

		element = workList[length-1]
		line = getLineNumber(element, entryExitList)
		x = substitution(line, entryExitList)
		if (x == 0):
			solveWorkList(entryExitList)
		if (x == 1):
			workList.pop()
			'''
			prettyPrint(entryExitList)
			'''
			solveWorkList(entryExitList)

	#else -> end recursion	




def backSubstitueList(entryExitList):
	
	length = len(entryExitList)/2
	for i in range(1, length + 1):
		if (len(workList) != 0):
			solveWorkList(entryExitList)

		substitution(i, entryExitList)
		'''	
		prettyPrint(entryExitList)
		'''
		if (len(workList) != 0):
			solveWorkList(entryExitList)

		substitution(i + len(entryExitList)/2, entryExitList)
		'''
		prettyPrint(entryExitList)
		'''
	

#entryExitList = getEntryExitList(controlFlow, killGenList)

#backSubstitueList(entryExitList)



#Write CSV file:
def writeCSV(entryExitList, fileName):
	error = "MLSA: RDAEntryExitList "

	Final = []
	subList = []
	try:	
		with open(fileName, 'w') as ofile:
			writer = csv.writer(ofile)

			for i in entryExitList:

				#Only include entry list in csv
				if i[0][0] == "RDexit":
					break
				subList = []
				lineNumber = i[0][1]
				subList.append(lineNumber)
				for j in i[2]:
					for x in j:
						subList.append(x)

				Final.append(subList)
			writer.writerows(Final)
	except Exception:
		sys.exit(error + "file " + '"' + fileName + '"' + " could not be written")





#Format of controlFlow:
#	Python List [[line i, [all lines that could have led to i]], ...]
#Format of killGenLis
#	Python List [[line number, (scope), {'Kill': [kill list], 'Gen': [gen list]}], ...]
def main(controlFlow, killGenList, outputFile):

	#Initialize the entryExitList (before solving)
	entryExitList = getEntryExitList(controlFlow, killGenList)


	#Solve the initialied list
	backSubstitueList(entryExitList)
	#Output the solution to a file
	writeCSV(entryExitList, outputFile)
	#Return the solution
	return entryExitList



