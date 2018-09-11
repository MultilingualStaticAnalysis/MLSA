#!/usr/bin/env python
# MLSA Multilingual Software Analysis
# This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
# cSA.py takes in a C or C++ file and generates a text ast file from that C/C++ file. cFunCall is called with the ast file passed to it, and creates a csv file of all the call graphs in the C/C++ program.  is called with that csv file, and results in a new csv file where any Python files called in the C/C++ program are substituted in for the appropriate API. That resulting csv file is then returned.
# Author: Anne Marie Bogar
# Date: June 13, 2017
# this code can be copied or used and is without warrenty or support, 
# but this header needs to be copied along with the program FU2017
# Input: command line, one digit for the test number to perform
# Output: all the CSV files fomr mlcg and _stats.txt file which will show
# any differences between the output of this run and the correct output

import os
import sys

error = 'MLSA: testcode; '
diffDict = {
    '0_OG':['Binary.c_call_OG.csv', 'Binary.c_finalcall_OG.csv', 'Bubble.c_call_OG.csv', 'Bubble.c_finalcall_OG.csv', 'RPG.cpp_call_OG.csv', 'RPG.cpp_finalcall_OG.csv', 'Stenciltst.c_call_OG.csv', 'Stenciltst.c_finalcall_OG.csv', 'Summation.c_call_OG.csv', 'Summation.c_finalcall_OG.csv', 'test0_callgraph_OG.csv', 'test0_funcs_OG.csv'], 
    '0_new':['Binary.c_call.csv', 'Binary.c_finalcall.csv', 'Bubble.c_call.csv', 'Bubble.c_finalcall.csv', 'RPG.cpp_call.csv', 'RPG.cpp_finalcall.csv', 'Stenciltst.c_call.csv', 'Stenciltst.c_finalcall.csv', 'Summation.c_call.csv', 'Summation.c_finalcall.csv','test0_callgraph.csv', 'test0_funcs.csv'], 
    '1_OG':['func.c_rcfg_OG.csv', 'func.c_rda_OG.csv','func.c_fcfg_OG.csv','func.c_vars_OG.csv', 'if.cpp_rcfg_OG.csv', 'if.cpp_rda_OG.csv', 'if.cpp_fcfg_OG.csv', 'if.cpp_vars_OG.csv', 'ifWithinIf.c_rcfg_OG.csv', 'ifWithinIf.c_rda_OG.csv', 'ifWithinIf.c_fcfg_OG.csv', 'ifWithinIf.c_vars_OG.csv', 'ifWithinWhile.c_rcfg_OG.csv', 'ifWithinWhile.c_rda_OG.csv', 'ifWithinWhile.c_fcfg_OG.csv', 'ifWithinWhile.c_vars_OG.csv', 'whileAfterWhile.c_rcfg_OG.csv', 'whileAfterWhile.c_rda_OG.csv', 'whileAfterWhile.c_fcfg_OG.csv', 'whileAfterWhile.c_vars_OG.csv', 'whileWithinIf.c_rcfg_OG.csv', 'whileWithinIf.c_rda_OG.csv', 'whileWithinIf.c_fcfg_OG.csv', 'whileWithinIf.c_vars_OG.csv', 'whileWithinWhile.c_rcfg_OG.csv', 'whileWithinWhile.c_rda_OG.csv', 'whileWithinWhile.c_fcfg_OG.csv', 'whileWithinWhile.c_vars_OG.csv'],
     '1_new':['func.c_rcfg.csv', 'func.c_rda.csv','func.c_fcfg.csv','func.c_vars.csv', 'if.cpp_rcfg.csv', 'if.cpp_rda.csv', 'if.cpp_fcfg.csv', 'if.cpp_vars.csv', 'ifWithinIf.c_rcfg.csv', 'ifWithinIf.c_rda.csv', 'ifWithinIf.c_fcfg.csv', 'ifWithinIf.c_vars.csv', 'ifWithinWhile.c_rcfg.csv', 'ifWithinWhile.c_rda.csv', 'ifWithinWhile.c_fcfg.csv', 'ifWithinWhile.c_vars.csv', 'whileAfterWhile.c_rcfg.csv', 'whileAfterWhile.c_rda.csv', 'whileAfterWhile.c_fcfg.csv', 'whileAfterWhile.c_vars.csv', 'whileWithinIf.c_rcfg.csv', 'whileWithinIf.c_rda.csv', 'whileWithinIf.c_fcfg.csv', 'whileWithinIf.c_vars.csv', 'whileWithinWhile.c_rcfg.csv', 'whileWithinWhile.c_rda.csv', 'whileWithinWhile.c_fcfg.csv', 'whileWithinWhile.c_vars.csv'], 
     '2_OG':['testing.py_call_OG.csv', 'testing.py_finalcall_OG.csv', 'testing1.py_call_OG.csv', 'testing1.py_finalcall_OG.csv', 'testing2.py_call_OG.csv', 'testing2.py_finalcall_OG.csv', 'testing3.py_call_OG.csv', 'testing3.py_finalcall_OG.csv', 'testing4.py_call_OG.csv', 'testing4.py_finalcall_OG.csv', 'testing5.py_call_OG.csv', 'testing5.py_finalcall_OG.csv', 'testing6.py_call_OG.csv', 'testing6.py_finalcall_OG.csv', 'test2_callgraph_OG.csv', 'test2_funcs_OG.csv'], 
     '2_new':['testing.py_call.csv', 'testing.py_finalcall.csv', 'testing1.py_call.csv', 'testing1.py_finalcall.csv', 'testing2.py_call.csv', 'testing2.py_finalcall.csv', 'testing3.py_call.csv', 'testing3.py_finalcall.csv', 'testing4.py_call.csv', 'testing4.py_finalcall.csv', 'testing5.py_call.csv', 'testing5.py_finalcall.csv', 'testing6.py_call.csv', 'testing6.py_finalcall.csv', 'test2_callgraph.csv', 'test2_funcs.csv'], 
    '3_OG':['addAccount.py_call_OG.csv', 'addAccount.py_finalcall_OG.csv', 'Balance.py_call_OG.csv', 'Balance.py_finalcall_OG.csv', 'Bank.c_call_OG.csv', 'Bank.c_finalcall_OG.csv', 'Bank.c_fcfg_OG.csv', 'Bank.c_rcfg_OG.csv', 'Bank.c_rda_OG.csv', 'Bank.c_vars_OG.csv', 'Deposit.py_call_OG.csv', 'Deposit.py_finalcall_OG.csv', 'ex1.c_call_OG.csv', 'ex1.c_finalcall_OG.csv', 'ex1.py_call_OG.csv', 'ex1.py_finalcall_OG.csv', 'ex2.c_call_OG.csv', 'ex2.c_finalcall_OG.csv', 'ex2.py_call_OG.csv', 'ex2.py_finalcall_OG.csv', 'ex3.cpp_call_OG.csv', 'ex3.cpp_finalcall_OG.csv', 'ex3.py_call_OG.csv', 'ex3.py_finalcall_OG.csv', 'ex4.c_call_OG.csv', 'ex4.c_finalcall_OG.csv', 'ex4.py_call_OG.csv', 'ex4.py_finalcall_OG.csv', 'ex5.c_call_OG.csv', 'ex5.c_finalcall_OG.csv', 'ex5.py_call_OG.csv', 'ex5.py_finalcall_OG.csv', 'Transfer.py_call_OG.csv', 'Transfer.py_finalcall_OG.csv', 'Welcome.py_call_OG.csv', 'Welcome.py_finalcall_OG.csv', 'test3_callgraph_OG.csv', 'test3_funcs_OG.csv'], 
    '3_new':['addAccount.py_call.csv', 'addAccount.py_finalcall.csv', 'Balance.py_call.csv', 'Balance.py_finalcall.csv', 'Bank.c_call.csv', 'Bank.c_finalcall.csv', 'Bank.c_fcfg.csv', 'Bank.c_rcfg.csv', 'Bank.c_rda.csv', 'Bank.c_vars.csv', 'Deposit.py_call.csv', 'Deposit.py_finalcall.csv', 'ex1.c_call.csv', 'ex1.c_finalcall.csv', 'ex1.py_call.csv', 'ex1.py_finalcall.csv', 'ex2.c_call.csv', 'ex2.c_finalcall.csv', 'ex2.py_call.csv', 'ex2.py_finalcall.csv', 'ex3.cpp_call.csv', 'ex3.cpp_finalcall.csv', 'ex3.py_call.csv', 'ex3.py_finalcall.csv', 'ex4.c_call.csv', 'ex4.c_finalcall.csv', 'ex4.py_call.csv', 'ex4.py_finalcall.csv', 'ex5.c_call.csv', 'ex5.c_finalcall.csv', 'ex5.py_call.csv', 'ex5.py_finalcall.csv', 'Transfer.py_call.csv', 'Transfer.py_finalcall.csv', 'Welcome.py_call.csv', 'Welcome.py_finalcall.csv', 'test3_callgraph.csv', 'test3_funcs.csv'], 
    '4_OG':['ex1.js_call_OG.csv', 'ex1.js_finalcall_OG.csv', 'ex2.js_call_OG.csv', 'ex2.js_finalcall_OG.csv', 'ex3.js_call_OG.csv', 'ex3.js_finalcall_OG.csv', 'ex4.js_call_OG.csv', 'ex4.js_finalcall_OG.csv', 'ex5.js_call_OG.csv', 'ex5.js_finalcall_OG.csv', 'test4_callgraph_OG.csv', 'test4_funcs_OG.csv'], 
    '4_new':['ex1.js_call.csv', 'ex1.js_finalcall.csv', 'ex2.js_call.csv', 'ex2.js_finalcall.csv', 'ex3.js_call.csv', 'ex3.js_finalcall.csv', 'ex4.js_call.csv', 'ex4.js_finalcall.csv', 'ex5.js_call.csv', 'ex5.js_finalcall.csv', 'test4_callgraph.csv', 'test4_funcs.csv'], 
    '5_OG':['ex1.cpp_call_OG.csv', 'ex1.cpp_finalcall_OG.csv', 'ex1.cpp_fcfg_OG.csv', 'ex1.cpp_rcfg_OG.csv', 'ex1.cpp_rda_OG.csv', 'ex1.cpp_vars_OG.csv', 'ex1.js_call_OG.csv', 'ex1.js_finalcall_OG.csv', 'ex1.py_call_OG.csv', 'ex1.py_finalcall_OG.csv', 'ex2.cpp_call_OG.csv', 'ex2.cpp_finalcall_OG.csv', 'ex2.js_call_OG.csv', 'ex2.js_finalcall_OG.csv', 'ex2.py_call_OG.csv', 'ex2.py_finalcall_OG.csv', 'ex3.py_call_OG.csv', 'ex3.py_finalcall_OG.csv', 'ex3.js_call_OG.csv', 'ex3.js_finalcall_OG.csv', 'test5_callgraph_OG.csv', 'test5_funcs_OG.csv'], 
    '5_new':['ex1.cpp_call.csv', 'ex1.cpp_finalcall.csv','ex1.cpp_fcfg.csv', 'ex1.cpp_rcfg.csv', 'ex1.cpp_rda.csv', 'ex1.cpp_vars.csv', 'ex1.js_call.csv', 'ex1.js_finalcall.csv', 'ex1.py_call.csv', 'ex1.py_finalcall.csv', 'ex2.cpp_call.csv', 'ex2.cpp_finalcall.csv', 'ex2.js_call.csv', 'ex2.js_finalcall.csv', 'ex2.py_call.csv', 'ex2.py_finalcall.csv', 'ex3.py_call.csv', 'ex3.py_finalcall.csv', 'ex3.js_call.csv', 'ex3.js_finalcall.csv', 'test5_callgraph.csv', 'test5_funcs.csv']}

if len(sys.argv) != 2:
    sys.exit(error+'number of test folder needed')
if sys.argv[1] != '-1' and sys.argv[1] != '0' and sys.argv[1] != '1' and sys.argv[1] != '2' and sys.argv[1] != '3' and sys.argv[1] != '4' and sys.argv[1] != '5':
    sys.exit(error+'there is no test folder numbered '+sys.argv[1])

version = sys.argv[1]
mlsaPath = os.path.split(os.getcwd())[0]+'/bin/'
testPath = os.getcwd()+'/test'+version
myPath = os.getcwd()+'/'
statsfile = 'test'+version+'_stats.txt'

if (version=='-1'):
    print "Removing any new files in the test folders..."
    for checkversion in ['0','1','2','3','4','5']:
        testPath = os.getcwd()+'/test'+checkversion
        delete = [os.path.join(testPath, f) for f in os.listdir(testPath) if os.path.isfile(os.path.join(testPath, f))]
        for d in delete:
            if 'OG.' not in d.split('_')[-1]:
                if '_' in d:
                    print "Deleting "+d
                    os.system('rm '+d)
    delete = [os.path.join(os.getcwd(), f) for f in os.listdir(os.getcwd()) if os.path.isfile(os.path.join(os.getcwd(), f))]
    for d in delete:
        if 'testcode.py' not in d:
            print "Deleting "+d
            os.system('rm '+d)
    sys.exit("All new files removed.")


os.system('python '+mlsaPath+'mlcg.py '+testPath)
os.system('cp test'+version+'_callgraph.csv test'+version)
os.system('cp test'+version+'_funcs.csv test'+version)

with open(statsfile, 'w') as f:
    for i, ogfile in enumerate(diffDict[version+'_OG']):
        ogfile = testPath+'/'+ogfile
        filename = diffDict[version+'_new'][i]
        #if 'test'+version in filename:
        #    newfile = myPath+filename
        #else:
        newfile = testPath+'/'+filename
        f.write('differences in '+filename+':\n')
        #os.system('diff --brief '+ogfile+' '+newfile+' >> '+statsfile)
	#command = 'bash -c "diff <(python ' +mlsaPath+ 'pathfilter.py '+ogfile+')' + ' <(python ' +mlsaPath+ 'pathfilter.py '+newfile+')' + ' >> '+statsfile + '"'
# The following statement has been used to compare data from the two files to avoid the differences being created due to presence of unique identification numbers(hexadecimal number)
# 'sed' command has been used to remove unique numbers from the file for avoiding the differences in files
# NAME: Saba Zahra
# DATE: 9/6/2018
        command = 'bash -c "diff <(python ' +mlsaPath+ 'pathfilter.py '+ogfile+'|sed -r \'s/0x[0-9,a-f]+//g\')' + ' <(python ' +mlsaPath+ 'pathfilter.py '+newfile+'|sed -r \'s/0x[0-9,a-f]+//g\')' + ' >> '+statsfile + '"'

	print command
        os.system(command)
        #os.system('bash -c "diff --brief <(python ' +mlsaPath+ 'pathfilter.py '+ogfile+')' + ' <(python ' +mlsaPath+ 'pathfilter.py '+newfile+')' + ' >> '+statsfile + '"')
#	count = count + 1
#	if count > 11:
		#sys.exit()
