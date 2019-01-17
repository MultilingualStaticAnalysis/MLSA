#!/usr/bin/env python
# MLSA Multilingual Software Analysis
# This program is part of the MLSA package under development at Fordham University Department of Computer and Information Science.
# The program is a test program for C++ being called by Python using Pybind11
# Author: Saba Bakhshish Zahra
# Date: Jan 17, 2019

import example
import example2
import example3
import ex2 as ex
def X():
   example.add(2)
   example.add(3)
   example.subt(7,5)
   ex.sum1(5,3)
   ex.diff(4,2)

def Y():
   example2.add(5)
   example2.subt(9,3)
   y=5
   example3.add(2,4)
   example3.subtract(4,1) 
X()
Y()
