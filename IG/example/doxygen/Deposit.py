def getAccountNumber():
    print "what's the account number?"
    return 5

def getPIN(n):
    print "What's your PIN number?"
    return 9

def getAmount():
    print "what amount would you like to deposit?"
    return 9

def takePictureOfCheck():
    print "taking pic of check"

def depositCheck(n, p, a):
    takePictureOfCheck()
    print "depositing check"

def printConfirmation():
    print "here's the confirmation of your deposit"

accountNumber = getAccountNumber()
pin = getPIN()
amount = getAmount()
depositCheck(accountNumber, pin, amount)
printConfirmation()
