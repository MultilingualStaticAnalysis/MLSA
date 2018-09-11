#!/bin/bash
# MLSA Multilingual Software Analysis
#
# This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
# cSA.py takes in a C or C++ file and generates a text ast file from that C/C++ file. cFunCall is called with the ast file passed to it, and creates a csv file of all the call graphs in the C/C++ program. pyViaC.py is called with that csv file, and results in a new csv file where any Python files called in the C/C++ program are substituted in for the appropriate API. That resulting csv file is then returned.
# Author: Damian Lyons
# Date: July, 2017
# this code can be copied or used and is without warrenty or support, but this header needs to be copied along with the program FU2017
#
# adds the MLSA path to the ENVIRONMENT variable
# must be executed from mlsa as follows: "source mlsapath.bash" 
# if you do ./mlsapath.bash then the PATH is not updated!
#
echo "MLSA executable path will be `pwd`/bin"
chmod a+x `pwd`/bin/*.py
chmod a+x `pwd`/metrics/*.py
chmod a+x `pwd`/test/*.py
export PATH=$PATH:`pwd`/bin
export PATH=$PATH:`pwd`/metrics

