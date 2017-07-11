# Jun 15, 2016
# Author: Bruno Sergio Cardoso Vieira
# Project MLSA

# This program runs through a CLANG dumped AST file getting information about function declarations

import os
import re 	# imported to use "search" method in strings
import sys

class GraphNode():	# holds the information about a call. It is the node to the callgraph
	def __init__(self, line, callee, called):
		self.line = line
		self.callee = callee
		self.called = called

class Call():		# holds the information of the call of a function, with its name, the line it was called, the number of arguments and a list of the arguments used
	def __init__(self, line, callee, function, nArgs, args):
		self.callee = callee
		self.function = function
		self.line = line
		self.nArgs = nArgs
		self.args = args

class Argument():	# holds the information of an argument of a function, with its name (variable), kind (variable / constant), type and value (constant)
	def __init__(self, name, typ, kind, value):
		self.name = name
		self.kind = kind
		self.type = typ
		self.value = value

class Function(): 	# holds the information of a declared function, with its name, signature, return type, whether it is used or not, a list of calls, number of parameters and a list of their types
    def __init__(self, name, signature, returnType, used, calls, numberOfParameters, parameters):
		self.name = name
		self.signature = signature
		self.returnType = returnType
		self.used = used
		self.calls = calls
		self.numberOfParameters = numberOfParameters
		self.parameters = parameters

# function that prints the table with the current results in listOfFunctions
def printTable(listOfFunctions):
	# printing a table with the information collected
	counter = 0
	for f in listOfFunctions:
		if(f.used == "True"):
			counter = counter + 1
			print("\n\nFunction Name: " + f.name)
			print("Signature: " + f.signature)
			print("Return Type: " + f.returnType)
			print("Number of Parameters: " + str(f.numberOfParameters))
			if(f.numberOfParameters != "undefined"):
				print("\n - Types: ")
				for i in range(0,f.numberOfParameters):
					print(" --- " + f.parameters[i])
			print("\nUsed: " + f.used)
			print("Calls: ")
			for call in f.calls:
				print("\n - Line: " + call.line + " from " + call.callee)
				if(not(f.numberOfParameters == "undefined" or f.numberOfParameters == 0)):
					print(" - Arguments: ")
					print(" --- \tKind\t\tName\t\tType\t\t\tValue")
					for arg in call.args:
						print(" --- \t" + arg.kind + "\t" + arg.name + "\t\t" + arg.type + "\t\t\t" + arg.value)
			print("-----------------------------------------------------------------------------------------")
	print("\n\n Result: " + str(len(listOfFunctions)) + " functions found (including headers)")
	print(" Used: " + str(counter) + " functions being used")

	return

# function that prints the list of nodes in the graph
def printGraph(graph):
	print("\n\n*******************************************")
	print("Number of Calls: " + str(len(graph)))
	for node in graph:
		print(node.line + " - " + node.callee + "\t->\t" + node.called)

	return

# function that generates the csv output file for the list of functions 
def saveGraph(listOfFunctions):
	global program
	f = open(program+"_func.csv", "w")
	for func in listOfFunctions:
		if(func.used == "True"):
			for call in func.calls:
				string = call.callee + ", " + func.name
				if(func.numberOfParameters != "undefined"):				
					for arg in call.args:
						if(arg.kind == "Variable"):							
							found = arg.type.find("char")
							if(found == -1):
								string = string + ", " + arg.name
							else:
								string = string + ", \"" + arg.name + "\""
						elif(arg.kind == "Literal"):							
							found = arg.type.find("char")
							if(found == -1):
								string = string + ", " + arg.value
							else:
								string = string + ", \"" + arg.value + "\""
						elif(arg.kind == "Function"):
							string = string + ", \'" + arg.name + "\'"						
						else:
							string = string + ", " + arg.kind.upper()
				else:
					string = string + ", " + "undefined n of arguments"
					
				string = string + "\n"
				f.write(string)
	f.close()
	return


# function that returns the name of the function called
def getFunctionName(currentLine):

	# look for the function name reference (running through next lines)
	lineSearch = fileLines[currentLine]
	found = lineSearch.find(stringFunction)
	if(found == -1):
		noFunctionFound = lineSearch.find(" '")
		

	while(found == -1):
		currentLine = currentLine + 1
		lineSearch = fileLines[currentLine]
		found = lineSearch.find(stringFunction)
	
	# getting the name of the function called
	foundName = lineSearch.find("' '")
	k = foundName - 1
	name = ""
	while(lineSearch[k] != "'"):
		name = name + lineSearch[k]
		k = k - 1
	name = name[::-1]

	return name

# function that returns the line in which the function was called
def getLineCall():
	global currentLine

	found = line.find(lineValue) # <line:
	if(found == -1):	# the call is nested in other expressions
		j = currentLine
		while(found == -1):		# runs back through the lines to find in which line the function was called
			j = j - 1	
			lineSearch = fileLines[j]
			found = lineSearch.find(lineValue)
		
		lineCall = lineSearch 
	else:
		lineCall = line
	
	# lineCall holds the line with the call information (line information)
	lineCalled = ""
	k = found + 7
	while(lineCall[k] != ':'): # copies the number of the line in which the function was called
		lineCalled = lineCalled + lineCall[k]
		k = k + 1

	return lineCalled


# function that anaylizes a function call (get name, arguments) - used recursively to handle nested calls
def analyzeFunctionCall(callee):
	global currentLine
	global graph
        nArguments = "undefined"  # dml 6/6/17 added as fix for CPP error

	lineString = fileLines[currentLine]

	lineCalled = getLineCall()			
	name = getFunctionName(currentLine)

	graph.append(GraphNode(lineCalled,callee, name))

	# add the line to the right functions in the list
	counted = False
	k = 0
	nOfFunctions = len(listOfFunctions)
	while((k < nOfFunctions) and (not counted)):
		f = listOfFunctions[k]
		if(name.lower() == f.name.lower()):
			counted = True					
			nArguments = f.numberOfParameters
		k = k + 1

	args = []
	nameCalled = ""
	if(nArguments !=  "undefined"):
		# get function arguments
		countedArguments = 0
		arrayCount = 0
		memberName = ""
		while(countedArguments < nArguments): # iterates to find all arguments

			currentLine = currentLine + 1
			#print("/////////////////////////" + str(currentLine+1))
			lineSearch = fileLines[currentLine]


			# tries to find an expression
			found = lineSearch.find(stringOperator) # Operator ("-BinaryOperator ")
			if(found != -1): 
				argKind = "Expression"
				argValue = "*****"
				argType = f.parameters[countedArguments]
				argName = "*****"
			
				ops = 2	# initial number of operators to find
				found = 1
				while(ops != 0):
					currentLine = currentLine + 1
					#print("*************************************"+ str(currentLine+1))
					lineSearch = fileLines[currentLine]

					found1 = lineSearch.find(stringVariable) # finds a Variable (" Var ")
					found2 = lineSearch.find(litExp) # finds a literal
					found3 = lineSearch.find("sizeof")
					if((found1 != -1) or (found2 != -1) or (found3 != -1)):
						ops = ops - 1	# decrease remaining operators to find
				
					else:
						found = lineSearch.find(stringOperator) # nested operators
						if(found != -1):
							ops = ops + 1	# increase remaining operators to find
						else:
							found = lineSearch.find(funcCall)
							if(found != -1):	# argument is a function
								analyzeFunctionCall(callee)
								ops = ops - 1	# decrease remaining operators to find

				# adds the variable to the list of arguments
				args.append(Argument(argName, argType, argKind, argValue))
				countedArguments = countedArguments + 1

			else: 

				found = lineSearch.find(stringVariable) # tries to find a variable argument (" Var ")
				if(found != -1): # this line is a variable argument
					argKind = "Variable"
					argValue = "*****"
			
					argType = f.parameters[countedArguments]
					argName = ""
			
					# gets the name of the variable
					found = lineSearch.find("' '")
					aux = found - 1
					while(lineSearch[aux] != "'"):
						argName = argName + lineSearch[aux]
						aux = aux - 1
					argName = argName[::-1]

					isStruct = lineSearch.find(stringStruct) # tries to find ("'struct ")
					if(isStruct != -1): 	# it is a struct
						argName = argName + memberName
						memberName = "" # reset the temporary variable
					if(arrayCount != 0):
						while(arrayCount != 0):
							currentLine = currentLine + 1
							lineSearch = fileLines[currentLine]
							searchObj = re.search("> 'int' (.*)", lineSearch);
                                                        if (searchObj):
                                                                index = searchObj.group(1);
                                                                argName = argName + "[" + index + "]"
                                                                arrayCount = arrayCount - 1

					# adds the variable to the list of arguments
					args.append(Argument(argName, argType, argKind, argValue))
					countedArguments = countedArguments + 1

				else: # tries to find a literal
					found = lineSearch.find(litExp)
					if(found != -1): # this line is a literal argument
						argName = "*****"
						argKind = "Literal"

						argType = f.parameters[countedArguments]
						argValue = ""

						# gets the value of the variable
						isString = lineSearch.find(stringLiteral)
						if(isString == -1): 	# any Literal but string
							found = lineSearch.rfind("'")
							aux = found + 2
							argValue = lineSearch[aux:]

						else:					# string literal
							argValue = re.search("\"(.*)\"", lineSearch).group(1)

						# adds the constant to the list of arguments
						args.append(Argument(argName, argType, argKind, argValue))
						countedArguments = countedArguments + 1

					else: # tries to find a function
						found = lineSearch.find(funcCall)
						if(found != -1): # this line is a function argument

							found = line.find(lineValue) # <line:
							if(found == -1):	# the call is nested in other expressions
								j = currentLine
								while(found == -1):		# runs back through the lines to find in which line the function was called
									j = j - 1	
									lineSearch = fileLines[j]
									found = lineSearch.find(lineValue)
	
								lineCall = lineSearch 
							else:
								lineCall = line

							# lineCall holds the line with the call information (line information)
							lineCalled = ""
							k = found + 7
							while(lineCall[k] != ':'): # copies the number of the line in which the function was called
								lineCalled = lineCalled + lineCall[k]
								k = k + 1	
		
							# look for the function name reference (running through next lines)
							found = -1
							j = currentLine
							while(found == -1):
								j = j + 1
								lineSearch = fileLines[j]
								found = lineSearch.find(stringFunction)

							# getting the name of the function called
							foundName = lineSearch.find("' '")
							k = foundName - 1
							argName = ""
							while(lineSearch[k] != "'"):
								argName = argName + lineSearch[k]
								k = k - 1
							argName = argName[::-1]

							argType = f.returnType
							argKind = "Function"
							argValue = "*****"
							
							analyzeFunctionCall(callee)

							args.append(Argument(argName, argType, argKind, argValue))
							countedArguments = countedArguments + 1

							currentLine = currentLine + 1
						
						else:
							found = lineSearch.find(stringMember)	# (" -MemberExpr" )
							if(found != -1):
                                                                searchObj = re.search("' lvalue (.*) 0x", lineSearch)
                                                                if (searchObj):
                                                                        memberName = searchObj.group(1) + memberName	# concatenate nested struct members until a Variable is found

							else:
								found = lineSearch.find(stringArray)	# ("-ArraySubscriptExpr")
								if(found != -1):
									arrayCount = arrayCount + 1
								
								

		# endWHILE counting arguments
	
	if(f.calls == [] and f.used == "False"):
		f.used = "True"
	f.calls.append(Call(lineCalled, callee, name, nArguments, args)) # add the call to the function
	return

fileLines = []
nOfLines = 0
i = 0
currentLine = 0

programName = ""


funcDecl = "-FunctionDecl"			# token to look for a Function Declaration
funcCall = "-CallExpr"				# token to look for a Call Expression
refExp = "-DeclRefExpr"				# token to look for a Reference to a function or an argument
litExp = "Literal "					# token to look for a Literal to an argument of a function
paramDecl = "-ParmVarDecl"			# token to look for a Parameter Declaration
lineValue = " <line:"				# token to look for the number of the line in which the function was called
stringUsed = " used "				# token to look for the Used flag within a line
stringFunction = " Function "		# token to look for the Function flag within a line
stringVariable = "Var "				# token to look for the Var flag within a line
stringLiteral = "-StringLiteral "	# token to look for the declaration of a String Literal (constant)
stringOperator = "-BinaryOperator "	# token to look for an Operator (Binary / Unary)
stringStruct = "'struct "			# token to look for a struct used as an argument
stringMember = "-MemberExpr "		# token to look for a member of a struct as argument for a function
stringLvalue = " lvalue "			# token to look for a logical value (used in struct member arguments)
stringArray = "-ArraySubscriptExpr"	# token to look for an array as an argument

listOfFunctions = []		# holds the list of declared functions (initialized as empty)
listOfCalls = []			# holds the list of functions calls (initialized as empty)
graph = []					# holds the list of nodes for the calls (initialized as empty)

# main processing
# open the file
if(len(sys.argv) != 2):
	print("Usage: python br-functionChecker program")
	print("-- where program is a C or a CPP program")
	exit(0)
else:
	program = str(sys.argv[1])
	astFile = program+"_ast.txt"
	os.system('clang-check-3.8 -ast-dump ' + program + ' --extra-arg="-fno-color-diagnostics" -- > ' + astFile)

	with open(astFile) as fileAST:

		fileString = fileAST.read()
		fileLines = fileString.split("\n")	# divide the file into lines
		nOfLines = len(fileLines)
		programName = fileLines[0]
		currentLine = 1
		while(currentLine < nOfLines):
			#print ("-----" + str(currentLine+1))
			line = fileLines[currentLine]
			found = line.find(funcDecl)		# looks for a function declaration
			if(found != -1):	# this line is a function declaration/definition
				#print("++" + str(currentLine+1))
				#auxiliar variables			
				signature = ""
				function = ""
				params = ""
				returnType = ""
				numberOfVariables = 0
				numberOfSpaces = 0
				used = "False"

				found = line.find(" prev ") 
				if(found == -1): # the function has not been added to the list of functions (function prototype)

					found = line.find(stringUsed) # checks if the function is being used
					if(found != -1):
						used = "True"
		
					signature = re.search("'(.*)'", line).group(1) # getting the signature of the function

					k = 0
					while(signature[k] != '('): # copies the return type of the function			
						returnType = returnType + signature[k]
						k = k + 1
					 

					j = line.find("'")	# finding the beginning of the return type of the function
					# copy the name of the function
					if(j != -1):
		
						j = j - 2
						while(line[j] != ' '):			
							function = function + line[j]
							j = j - 1

						# reversing the string
						function = function[::-1]
		
					# defining the number of parameters
					numberOfParams = signature.count(",")
					numberOfParams = numberOfParams + 1
					foundinf = line.find("...")
					foundnone = line.find("(void)")
		
					if(foundinf != -1):
						numberOfParams = "undefined"
					if(foundnone != -1):
						numberOfParams = 0

					# getting the types of the parameters
					j = signature.find('(')
					j = j + 1
					while(signature[j] != ')'):
						params = params + signature[j]
						j = j + 1
		
					args = params.split(', ')

					calls = []
					listOfFunctions.append(Function(function, signature, returnType, used, calls, numberOfParams, args))	# add the function to the list	

				else:
					j = line.find("'")	# finding the beginning of the return type of the function
					# copy the name of the function
					if(j != -1):
		
						j = j - 2
						while(line[j] != ' '):			
							function = function + line[j]
							j = j - 1

						# reversing the string
						function = function[::-1]

				foundNewDecl = -1 # found another function declaration (finished this one)
				nameCalled = ""
				while(foundNewDecl == -1 and (currentLine < nOfLines-1)):	# last function in the file doesn't find another function declaration
					currentLine = currentLine + 1
					#print("==========" + str(currentLine+1))
					line = fileLines[currentLine]
					foundNewDecl = line.find(funcDecl)	# update found
					if(foundNewDecl == -1):	# didn't find a function decl
						foundCall = line.find(funcCall)		# tries to find a function call
						if(foundCall != -1):
							analyzeFunctionCall(function)

			
			else:				
				currentLine = currentLine + 1

	
		#printTable(listOfFunctions)
		#printGraph(graph)	
		saveGraph(listOfFunctions)


