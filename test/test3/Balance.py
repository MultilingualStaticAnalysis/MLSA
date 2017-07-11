import Pyv8

def getAccountNumber():
    print "what's the account number?"
    return 5

def getPIN(n):
    print "What's your PIN number?"
    return 9

def findBalance(a, n):
    print "checking balance in database"
    return 4

def printBalace(b):
    print "printing balance in neat style"

accountNumber = getAccountNumber()
pin = getPIN(accountNumber)
balance = findBalance(accountNumber, pin)
printBalance(balance)
