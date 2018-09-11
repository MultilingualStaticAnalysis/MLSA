#!/usr/bin/env python
import RDAKillGen
import getControlFlow
import RDAEntryExitList

def main(controlFlowFile, varsFile, outputFile):
	#generate control flow CFG:	
	controlFlow = getControlFlow.main(controlFlowFile)

	
	#Generate the killGenList
	killGenList = RDAKillGen.main(varsFile)
	#output file is the RDA csv
	entryExitList = RDAEntryExitList.main(controlFlow, killGenList, outputFile)

#main('test.c_rcfg.csv', 'test.c_vars.csv', 'test.c_rda.csv')