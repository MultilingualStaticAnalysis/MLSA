# MLSA Multilingual Software Analysis
# This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
# pyFunCall.py takes in the JSON ast file generated by pySA.py. The program walks through the JSON file to find all the function calls in the Python program. The program also finds the scope of the call (if it is found inside another function definition or in the main body of the program), the class of the call (if it is a member function -> if not, class is GLOBAL), and the arguments of the call
# Author: Anne Marie Bogar
# Date: June 8, 2017
# this code can be copied or used and is without warrenty or support, but this header needs to be copied along with the program FU2017
# Input: JSON file of Python program's ast
# Output: csv file
#		call_id(int),class(string),scope(string),function_name(string),argument1(string),argument2(string)...
# for arguments, all literals are encased in <> (ex: <5>) and all variables have their line number attached (ex: var-6)
# function calls that are arguments of another function call have their id next to () in csv line of the other function call
#               ex: 6,GLOBAL,file.py,function1,function2()4
# commas in list-type arguments are replaced with |
#               ex: [element1|element2|element3]
# Documentation for the Python AST can be found here: https://docs.python.org/2/library/ast.html

import sys
import json
import csv

#global variables
error = 'MLSA: pyFunCall; '

#------------------------------Call Class--------------------------------#

#Function Call:
#string className -> if in class, if not GLOBAL
#string name -> name of function called
#string scope -> if called inside function, another call, or the main body of the program
#list args -> all of the arguments on the call (literal, variable, tuple, list, dictionary, lambda, subscript)
class Call:
    def __init__(self, name, ID):
        self.name = name
        self.args = []
        self.scope = ''
        self.className = ''
        self.ID = ID

    def setScope(self, scope):
        self.scope = scope

    def setClass(self, className):
        self.className = className

    #prints in CSV format -> class,scope,name,arg1,arg2...
    def printCall(self):
        retval =  [self.ID, self.className, self.scope, self.name]
        return retval+self.args

    def setArgs(self, arglist):
        self.args = arglist

#------------------------------------------------------------------------#

#-----------------------------Import Class-------------------------------#

class Import:
    def __init__(self, name):
        self.name = name
        self.funcs = []

    def setFuncs(self, func):
        self.funcs.append(func)

#------------------------------------------------------------------------#

#-----------------------------Walker Class-------------------------------#
        
#JSON Walker:
#walks the AST JSON file
#list functionDefs -> [name, JSON] keeps track of function definitions
#list classDefs -> (name, JSON) keeps track of class definitions
#list calls -> keeps track of function calls
class Walker:
    def __init__(self):
        self.functionDefs = []
        self.classDefs = []
        self.calls = []
        self.imports = []

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
            Type = item.get('_type', None) #get object "type", or return None
            if Type == 'FunctionDef':
                self.functionDefs.append([item.get('name'), item])
                #for d in item['args']['defaults']:
                #    if 'Lambda' in str(d):
                #        self.lambdaCount += 1
            if Type == 'Call':
                self.calls.append(item)
            #if Type == 'Assign':
            #    if item['value'].get('_type', None) == 'Lambda':
            #        self.lambdaCount += 1
            #    for a, f in self.functionDefs:
            #        if item['value'].get('id') == a:
            #            self.variableFunctionCount += 1
            if Type == "ClassDef":
                self.classDefs.append((item.get('name'), item))
            if Type == 'Import':
                for i in item.get('names'):
                    self.imports.append(Import(i.get('name')))
            if Type == 'ImportFrom':
                self.imports.append(Import(item.get('module')))
                for i in item.get('names'):
                    self.imports[-1].setFuncs(i.get('name'))
        else:
            pass
            #print '/' + '/'.join(path), key, item

    def walk(self, tree, path=[]):
        assert(isinstance(tree, dict))
        for k, v in tree.iteritems():
            self.walkItem(path=path, key=k, item=v)

#------------------------------------------------------------------------#

#-----------------------------Parser Class-------------------------------#

#Parser:
#Walker walker -> mainly for use of walker's lists
#list final -> holds Calls with all the function calls in the program
#list calls -> copy of walker's calls list; keeps track of function calls
class Parser:
    def __init__(self, walker):
        self.walker = walker
        self.final = []
        self.calls = walker.calls

    #creates all the Call objects for the final list
    def parse(self, filename):
        for n, call in enumerate(self.calls):
            name = self.getName(call)
            self.final.append(Call(name, n)) #create Call object
            self.final[-1].setScope(self.getScope(filename, call)) #set scope of Call object
            self.final[-1].setClass(self.getClass(call)) #set class of Call object
            self.final[-1].setArgs(self.getArgs(call, True, name)) #set arguments of Call object

    #returns the scope (where in the program the function was called)
    def getScope(self, filename, callJSON):
        scope = filename #assume called in the main body of the program
        for funName, funDef in self.walker.functionDefs:
            if str(callJSON) in str(funDef):
                scope = funName #called in a function definition
                break
        return scope

    #returns the class (name of class if inside member function, else GLOBAL)
    def getClass(self, call):
        className = 'GLOBAL' #assume called outside a class definition
        for name, classDef in self.walker.classDefs:
            if str(call) in str(classDef):
                className = name #inside member function definition
                break
        return className

    def getName(self, call):
        name = call.get('func').get('id', None)
        if name == None:
            name = call.get('func').get('attr', None)
            if name == None:
                name = '**Unidentified_Function**'
            else:
                 name = self.checkImports(name, call.get('func').get('value').get('id', None))
        else:
            name = self.checkImports(name)
        return name

    def checkImports(self, call, attr='1'):
        name = call
        if attr == '1':
            for i in self.walker.imports:
                for f in i.funcs:
                    if call == f:
                        name = i.name+'.'+call
        else:
            name = 'OBJ.'+call
            for i in self.walker.imports:
                if attr == i.name:
                    name = i.name+'.'+call
        return name

    #returns the value if the argument is a literal or name if variable; None otherwise
    def getSimpleValue(self, item):
        retval = item.get('id', None)
        if retval:
            retval = retval+'-'+str(item.get('lineno'))
        elif retval == None: #not variable
            retval = item.get('n', None)
            if retval == None: #not int/double or variable
                retval = item.get('s', None)
        return retval

    #returns the value/name of the argument of a call
    def parseArgs(self, item):
        global error
        if item.get("_type", None) == 'Call': #function call as argument of another call
            name = self.getName(item)
            for n, c in enumerate(self.calls):
                if str(item) == str(c):
                    if self.final[n].args == []:
                        name = name+'()'+str(n)
                    else:
                        name = name+'('+'|'.join(self.final[n].args)+')'+str(n)
            return name
        else:
            argName = self.getSimpleValue(item) #gets argument's value if literal or variable
            if argName != None: #literal argument (int, string, char...)
                if item.get('id', None) == None:
                    if '\n' in str(argName):
                        argName = argName.replace('\n', '\\n')
                    argName = '<'+str(argName).replace(',', '')+'>' #distinguishes literal value (as opposed to variable name)
            else:
                argName = ''
                Type = item.get('_type', None)
                if Type == 'Tuple': #(a, b)
                    for e in item['elts']:
                        argName = argName+self.parseArgs(e)+'|'
                    argName = '('+argName[:-1]+')'
                if Type == 'List': #[1, 2, 3]
                    for e in item['elts']:
                        argName = argName+self.parseArgs(e)+'|'
                    argName = '['+argName[:-1]+']'
                if Type == 'Dict': #{key: value}
                    d = []
                    for k in item['keys']:
                        d.append([self.parseArgs(k)])
                    for i, v in enumerate(item['values']):
                        d[i].append(self.parseArgs(v))
                    for k, v in d:
                        argName = argName+str(k)+':'+str(v)+'|'
                    argName = '{'+argName[:-1]+'}'
                if Type == 'Subscript': #var[1][2]
                    argName = self.getSubscript(item)
                if Type == 'Lambda': #lambda k: print(k)
                    a = self.getArgs(item['args'], False, '') #find values of all arguments (ex: k)
                    argName = 'lambda('+'|'.join(a)+')'
                if Type == 'Attribute': # object.memberVariable
                    var = self.parseArgs(item['value'])
                    if '(' in var and ')' in var:
                        var = 'OBJ'
                    argName = var+'.'+item.get('attr')+'-'+str(item.get('lineno'))
                if Type == 'BinOp':
                    argName = 'BinOp'
                if Type == 'UnaryOp':
                    argName = 'UnOp'
            if argName == None:
                sys.exit(error+"argument type unidentified")
            return str(argName)

    #returns a String of a subscript argument -> var[j][k] or var[k]
    def getSubscript(self, item):
        def parseSub(item):
            global error
            a = ':'
            if item.get('value', None) != None:
                a = self.parseArgs(item.get('value'))
            if item.get('step', None) != None:
                a = '::'+str(self.parseArgs(item.get('step')))
            if item.get('upper', None) != None:
                a = a+str(self.parseArgs(item.get('upper')))
            if item.get('lower', None) != None:
                a = str(self.parseArgs(item.get('lower')))+a
            if a == ':':
                sys.exit(error+'subscript value unidentified')
            return a
        arg = ''
        arg = '['+parseSub(item.get('slice'))+']'
        if item.get('value').get('_type') == 'Name':
            arg = item.get('value').get('id')+arg
        else:
            if item.get('value').get('_type') == 'Subscript':
                arg = self.getSubscript(item.get('value'))+arg
            else:
                arg = self.parseArgs(item.get('value'))+arg
        return arg

    #returns a list of the values of all the arguments of a call
    def getArgs(self, c, call, callName):
        args = []
        if c['args'] != []: #normal arguments
            for a in c['args']:
                args.append(self.parseArgs(a))
        if call:
            if c.get('kwargs') != None: #**kwargs -> predefined dictionary variable
                args.append('**'+self.parseArgs(c.get('kwargs')))
            if c['keywords'] != []: #arguments whose values are defined in the call -> call(var='value')
                for k in c['keywords']:
                    args.append(self.parseArgs(k.get('value')))
            if c.get('starargs') != None: #*starargs -> predefined list variable
                args.append('*'+self.parseArgs(c.get('starargs')))
        else: #lambda parameters
            if c.get('kwarg') != None: #**kwargs -> predefined dictionary variable
                args.append('**'+self.parseArgs(c.get('kwarg')))
            if c['defaults'] != []: #parameters whose values are predefined -> function(var='value')
                for k in c['defaults']:
                    args.append(self.parseArgs(k))
            if c.get('vararg') != None: #*varargs -> predefined list variable (allows for dynamic number of parameters)
                args.append('*'+self.parseArgs(c.get('varargs')))
        return args

    #prints out all Call objects in final list to the CSV file
    def printFunCalls(self, csvFile):
        printable = []
        for f in self.final:
            printable.append(f.printCall())
        writer = csv.writer(csvFile)
        writer.writerows(printable)

    def getParamNum(self, function):
        args = function.get('args')
        num = len(args.get('args'))
        if args.get('kwarg'):
            num += len(args.get('kwarg'))
        if args.get('vararg'):
            num += len(args.get('vararg'))
        return num

    def printFuncs(self, f, filename):
        functions = []
        for func in self.walker.functionDefs:
            functions.append([filename, self.getClass(func[1]), func[0], self.getParamNum(func[1])])
        writer = csv.writer(f)
        writer.writerows(functions)

#------------------------------------------------------------------------#

#-----------------------------Main Function------------------------------#

def main(astfile, pyfile, csvfile, funcfile):
    global error

    try:
        with open(astfile, 'rb') as jsonfile:
            walker = Walker()
            try:
                walker.walk(json.load(jsonfile)) #walks JSON object
            except ValueError:
                sys.exit(error+'decoding JSON has failed')
    except IOError:
        sys.exit(error+astfile+' does not exist')

    parser = Parser(walker)
    parser.parse(pyfile) #collects all the relevant information from the walked JSON object

    try:
        with open(csvfile, 'w') as f:
            parser.printFunCalls(f) #prints Call information to CSV file
    except IOError:
        sys.exit(error+'problem writing Function Call csv file')

    try:
        with open(funcfile, 'a') as f:
            parser.printFuncs(f, pyfile)
    except IOError:
        sys.exit(error+'problem writing Function csv file')
