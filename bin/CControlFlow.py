import csv
import sys
from collections import OrderedDict

#Definition for AST node class
class ASTEntry(object):
	def __init__(self):
		self.typeString = ""	
		self.uniqueID = ""		
		self.lineNum = -1		
		self.treeLevel = -1		
		self.children = []		
		self.parent = None 		
		self.index = -1	
		#If statments
		self.hasElseStmt = False	
		self.isElseStmt = False


		self.conditional = False
		self.conditionalType = ""
		self.lastChild = False	


def getInput(inputfile):
	error = "MLSA: CControlFlow "
	try:
		with open(inputfile, "r") as txtFile:
			treeLines = txtFile.readlines()
			txtFile.close()
	except Exception:
		sys.exit(error + "file " + '"' + inputfile + '"' + " not found")

	return treeLines



def getSource(treeLines, inputfile):
	treeList = []

	#Strip _ast.txt
	fileName = inputfile.replace('_ast.txt', '')
	fileName = backslashRemoverAfter(fileName)

	fileFound = False
	firstFound = False
	
	for line in treeLines:
		if line.find('<') != -1 and line.find('>') != -1 and (line.find('.c') != -1 or line.find('.cpp') != -1 or line.find('.h') != -1):
			tempLine = line.split()
			for index in tempLine:
				if index.find('<') != -1 and (index.find('.c') != -1 or index.find('.cpp') != -1 or index.find('.h') != -1):

					index = colonRemoverBefore(index)
					index = backslashRemoverAfter(index)
					index = index.strip('<')
					if index == fileName:
						fileFound = True
						firstFound = True
					else:
						fileFound = False
		
		if fileFound or (line.find('CallExpr') != -1 and firstFound):
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

#Returns the part of the string BEFORE the colon
def colonRemoverBefore(text):
	colonCount = 0
	for index in text:
		colonCount = colonCount + 1
		if (index == ':'):
			break
	text = text[:colonCount - 1]
	return text

def prettyPrint(body):
	for i in body:
		print i

def GetTreeLevel(text):
	spaceCount = 0

	for character in text:
		if (character == '-'):
			break;
		else:
			spaceCount = spaceCount + 1

	return (spaceCount - 1)/2 #spaceCount will always be odd, this changes it to the whole numbers 


def getNodeList(astList):
	nodeList = []
	parentList = []
	treeList = []

	for index, line in enumerate(astList):
		astItem = ASTEntry()
		stringIndex = -1
		lineList = line.split()

		#Find astList index---
		astItem.index = index
		#----------------------

		#Find typeString-------------------------------
		for nodeIndex, element in enumerate(lineList):
			if element.find('-') != -1 and (element.find('`') != -1 or element.find('|') != -1):
				typeString = element.split('-')[1]
				stringIndex = nodeIndex
		astItem.typeString = typeString
		#----------------------------------------------

		#Find unique ID: it appears after the typeString -------
		if (len(lineList) > stringIndex + 1):
			astItem.uniqueID = lineList[stringIndex + 1]
		#--------------------------------------------------------

		#Find treeLevel----------------
		treeLevel = GetTreeLevel(line)
		astItem.treeLevel = treeLevel
		#------------------------------


		#Find parent-----------------------

		#Tells us which node at the parent level we're looking at (building parentList)
		if len(parentList) < (astItem.treeLevel + 1):
			parentList.append(index)
		else:
			parentList[treeLevel] = index

		#If it's the root node, there is no parent
		if astItem.treeLevel == 0:
			astItem.parent = None
			treeList.append(astItem)
		#Otherwise, we find the parent using its level and parentList
		else:
			parentLevel = astItem.treeLevel - 1
			parent = nodeList[parentList[parentLevel]]
			parent.children.append(astItem)
			astItem.parent = parent
		#------------------------------------
			
		#Find line number (if it exists) --> Maybe do this AFTER parent/child info is filled out

		nodeList.append(astItem)

	return nodeList, treeList

def printTree(rootNode):
	if rootNode != None:
		print rootNode.typeString, '\t|\t', rootNode.uniqueID
		for i in rootNode.children:
			printTree(i)


def getNextSibling(currNode):
	parent = currNode.parent
	currNodeCheck = False
	nextSibling = None
	if (parent != None):
		for child in parent.children:
			if currNodeCheck and child.typeString.find('NULL') == -1:
				nextSibling = child
				break
			if child == currNode:
				currNodeCheck = True

	return nextSibling
	
def getFirstNonNullChild(currNode):
	for child in currNode.children:
		if child.typeString.find('NULL') == -1:
			return child


def setConditional(currNode, conditionalType):
	for child in currNode.children:
		if child.typeString.find('NULL') == -1:
			child.conditional = True
			child.conditionalType = conditionalType
			return child

def setLastChild(currNode):
	for child in currNode.children[::-1]:
		if (child.typeString.find('NULL') == -1 and child.isElseStmt == False):
			child.lastChild = True
			return child

def getElseStmt(currNode):
	for child in currNode.children:
		if child.isElseStmt == True:
			return child

def getConditionalParent(currNode):

	if currNode == None:
		return None

	elif currNode.conditional == True:
		#print 'Conditional: ', currNode.typeString
		return currNode

	else:
		if currNode.parent != None:
			for child in currNode.parent.children:
				if child.conditional == True:
					return child
			return getConditionalParent(currNode.parent)

def getNonCompoundParent(currNode):
	if currNode == None:
		return None
	else:
		if currNode.parent != None and currNode.parent.typeString != 'CompoundStmt':
			return currNode.parent
		else:
			return getNonCompoundParent(currNode.parent)


forwardFlow = []
visitedList = []

def getForwardFlow(rootNode):
	currNode = rootNode
	tempList = [currNode.uniqueID]
	nextList = []

	if currNode not in visitedList:

		visitedList.append(currNode)

		if currNode.typeString == 'FunctionDecl' and len(currNode.children) > 0:
			nextList.append(currNode.children[0])
			#nextNode = currNode.children[0]



		#If statements-----------------------------------------------------------------------------
		elif currNode.typeString == 'IfStmt':
			nextList.append(setConditional(currNode, 'If'))

			#Check for else:
			if currNode.children[-1].typeString.find('NULL') == -1:
				currNode.hasElseStmt = True
				currNode.children[-1].isElseStmt = True
				setLastChild(currNode)
		
		#For conditionals
		elif (currNode.conditional == True and currNode.parent.typeString == 'IfStmt'):
			nextList.append(getNextSibling(currNode))
			if currNode.parent.hasElseStmt == False:
				nextList.append(getNextSibling(currNode.parent))
			else:
				nextList.append(getElseStmt(currNode.parent))


		#For last child in if
		elif (currNode.lastChild == True and currNode.parent.typeString == 'IfStmt' and currNode.typeString != 'CompoundStmt'):
			nextList.append(getNextSibling(currNode.parent))

		elif (currNode.isElseStmt and currNode.typeString != 'CompoundStmt'):
			nextList.append(getNextSibling(currNode.parent))

		#-----------------------------------------------------------------------------------------


		#While statements--------------------------------------------------------------------------
		elif currNode.typeString == 'WhileStmt':
			nextList.append(setConditional(currNode, 'While'))
			setLastChild(currNode).typeString



		elif currNode.conditional == True and currNode.parent.typeString == 'WhileStmt':
			nextList.append(getNextSibling(currNode))
			
			
			if currNode.parent.lastChild == True:
				conditionalParent = getConditionalParent(currNode.parent)
				if conditionalParent != None:
					if (conditionalParent.conditionalType == 'While'):
						nextList.append(conditionalParent)
					else:
						nextList.append(getNextSibling(currNode.parent))
				else:
					nextList.append(getNextSibling(currNode.parent))

			else:
				nextList.append(getNextSibling(currNode.parent))
					
				
				
				


		elif currNode.lastChild == True and currNode.parent.typeString == 'WhileStmt' and currNode.typeString != 'CompoundStmt':
			#Go back to the conditional
			nextList.append(getConditionalParent(currNode))

		#------------------------------------------------------------------------------------------


		#Compound statements-----------------------------------------------------------------------
		elif currNode.typeString == 'CompoundStmt':
			nextList.append(currNode.children[0])
			setLastChild(currNode).typeString
			
			

		elif currNode.lastChild == True and currNode.parent.typeString == 'CompoundStmt':

			nonCompoundParent = getNonCompoundParent(currNode)
	
			if nonCompoundParent.typeString == 'FunctionDecl':
				nextList.append(None)
			elif nonCompoundParent.typeString == 'WhileStmt':
				nextList.append(getConditionalParent(currNode.parent))
			elif nonCompoundParent.typeString == 'IfStmt':
				if nonCompoundParent.lastChild == True:
					if getNonCompoundParent(nonCompoundParent).typeString == 'WhileStmt':
						nextList.append(getConditionalParent(nonCompoundParent))
					else:
						nextList.append(getNextSibling(nonCompoundParent))
				else:
					nextList.append(getNextSibling(nonCompoundParent))
			else:
				nextList.append(getNextSibling(nonCompoundParent))


		#-----------------------------------------------------------------------------------------



		else:

			nextList.append(getNextSibling(currNode))
			#nextNode = getNextSibling(currNode)

		#Go through next list and update temp
		for nextNode in nextList:
			if nextNode == None:
				tempList.append(None)
			else:
				tempList.append(nextNode.uniqueID)

		forwardFlow.append(tempList)
	

		for nextNode in nextList:
			if nextNode != None:
				getForwardFlow(nextNode)



def getReverseFlow(forwardFlow):
	reverseDict = OrderedDict()
	for subList in forwardFlow:
		#Pick out the first node of the sublist and check if it's in the dict
		prevNode = subList[0]
		if prevNode not in reverseDict:
			reverseDict[prevNode] = []
		if len(subList) > 1:
			for element in subList[1:]:
				if element == None:
					continue
				elif element not in reverseDict:
					reverseDict[element] = [prevNode]
				else:
					reverseDict[element].append(prevNode)
	
	#Convert to list:
	reverseFlow = []
	for key in reverseDict:
		subList = []
		subList.append(key)
		for item in reverseDict[key]:
			subList.append(item)

		#print subList
		reverseFlow.append(subList)
	#print reverseFlow
	return (reverseFlow)

def writeCSV(fcfgFile, rcfgFile,forwardFlow, reverseFlow):
	error = "MLSA: CControlFlow "
	try:	
		with open(fcfgFile, 'w') as wfile:
			writer = csv.writer(wfile)	
			writer.writerows(forwardFlow)
	except Exception:
		sys.exit(error + "file could not be written")

	try:	
		with open(rcfgFile, 'w') as ofile:
			writer = csv.writer(ofile)	
			writer.writerows(reverseFlow)
	except Exception:
		sys.exit(error + "file could not be written")



#-------------------MAIN--------------------------#



def main(inputFile, fileName, fcfgFile, rcfgFile):
	astLines = getInput(inputFile)
	astList = getSource(astLines, inputFile)
	nodeList, treeList = getNodeList(astList)

	for i in treeList:
		getForwardFlow(i)


	reverseFlow = getReverseFlow(forwardFlow)
	writeCSV(fcfgFile, rcfgFile, forwardFlow, reverseFlow)
	




	
#main("test.c_ast.txt", 'test.c', 'test.c_fcfg.csv', 'test.c_rcfg.csv')








