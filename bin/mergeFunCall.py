# MLSA Multilingual Software Analysis
# This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
# mergeFunCall.py takes in a list of csv files generated from pyViaC.py, pyViaJS.py, and jsViaPy.py. The program modifies all the arguments in the calls, taking out the line numbers in the variable arguments. Then, the program adds two columns to the beginning of each csv file - the program id in the first column, and the type of program in the second column (1-C/C++, 2-Python, 3-JavaScript). The output is a csv file with all of the input csv files' content
# Author: Anne Marie Bogar
# Date: June 15, 2017
# this code can be copied or used and is without warrenty or support, but this header needs to be copied along with the program FU2017
# Input: csv file
#		call_id(int),class(string),scope(string),function_name(string),argument1(string),argument2(string)...
# Output: csv file
#		program_id(int),program_type(int),call_id(int),class(string),scope(string),function_name(string),argument1(string),argument2(string)...
# for arguments, all literals are encased in <> (ex: <5>) and all variables have their line number attached (ex: var-6)

import sys
import os
import csv

#global variables
error = 'MLSA: mergeFunCall; ' #beginning of all error messages

#dictionary -> change if adding another language
# C/C++ = 1, Python = 2, JavaScript = 3
typeDict = {'cpp':1, 'c':1, 'py':2, 'js':3}

#---------------------------Body Functions-------------------------------#

#returns the csv line with all variable arguments sans line number
def modifyArgs(row):
    #the arguments are found after the 4th column in the csv file
    args = row[4:]
    #call deleteLineNo on all arguments
    for num, a in enumerate(args):
        args[num] = deleteLineNo(a)
    #returns the first 4 columns of the original csv line and the newly modified argument columns
    return row[:4]+args

#deletes the line number from argument variables
#ex: var-6 -> var
def deleteLineNo(arg):
    #get the first character in the string arg
    beginning = arg[0]
    #get the last character in the string arg
    end = arg[-1]
    tempArg = ''
    #literal
    if beginning == '<' and end == '>':
        return arg
    #tuple, list, dictionary, subscript
    elif (beginning == '(' and end == ')') or (beginning == '[' and end == ']') or (beginning == '{' and end == '}'):
        #takes away beginning and end ex: (), [], {}
        arg = arg[1:-1]
        #breaks up lists, types, and dictionaries by element (ex: [a|b|c])
        arglist = arg.split('|')
        #call deleteLineNo on each individual element
        for a in arglist:
            tempArg = tempArg + '|' + deleteLineNo(a)
        #add back the beginning and end of argument
        return beginning+tempArg[1:]+end
    #lambda or function call
    elif '(' in arg and ')' in arg:
        #take off the call ID at the end, and then break up the elements in the function call
        #ex: func(arg1|arg2)6
        a = arg.split(')')
        #for cases where a call is inside of another call inside of another call (ex: func1(func2(func3())))
        if len(a) > 2:
            a.pop()
            a = [')'.join(a)]
        arglist = a[0].split('|')
        #call deleteLineNo on each individual argument
        for a in arglist:
            tempArg = tempArg+'|'+deleteLineNo(a)
        #add back the end ) and the call ID
        return tempArg[1:]+')'+arg.split(')')[-1]
    #ex: {key:value}, list[:5]
    elif ':' in arg:
        #ex: [::7]
        if '::' in arg:
            return '::'+deleteLineNo(arg)
        #ex: [:8]
        elif beginning == ':':
            return ':'+deleteLineNo(arg)
        #ex: [:-3]
        elif end == ':':
            return deleteLineNo(arg)+':'
        #ex: {key:value}, [1:-1]
        else:
            #call deleteLineNo on each element in between :
            for a in arg.split(':'):
                tempArg = tempArg+':'+deleteLineNo(a)
            #tempArg[1:] gets rid of the first : that is added in the for loop
            #ex: :key:value
            return tempArg[1:]
    #member variable (ex: classObj.memberVar)
    elif '.' in arg:
        #call deleteLineNo on each object and attribute
        for a in arg.split('.'):
            tempArg = tempArg+'.'+deleteLineNo(a)
        #tempArg[1:] gets rid of the first . that is added in the for loop
        #ex: .callObj.memberVar
        return tempArg[1:]
    #variable
    else:
        #deletes the line number of a variable argument
        return arg.split('-')[0]

def setFuncs(funcList):
    functions = []
    global error
    try:
        with open(funcList, 'r') as f:
            reader = csv.reader(f)
            functions = list(reader)
    except IOError:
        sys.exit(error+funcList+' does not exist')
    return functions

def integrate(call, funcList, progname):
    added = False
    if '.' in call and call[:4] != 'OBJ.':
        funcprog = call.split('.')[0]+'.'+progname.split('.')[-1]
        numSlashes = len(funcprog.split('/'))
        for f in funcList:
            p = f[0].split('/')
            prog = ''
            if numSlashes == 1:
                prog = p[-1]
            else:
                for x in range(numSlashes-1, -1, -1):
                    prog = '/'+p[x]+prog
                prog = prog[1:]
            if funcprog == prog and call.split('.')[-1] == f[2]:
                return f[0], call.split('.')[-1]
    return progname, call

#------------------------------------------------------------------------#

#---------------------------Main Function--------------------------------#

def main(files, funcs, outputCsv):
    functions = setFuncs(funcs)
    calls = []
    global typeDict, error
    #typeDict = {'cpp':1, 'c':1, 'py':2, 'js':3}

    for filename in files:
        try:
            with open(filename, "r") as csvfile:
                progname = filename[:-14]
                reader = csv.reader(csvfile)
                #ex: file.py_edfunc.csv -> this would get py_edfunc
                t = filename.split('.')[-2]
                #this would get py from py_edfunc
                progType = t.split('_')[0]
                for row in reader:
                    #takes out all line numbers in variable arguments
                    row = modifyArgs(row)
                    fprog, row[3] = integrate(row[3], functions, progname)
                    row.insert(0, fprog)
                    #adds the program type to the beginning of the csv line
                    row.insert(0, typeDict[progType])
                    #adds the program ID to the beginning of the csv line
                    row.insert(0, progname)
                    calls.append(list(row))
        except IOError:
            sys.exit(error+filename+" does not exist")

    try:
        with open(outputCsv, 'w') as mlcsv:
            writer = csv.writer(mlcsv)
            writer.writerows(calls)
    except IOError:
        sys.exit(error+"problem writing new csv file")

    #for csv in files:
    #    os.system("rm "+csv)

#if len(sys.argv) < 2:
#    sys.exit(error+"argument(s) required")

#sys.argv.pop(0)
#main(sys.argv, 'mlcsv')
