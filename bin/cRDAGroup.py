#!/usr/bin/env python
import CControlFlow
import CAssignmentCollector
import cRDA

def main(inputFile, fileName, outputFile):
	#FileName conventions:
	fcfgFile = fileName + '_fcfg.csv'
	rcfgFile = fileName + '_rcfg.csv'
	varsFile = fileName + '_vars.csv'


	#Generate controlFlow files (fcfg and rcfg)
	CControlFlow.main(inputFile, fileName, fcfgFile, rcfgFile)
	CAssignmentCollector.main(inputFile, varsFile)
	cRDA.main(rcfgFile, varsFile, outputFile)
	

#main('test.cpp_ast.txt', 'test.cpp', 'test.cpp_rda.csv')
