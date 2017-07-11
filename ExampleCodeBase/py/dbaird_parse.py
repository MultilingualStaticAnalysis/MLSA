import ast
import csv

#for functions
class Def:
    __properties__ = ('defName',)
    def __init__(self, defName):
        self.defName = defName
    def __repr__(self):
        return self.defName

#for the variables, calls, and local functions in functions
class UseDef:
    __properties__ = ('defName', 'localName', 'useName',)
    def __init__(self, defName, localName, useName):
        self.defName = defName 
        self.localName = localName 
        self.useName = useName 
    def __repr__(self):
        return '(%s,%s,%s)' % (self.defName, self.localName, self.useName)

class Foobar(ast.NodeVisitor):
    def __init__(self):
        ast.NodeVisitor.__init__(self)
        self.defStack = ['<global>']
        self.definitionStack = [{}] # localName -> qualifiedName
        self.defResults = []
        self.useDefResults = []

    def visit_FunctionDef(self, node):
        #print node
        #print node.name
        #print [x.id for x in node.args.args]
        defName = '$'.join(self.defStack + [node.name])
        self.definitionStack.append(self.definitionStack[-1].copy())
        self.definitionStack.pop()
        self.definitionStack[-1][node.name] = defName
        self.defResults.append(Def(defName=defName))
        self.defStack.append(defName)
        self.definitionStack.append(self.definitionStack[-1].copy())
        self.definitionStack.pop()
        self.generic_visit(node)
        self.defStack.pop()
        pass

    def visit_Call(self, node):
        #print node
        #print node.func.id, ' inside ', self.defStack
        localName = node.func.id
        useName = self.definitionStack[-1][localName]
        self.useDefResults.append(UseDef(defName=self.defStack[-1],
                                        localName=localName,
                                        useName=useName))

def run(filename):
    tree = ast.parse(open(filename).read()) #dump ast
    visitor = Foobar()
    visitor.visit(tree)
    print(visitor.defResults)
    print visitor.useDefResults

    with open('def.csv', 'w') as defFile, open('usedef.csv', 'w') as useDefFile:
        defCsv = csv.writer(defFile)
        useDefCsv = csv.writer(useDefFile)

        defCsv.writerow(Def.__properties__)
        for row in visitor.defResults:
            defCsv.writerow([row.defName])

        useDefCsv.writerow(UseDef.__properties__)
        for row in visitor.useDefResults:
            useDefCsv.writerow([row.defName, row.localName, row.useName])

run('analyzeme.py')
