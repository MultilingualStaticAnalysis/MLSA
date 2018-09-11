def getAccountNumbers():
    print "what's the account number?"
    return 5, 6

def getPIN(a, b):
    print "What's your PIN number?"
    return 9

def getAmount():
    print "how much do you want to transfer?"
    return 8

def makeTransfer(a, b, p):
    amount = getAmount()
    print "making transfer"

def printConfirmation():
    print "your transfer was successful"

accountOne, accountTwo = getAccountNumbers()
pin = getPIN(accountOne, accountTwo)
makeTransfer(accountOne, accountTwo, pin)
printConfirmation()
