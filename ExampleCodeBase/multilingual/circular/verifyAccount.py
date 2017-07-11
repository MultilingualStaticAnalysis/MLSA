import PyV8

def checkDb(u, p):
    print 'check db'
    return True;

def printError():
    print 'this is an error message'

def printWelcome():
    print(PyV8.JSContext().eval(open("welcome.js").read()))

verfied = checkDb(username, password)
if verified:
    printWelcome()
else:
    printError()
