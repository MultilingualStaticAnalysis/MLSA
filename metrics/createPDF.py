#!/usr/bin/env python
import os

#dotfile = os.getcwd()+"/includes.dot"
#psfile = os.getcwd()+"/includes.ps"
#pdffile = os.getcwd()+"/includes.pdf"

def main(dotfile, psfile, pdffile):
	print "generating dependency graph..."
	os.system("dot -Tps2 "+dotfile+" -o "+psfile)
	os.system("ps2pdf "+psfile+" "+pdffile)
	print "the callgraph can be found in "+pdffile
