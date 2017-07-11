import sys
import json

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
    def printCall(self, csvFile):
        if self.args:
            csvFile.write(str(self.ID)+','+self.className+','+self.scope+','+self.name+','+','.join(self.args)+'\n')
        else:
            csvFile.write(str(self.ID)+','+self.className+','+self.scope+','+self.name+'\n')

    def setArgs(self, arglist):
        self.args = arglist
        
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
        self.functionDefinitionCount = 0
        self.lambdaCount = 0
        self.variableFunctionCount = 0

    def printStats(self, f):
        f.write('Function Definitions: '+str(self.functionDefinitionCount)+'\n')
        f.write('Lambda Functions: '+str(self.lambdaCount)+'\n')
        f.write('Functions assigned to variables: '+str(self.variableFunctionCount)+'\n')

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
                for d in item['args']['defaults']:
                    if 'Lambda' in str(d):
                        self.lambdaCount +=1
                self.functionDefinitionCount += 1
            if Type == 'Call':
                self.calls.append((len(self.calls), item))
            if Type == 'Assign':
                if item['value'].get('_type', None) == 'Lambda':
                    self.lambdaCount += 1
                for a, f in self.functionDefs:
                    if item['value'].get('id') == a:
                        self.variableFunctionCount += 1
            if Type == "ClassDef":
                self.classDefs.append((item.get('name'), item))
        else:
            pass
            #print '/' + '/'.join(path), key, item

    def walk(self, tree, path=[]):
        assert(isinstance(tree, dict))
        for k, v in tree.iteritems():
            self.walkItem(path=path, key=k, item=v)

#Parser:
#Walker walker -> mainly for use of walker's lists
#list final -> holds Calls with all the function calls in the program
#list calls -> copy of walker's calls list; keeps track of function calls
class Parser:
    def __init__(self, walker):
        self.walker = walker
        self.final = []
        self.calls = walker.calls
        self.memberCallCount = 0
        self.callInsideCallCount = 0
        self.normalProcedureCallCount = len(self.calls)

    def printStats(self, f):
        f.write('Normal Procedure Calls: '+str(self.normalProcedureCallCount)+'\n')
        f.write('Calls as Arguments of another call: '+str(self.callInsideCallCount)+'\n')
        f.write('Member Function Calls: '+str(self.memberCallCount)+'\n')

    #creates all the Call objects for the final list
    def parse(self, filename):
        for n, c in self.calls:
            name = c.get('func').get('id', None) #name of function called
            if name == None:
                if(c.get('func').get('attr', None) != None):
                   name = 'OBJ.'+c.get('func').get('attr') #member function
                else:
                   name = '**Unidentified_Function**'
                self.memberCallCount += 1
                self.normalProcedureCallCount -= 1
            self.final.append(Call(name, n)) #create Call object
            self.final[-1].setScope(self.getScope(filename, c)) #set scope of Call object
            self.final[-1].setClass(self.getClass(c)) #set class of Call object
            self.final[-1].setArgs(self.getArgs(c, True)) #set arguments of Call object

    #returns the scope (where in the program the function was called)
    def getScope(self, filename, callJSON):
        scope = filename #assume called in the main body of the program
        for a, b in self.walker.functionDefs:
            if str(callJSON) in str(b):
                scope = a #called in a function definition
                break
        return scope

    #returns the class (name of class if inside member function, else GLOBAL)
    def getClass(self, c):
        className = 'GLOBAL' #assume called outside a class definition
        for d, e in self.walker.classDefs:
            if str(c) in str(e):
                className = d #inside member function definition
                break
        return className

    #returns the value if the argument is a literal or name if variable; None otherwise
    def getSimpleValue(self, i):
        retval = i.get('id', None)
        if retval == None: #not variable
            retval = i.get('n', None)
            if retval == None: #not int/double or variable
                retval = i.get('s', None)
        return retval

    #returns the value/name of the argument of a call
    def parseArgs(self, item):
        #print json.dumps(item)
        #print '-----'
        if item.get("_type", None) == 'Call': #function call as argument of another call
            self.callInsideCallCount += 1
            self.normalProcedureCallCount -= 1
            name = item['func'].get('id', None) #find name of funcion called
            if name == None:
                self.normalProcedureCallCount += 1
                name = 'OBJ.'+item['func'].get('attr') #member function
            for n, c in self.calls:
                if str(item) == str(c):
                    if self.final[n].args == []:
                        name = name+'()'+str(n)
                    else:
                        name = name+'('+','.join(self.final[n].args)+')'+str(n)
            return name
        else:
            argName = self.getSimpleValue(item) #gets argument's value if literal or variable
            if argName != None: #literal argument (int, string, char...)
                if item.get('id', None) == None:
                    if '\n' in str(argName):
                        argName = argName.replace('\n', '\\n')
                    argName = '<'+str(argName)+'>' #distinguishes literal value (as opposed to variable name)
            else:
                argName = item.get('_type', None)
                if argName == 'Tuple': #(a, b)
                    a = ''
                    for e in item['elts']:
                        a = a+self.parseArgs(e)+','
                    argName = '('+a[:-1]+')'
                if argName == 'List': #[1, 2, 3]
                    a = ''
                    for e in item['elts']:
                        a = a+self.parseArgs(e)+','
                    argName = '['+a[:-1]+']'
                if argName == 'Dict': #{key: value}
                    d = []
                    argName = '{'
                    for k in item['keys']:
                        d.append([self.parseArgs(k)])
                    for i, v in enumerate(item['values']):
                        d[i].append(self.parseArgs(v))
                    for k, v in d:
                        argName = argName+str(k)+':'+str(v)+','
                    argName = argName[:-1]+'}'
                if argName == 'Subscript': #var[1][2]
                    argName = self.getSubscript(item)
                if argName == 'Lambda': #lambda k: print(k)
                    a = self.getArgs(item['args'], False) #find values of all arguments (ex: k)
                    argName = 'lambda('+','.join(a)+')'
                if argName == 'Attribute': # object.memberVariable
                    var = self.parseArgs(item['value'])
                    if '(' in var and ')' in var:
                        var = 'OBJ'
                    argName = var+'.'+item.get('attr')
            if argName == None:
                sys.exit("argument type is undefined")
            return str(argName)

    #returns a String of a subscript argument -> var[j][k] or var[k]
    def getSubscript(self, item):
        def parseSub(item):
            if item.get('value', None) != None:
                return self.parseArgs(item.get('value'))
            elif item.get('step', None) != None:
                return '::'+str(self.parseArgs(item.get('step')))
            elif item.get('upper', None) != None:
                return ':'+str(self.parseArgs(item.get('upper')))
            elif item.get('lower', None) != None:
                return str(self.parseArgs(item.get('lower')))+':'
        subscript2 = subscript1 = arr = ''
        subscript1 = parseSub(item['slice']) #value of first subscript
        if 'slice' in item['value']:
            subscript2 = parseSub(item['value']['slice']) #value of second subscript (if exists)
            arr = self.parseArgs(item['value']['value']) #name of matrix
        else:
            arr = self.parseArgs(item['value']) #name of list
        if subscript2 != '':
            return arr+'['+str(subscript2)+']['+str(subscript1)+']'
        else:
            return arr+'['+str(subscript1)+']'

    #returns a list of the values of all the arguments of a call
    def getArgs(self, c, call):
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
    def printToFile(self, csvFile):
        for f in self.final:
            f.printCall(csvFile)

################################################################################################

filename = sys.argv[1] #JSON AST file
pyFi = filename[:-4]+'py' #Python file for the AST 
csvFi = filename[:-4]+'py_func.csv' #CSV file for the Python program
stats = filename[:-4]+'txt' #text file for stats

with open(filename, 'rb') as jsonfile:
    walker = Walker()
    walker.walk(json.load(jsonfile)) #walks JSON object

with open(csvFi, 'w') as f:
    parser = Parser(walker)
    parser.parse(pyFi) #collects all the relevant information from the walked JSON object
    parser.printToFile(f) #prints Call information to CSV file

with open(stats, 'w') as s:
    walker.printStats(s)
    parser.printStats(s)
