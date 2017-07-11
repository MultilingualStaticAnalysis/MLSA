# MLSA Multilingual Software Analysis
# This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
# <This program parses the Abstract Syntax Tree for a C program, and extracts the variable assignments (only literals) into a Python List>
# <It is important to note that although this program extracts some values for assignemnts, that in itself is a seperate issue. The main function
# of this program is to extract the assignments, not interperate them.>
# Author: <Sunand Raghupathi>
# Date: <6/14/17>
# This code can be copied or used and is without warrenty or support, but this header needs to be coppied along with the program FU2017
# Input: <the abstract syntax tree (.txt) generated by Clang>
# Output: A python list of the form: <Line number, Variable name, (Scope), Variable value>

import csv
import sys

def getFileName():
	inputfile = raw_input("Enter the program name: ")
	return inputfile


#Takes everything AFTER the colon
def colonRemoverAfter(text):
	colonCount = 0
	for index in text:
		colonCount = colonCount + 1
		if (index == ':'):
			break
	text = text[colonCount:]
	return text

#Returns the part of the string BEFORE the colon
def colonRemoverBefore(text):
	colonCount = 0
	for index in text:
		colonCount = colonCount + 1
		if (index == ':'):
			break
	text = text[:colonCount - 1]
	return text

def findSource(treeLines, fileName):

	treeList = []

	#Strip _ast.txt


	fileFound = False
	
	for line in treeLines:
		if line.find('<') != -1 and line.find('>') != -1 and (line.find('.c') != -1 or line.find('.cpp') != -1 or line.find('.h') != -1):
			tempLine = line.split()
			for index in tempLine:
				if index.find('<') != -1 and (index.find('.c') != -1 or index.find('.cpp') != -1 or index.find('.h') != -1):
					
					if index.find(':') != -1:
						index = colonRemoverBefore(index)
					if index.find('/') != -1:
						index = backslashRemoverAfter(index)
					index = index.strip('<')
					if index == fileName:
						fileFound = True
					else:
						fileFound = False
		
		if fileFound:
			treeList.append(line)

	return treeList



def backslashRemoverAfter(text):
	count = 0
	index = 0
	for i in text:
		count = count + 1
		if i == '/':
			index = count

	return text[index:]


def AssignmentCollector(inputfile):

	error = "MLSA: CAssignmentCollector "
	isCpp = False

	#This tells us if the value of the asssignment is an expression or a variable (which we don't evaluate)
	defaultValExpr = '?e'
	defaultValVar = '?v'

	if inputfile.find(".cpp") != -1:
		isCpp = True;
	elif inputfile.find(".c") != -1:
		isCpp = False
	else:
		sys.exit(error + "file " + inputfile + " is of the wrong format.")


	try:
		with open(inputfile, "r") as fr:
			#text2 = fr.readlines()
			text = fr.readlines()
			fr.close()
	except Exception:
		sys.exit(error + "file " + '"' + inputfile + '"' + " not found")

	#Tracks the index at which the "main" is defined
	#This poses a limitation: the program ignores everything in the AST before the main, therefore-
	#-all functions, variables, etc.. must be defined AFTER the main.


	fileName = inputfile.replace('_ast.txt', '')
	fileNameTemp = fileName.split('/')[-1]
	text = findSource(text, fileNameTemp)

	#Remove everything until main
	'''
	for l in text2:
		mainCount = mainCount + 1
		if l.find(' main ') != -1:
			break
	'''

	#text = text2[mainCount-1:]

	assignmentList = []
	GV = []
	subList = []
	address = ""
	varName = ""
	varType = ""
	lineNumber = ""
	lineNumberDecl = ""
	rValue = ""
	rightValFlag = False
	count = 1
	listCount = -1
	lineRange = ('0', '-1')
	

	callLine = -1
	strcpyCall = False	
	strcpyVal = False
	declCallFlag = False
	declLvalFlag = False
	declRvalFlag = False

	for line in text:
		temp = ""

#-----------------------------StrCpy--------------------------------------#
		#Find the line of the call number 
		if line.find('CallExpr') != -1:
			tempLine = line.split()
			for index in tempLine:
				if (index.find('<') != -1):
					if index.find(':') != -1:
						index = colonRemoverAfter(index)
					if index.find(':') != -1:
						index = colonRemoverBefore(index)
					index = index.strip('<')
					callLine = index
			
		if line.find('-DeclRefExpr') != -1 and line.find('strcpy') != -1:
			strcpyCall = True
			declLvalFlag = True
			declRvalFlag = True
		
		#[... '<col:9>', "'char", "[20]'", 'lvalue', 'Var', '0x30b95f8', "'arr'", "'char", "[20]'"]

		if strcpyCall and line.find('-DeclRefExpr') != -1 and line.find('lvalue') != -1 and declLvalFlag:
			tempLine = line.split()
			varName = tempLine[-3]
			varName = varName.strip("'")
			declLvalFlag = False
			continue			


	
		if strcpyCall and line.find('Literal') != -1 and declRvalFlag:
			tempLine = line.split()
			varVal = tempLine[-1]
			strcpyCall = False
			strcpyVal = False	
			lineRangeTemp = lineRange
			if (int(callLine) > int(lineRange[1])) or varName in GV:
				lineRangeTemp = ('0', '-1')
			
			varVal = varVal.strip('"')	
			subList = [callLine, varName, lineRangeTemp, varVal]
			assignmentList.append(subList)
			declRvalFlag = False
			
		if strcpyCall and line.find('-DeclRefExpr') != -1 and line.find('lvalue') != -1 and line.find('Var') != -1 and declRvalFlag:
			tempLine = line.split()
			varVal = '?v'
			strcpyCall = False
			strcpyVal = False	
			lineRangeTemp = lineRange
			if (int(callLine) > int(lineRange[1])) or varName in GV:
				lineRangeTemp = ('0', '-1')
			

			subList = [callLine, varName, lineRangeTemp, varVal]
			assignmentList.append(subList)	
			declRvalFlag = False
		
#------------------------------------------------------------------------#



		#Find function declerations (for scope)
		#ex: |-FunctionDecl 0x7fd14c824938 <test.c:1:1, line:10:1> line:1:5 main 'int ()'
		if line.find('FunctionDecl') != -1:
			tempLine = line.split()

			startLine = '0'
			endLine = '-1'

			for index in tempLine:
				startCount = 0

				if index.find('line:') != -1 and index.find('<') != -1:
					#This is the startLine
					startLine = index
					startCount = 1


				elif index.find('line:') != -1 and index.find('>') != -1:
					#This is the endLine
					endLine = index

				elif index.find('line:') != -1 and startCount == 0:
					#This is the startLine
					startLine = index



			colonCount = 0

			
			#Get rid of first colon
			if startLine.find(':') != -1:
				startLine = colonRemoverAfter(startLine)
			if startLine.find(':') != -1:	
				startLine = colonRemoverBefore(startLine)

			if endLine.find(':') != -1:
				endLine = colonRemoverAfter(endLine)
			if endLine.find(':') != -1:
				endLine = colonRemoverBefore(endLine)


			lineRange = (startLine, endLine)
		
		#Find the line number of all decleration statements, initialized or not
		#Ex: |-DeclStmt 0x7fd14c876ad0 <line:2:2, col:11>
		if line.find('DeclStmt') != -1:

			colonCount = 0

			tempLine = line.split()
			#We always index from the end because of the AST structure (a tree where levels are represented by spaces)
			cut1 = tempLine[-2]

			for index in cut1:
				colonCount = colonCount + 1
				if (index == ':'):
					break
		
			cut2 = cut1[colonCount:]		

			for index in cut2:
				if (index == ':'):
					break

				
				temp += index
			lineNumberDecl = temp





		#Looks for an = sign, but only in the contex of an assignment 
		#ex: | `-BinaryOperator 0x7fd14c876bb8 <line:4:3, col:7> 'int' '='
		if ((line.find('BinaryOperator') != -1) and (line.find('=') != -1) and (line.find('==') == -1) and (line.find('>=') == -1) and (line.find('<=') == -1) and (line.find('!=') == -1)):

			#Count tells us to expect to find a line in the AST with lvalue information
			count = 0


			#rightValFlag tells us that we need to look for a right value down the line
			rightValFlag = True

			#Get line number
			cut1 = line.split()
			
			'''
			#For C
			if isCpp == False:
				cut2 = cut1[-4]

			#For C++
			else:
				cut2 = cut1[-5]
			
			
			cut3 = cut2[6:]


			#Get

			for index in cut3:
				if (index == ':'):
					break

				
				temp += index


			lineNumber = temp
			'''
			for index in cut1:
				if (index.find('<') != -1) and index.find('line') != -1:
						if index.find(':') != -1:
							index = colonRemoverAfter(index)
						if index.find(':') != -1:
							index = colonRemoverBefore(index)
						index = index.strip('<')
						lineNumber = index

		
			

		#For ++ and -- (as opposed to x = x + 1)
		if ((line.find('UnaryOperator') != -1) and ((line.find('++') != -1) or (line.find('--') != -1)) or (line.find('+=') != -1) or (line.find('-=') != -1)):
			count = 0

			if line.find('line') != -1:
				tempLine = line.split()
				'''
				#get line number
				cut1 = line.split()


				cut2 = cut1[-5]

				

			
				cut3 = cut2[6:]

				for index in cut3:
					if (index == ':'):
						break

				
					temp += index
				'''		
	
				for index in tempLine:
					if (index.find('<') != -1):
						if index.find(':') != -1:
							index = colonRemoverAfter(index)
						if index.find(':') != -1:
							index = colonRemoverBefore(index)
						index = index.strip('<')
						lineNumber = index


				#lineNumber = temp
				rValue = '?e'
					
		#Extracting string lineNumber
		if line.find('CXXOperatorCallExpr') != -1 and line.find('string') != -1 and line.find('line') != -1:
			tempLine = line.split()
			for index in tempLine:
				if (index.find('<') != -1) and index.find('line') != -1:
					if index.find(':') != -1:
						index = colonRemoverAfter(index)
					if index.find(':') != -1:
						index = colonRemoverBefore(index)
					index = index.strip('<')
					lineNumber = index

			#DeclRefExpr is referring to an assignment
		#ex: | `-DeclRefExpr 0x7fd14c876ae8 <col:6> 'int' lvalue Var 0x7fd14c876a50 'x' 'int'
		#Since count is 0, this line is expected and useful (this is where we get the lvalue info from). Otherwise, we ignore it.
		if ((line.find('-DeclRefExpr') != -1) and ((count == 0) or (line.find('string') != -1 and line.find('Var') != -1))):
			count = 1
			rightValFlag = True

			#Get address, variable name, and variable type
			tempLine = line.split()


			#address = tempLine[-3]

			if line.find('string') != -1:
				varName = tempLine[-3]
				varName = varName.strip("'")
			else:
				#First find Var, then use that as reference to index
				nameCount = -2
				for index, i in enumerate(tempLine):
					if i.find('Var') != -1:
						nameCount = index
			
				varName = tempLine[nameCount + 2]
				varName = varName.strip("'")	

			varType = tempLine[-1]
			varType = varType[1:-1]

			#subList = [lineNumber, varName, address, varType, '0']
			#^ Depending on what information we want the assignment collector to return

			lineRangeTemp = lineRange
			
			if lineNumber != '' and ((int(lineNumber) > int(lineRange[1])) or varName in GV):
				lineRangeTemp = ('0', '-1')
		
			subList = [lineNumber, varName, lineRangeTemp, '?']

			if lineRangeTemp == ('0', '-1'):
				GV.append(varName)
	
			assignmentList.append(subList)
			
			listCount = listCount + 1

			#find r
			rValue = "0"
			rVal = 1

		
			


		if (line.find('VarDecl') != -1 and line.find('used') != -1) and lineNumberDecl == '': 
			tempLine = line.split()
			nameIndex = 0
			for i in tempLine:
				nameIndex = nameIndex + 1
				if i.find('used') != -1:
					break
			
			tempName = tempLine[nameIndex]
			GV.append(tempName)


			
		#filter for decleration statements with initializations
		#ex: | `-VarDecl 0x7fd14c876a50 <col:2, col:10> col:6 used x 'int' cinit

		if (line.find('VarDecl') != -1 and line.find('cinit') != -1):
			
			rightValFlag = True

			tempLine = line.split()

			#To account for differences in 'VarDecl' line in AST
			count = 1
			for VarDecl in tempLine:
				if VarDecl == '`-VarDecl':
					break
				else:
					count = count + 1

			
			
			#address = tempLine[count]
			lineNumber = lineNumberDecl
			check = 0

			#See if line number appears here
			if line.find('line') != -1 or line.find(fileName) != -1:
				for i in tempLine:
					if '<' in i:
						lineNumber = colonRemoverAfter(i)
						lineNumber = colonRemoverBefore(lineNumber)




			for i in tempLine:
				if ('[' in i and ']' in i) or (line.find('string') != -1):
					check = 1
					
			if check == 1:
				varName = tempLine[-4]
			else:
				#Find var type using ' ', then find element before in tempLine just before
				nameCount = 0
				for i in tempLine[::-1]:
					if i.find("'") != -1:
						nameCount = nameCount + 1
				varName = tempLine[-(nameCount + 2)]
				#varName = tempLine[-3]

			varType = tempLine[-2]
			varType = varType[1:-1]

		
			#subList = [lineNumberDecl, varName, address, varType, '0']
			lineRangeTemp = lineRange
			
			if lineNumber != '' and ((int(lineNumber) > int(lineRange[1])) or varName in GV):
				lineRangeTemp = ('0', '-1')


			subList = [lineNumber, varName, lineRangeTemp, '?']
			if lineRangeTemp == ('0', '-1'):
				GV.append(varName)

			assignmentList.append(subList)
			listCount = listCount + 1
			
			
		if rightValFlag == True and line.find('=') == -1 and line.find('BinaryOperator') != -1:

			subLength = len(assignmentList[len(assignmentList)-1])
			if assignmentList[len(assignmentList) - 1][subLength - 1] == '?':
				assignmentList[len(assignmentList) - 1][subLength - 1] = defaultValExpr
			rightValFlag = False
			

		if rightValFlag == True and line.find('<LValueToRValue>') != -1:
			subLength = len(assignmentList[len(assignmentList)-1])
			if assignmentList[len(assignmentList) - 1][subLength - 1] == '?':
				assignmentList[len(assignmentList) - 1][subLength - 1] = defaultValVar

			rightValFlag = False



		#To find the value being assigned to a variable
		#ex:  `-IntegerLiteral 0x7fd14c876e28 <col:10> 'int' 12
		#This is the interperatation portion. It is seperate from the assignment collection portion
		if line.find('Literal') != -1 and rightValFlag == True:
			rightValFlag = False
			tempLine = line.split()
			endIndex = len(tempLine)
			rValue = tempLine[endIndex - 1]
			rValue = rValue.strip('"')
			if varType == 'char':
				tempVal = int(rValue)
				rValue = chr(tempVal)

			subLength = len(assignmentList[len(assignmentList)-1])
			assignmentList[len(assignmentList) - 1][subLength - 1] = rValue	
			
		
	return assignmentList
	

def writeCSV(assignmentList, fileName):
	error = "MLSA: CAssignmentCollector "

	try:	
		with open(fileName, 'w') as ofile:
			writer = csv.writer(ofile)	
			writer.writerows(assignmentList)
	except Exception:
		sys.exit(error + "file " + '"' + 'test' + '"' + " could not be written")



#print AssignmentCollector("test.cpp_ast.txt")

def main(inputFile, outputFile):
	assignmentList = AssignmentCollector(inputFile)
	writeCSV(assignmentList, outputFile)

#main('Ctable.c_ast.txt', 'Ctable.c_vars.csv')
