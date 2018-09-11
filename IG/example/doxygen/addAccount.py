def getInformation():
        print "what's your information?"
        j = 4
        return 9

def createAccount(i, p):
        print "created account"
        checkBalance(i, p)

def setPIN():
        def getAccount(accountNumber):
                return getInformation()
        print "choose pin number"
        getAccount(549384761927).setPin()
        return 0

information = getInformation()
pin = setPIN()
createAccount(information, pin)
checkBalance(pin)
