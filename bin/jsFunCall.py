# MLSA Multilingual Software Analysis
# This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
# jsFunCall.py takes in the JSON ast file generated by jsSA.py. The program walks through the JSON file to find all the function calls in the JavaScript program. The program also finds the scope of the call (if it is found inside another function definition or in the main body of the program), the class of the call (if it is a member function -> if not, class is GLOBAL), and the arguments of the call
# Author: Anne Marie Bogar
# Date: June 15, 2017
# this code can be copied or used and is without warrenty or support, but this header needs to be copied along with the program FU2017
# Input: JSON file of JavaScript program's ast
# Output: csv file
#		call_id(int),class(string),scope(string),function_name(string),argument1(string),argument2(string)...
# for arguments, all literals are encased in <> (ex: <5>) and all variables have their line number attached (ex: var-6)
# function calls that are arguments of another function call have their id next to () in csv line of the other function call
#               ex: 6,GLOBAL,file.py,function1,function2()4
# commas in list-type arguments are replaced with |
#               ex: [element1|element2|element3]
# Documentation for the SpiderMonkey JavaScript AST can be found here: https://developer.mozilla.org/en-US/docs/Mozilla/Projects/SpiderMonkey/Parser_API

import sys
import json
import csv

#global variables
error = "MLSA: jsFunCall; "

#problem: call inside an anonymous function
#problem: figure out how class is used in SpiderMonkey

#------------------------------Call Class--------------------------------#

class Call:
    def __init__(self, name, ID):
        self.name = name
        self.args = []
        self.scope = ''
        self.className = 'GLOBAL' #assume no class until class can be figured out
        self.ID = ID

    def setScope(self, scope):
        self.scope = scope

    def setClass(self, className):
        self.className = className

    #prints in CSV format -> id,class,scope,name,arg1,arg2...
    def printCall(self):
        retval = [self.ID, self.className, self.scope, self.name]
        return retval+self.args

    def setArgs(self, arglist):
        self.args = arglist

#------------------------------------------------------------------------#

#-----------------------------Walker Class-------------------------------#

class Walker:
    def __init__(self):
        self.callExpr = [] #keep track of function calls
        self.functionDecl = [] #keep track of function declarations

    def walkItem(self, path, key, item):
        if isinstance(item, list): # []
            for i, item1 in enumerate(item): #element number and item
                self.walkItem(
                    path=path + [key],
                    key=str(i),
                    item=item1
                ) #recursive -> walks all elements in a list
        elif isinstance(item, dict): # {}
            self.walk(path=path + [key], tree=item)
            Type = item.get('type', None) #get object "type", or return None
            if Type == 'CallExpression':
                #save call JSON object
                self.callExpr.append(item)
            if Type == 'FunctionDeclaration':
                #save function name and JSON object
                self.functionDecl.append((item.get('id').get('name'), item))
        else:
            pass
            #print '/' + '/'.join(path), key, item

    def walk(self, tree, path=[]):
        assert(isinstance(tree, dict))
        for k, v in tree.iteritems():
            self.walkItem(path=path, key=k, item=v)

#------------------------------------------------------------------------#

#-----------------------------Parser Class-------------------------------#

class Parser:
    def __init__(self, walker):
        self.walker = walker
        self.calls = walker.callExpr #all of the function call json objects from the ast
        self.final = [] #final list of Call objects for the csv file

    def parse(self, filename):
        for i, c in enumerate(self.calls):
            self.final.append(Call(self.getCallName(c), i)) #create Call object for particular function call
            self.final[-1].setArgs(self.getArgs(c)) #get arguments of the call
            self.final[-1].setScope(self.getScope(filename, c)) #get the scope or call (if inside function or body)

    def getScope(self, filename, callJSON):
        scope = filename #assume called in the main body of the program
        for a, b in self.walker.functionDecl:
            if str(callJSON) in str(b): #check if the call JSON object is found inside the function JSON object
                scope = a #called in a function definition
                break
        return scope

    def getCallName(self, c):
        name = ''
        if c.get('callee').get('type') == 'MemberExpression': #ex: classObj.memberFunction()
            name = 'OBJ.'+c.get('callee').get('property').get('name')
        else:
            name = c.get('callee').get('name')
        return name
    
    def parseArgs(self, item):
        global error
        #arg = argument variable, key = key variable (for dictionary), val = value variable (for dictionary)
        arg = key = val = ''
        #get the type of argument
        Type = item.get('type')
        if Type == 'Literal': #string or int
            #put <> around value to show it is a literal
            arg = '<'+str(item.get('value')).replace(',', '')+'>'
            if '\n' in str(arg):
                #\n could mess up csv file, so replace with \n
                arg = arg.replace('\n', '\\n')
        elif Type == 'Identifier': #variable
            arg = item.get('name')+'-'+str(item.get('loc').get('start').get('line')) #add the line number at the end (ex: var-6)
        elif Type == 'ArrayExpression': #array
            for e in item.get('elements'):
                #call parseArgs on all elements of the array
                arg = arg+self.parseArgs(e)+'|' #separate elements with |
            arg = '['+arg[:-1]+']'
        elif Type == 'ObjectExpression': #dictionary
            for p in item.get('properties'):
                #call parseArgs on all keys and values
                key = self.parseArgs(p.get('key'))
                val = self.parseArgs(p.get('value'))
                arg = arg+key+':'+val+'|' #separate key and value with :, separate elements with |
            arg = '{'+arg[:-1]+'}'
        elif Type == 'MemberExpression': #member variable or subscript
            arg = arg+self.parseArgs(item.get('object'))
            prop = self.parseArgs(item.get('property'))
            if item.get('property').get('loc') == None: #member variable
                arg = arg+'.'+prop
            else: #subscript
                arg = arg+'['+prop+']'
        elif Type == 'CallExpression': #function call
            arg = self.getCallName(item)
            for n, c in enumerate(self.calls): #get the arguments of the call (already in self.calls)
                if str(item) == str(c):
                    if self.final[n].args == []: #if no arguments, just add () to end of call name
                        arg = arg+'()'+str(n)
                    else:
                        arg = arg+'('+'~'.join(self.final[n].args)+')'+str(n) #include the arguments to the call name
        elif Type == 'BinaryExpression': #ex: 1+1
            arg = 'BinOp'
        elif Type == 'UnaryExpression': #ex: +3
            arg = 'UnOp'
        elif Type == 'FunctionExpression': #similar to lambda
            arg = 'AnonymousFunction'
        #argument type has not been identified -> send error message
        else:
            sys.exit(error+'argument type unidentified')
        return arg

    def getArgs(self, c):
        args = []
        for a in c.get('arguments'):
            #parse each argument in the function call
            args.append(self.parseArgs(a))
        return args

    #prints out all Call objects in final list to the CSV file
    def printToFile(self, csvFile):
        printable = []
        for f in self.final:
            #get call information in list form to print to csv
            printable.append(f.printCall())
        writer = csv.writer(csvFile)
        writer.writerows(printable)

    def getParamNum(self, function):
        args = function.get('params')
        num = len(args)
        return num

    def printFuncs(self, f, filename):
        functions = []
        for func in self.walker.functionDecl:
            functions.append([filename, 'GLOBAL', func[0], self.getParamNum(func[1])])
        writer = csv.writer(f)
        writer.writerows(functions)


#------------------------------------------------------------------------#

#-----------------------------Main Function------------------------------#

def main(astfile, jsfile, csvfile, funcfile):
    global error

    try:
        #JavaScript ast is in json form
        with open(astfile, 'rb') as jsonfile:
            walker = Walker()
            try:
                #walk json object
                walker.walk(json.load(jsonfile))
            except ValueError:
                sys.exit(error+'decoding JSON has failed')
    except IOError:
        sys.exit(error+astfile+' does not exist')

    parser = Parser(walker)
    parser.parse(jsfile)

    try:
        with open(csvfile, 'w') as csvFile:
            parser.printToFile(csvFile)
    except IOError:
        sys.exit(error+'problem writing new csv file')

    try:
        with open(funcfile, 'a') as f:
            parser.printFuncs(f, jsfile)
    except IOError:
        sys.exit(error+'problem writing Function csv file')
