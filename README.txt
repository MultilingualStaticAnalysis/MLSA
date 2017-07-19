




::::    ::::  :::         ::::::::      :::     
+:+:+: :+:+:+ :+:        :+:    :+:   :+: :+:   
+:+ +:+:+ +:+ +:+        +:+         +:+   +:+  
+#+  +:+  +#+ +#+        +#++:++#++ +#++:++#++: 
+#+       +#+ +#+               +#+ +#+     +#+ 
#+#       #+# #+#        #+#    #+# #+#     #+# 
###       ### ##########  ########  ###     ### 

test

MLSA Installation & Use Instructions

When the MLSA project is cloned it will produce a folder with the following subfolders.
* Bin  contains python code implementing MLSA filter programs and MLSA pipelines.
* Doc  contains MLSA documentation
* Test contains the program testcode.py and test folders test0 through test5 that can be used to determine a correct installation
* Examples contains C/C++, Python and JavaScript subfolders with various programs downloaded from the web to evaluate MLSA.


To run MLSA you will need to have installed the following prerequisites
1.	Clang 3.8 
2.	Python 2.7
3.	SpiderMonkey 2.4 
4.	DOT (Graphviz) 2.38
5.	ps2pdf
6.	Evince or other PDF viewer
7.	Bash shell 


All MLSA testing was done using Ubuntu. Clang, Python, SpiderMonkey (js24) and Graphviz can be installed on Ubuntu using "sudo apt-get install". 

Once you have installed these, you can test whether your MLSA installation works by cd-ing to the test folder and invoking the testcode.py program. As a first step, cd to the top level mlsa directory. In that directory, do "source mlsapath.bash" to add yourinstallation/mlsa/bin to your executable path. 

Next, cd to the test folder. All calls to testcode.py will automatically diff the results generated with the correct results and report the differences in a text file called testN_stats.txt where N is the argument given to the testcode.py program:
1.	./testcode.py 0  will test the C function call generator. 
2.	./testcode.py 1  will test the C control flow, assignment collector and RDA pipeline.
3.	./testcode.py 2  will test the Python function call generator.
4.	./testcode.py 3  will test the multilingual Python and C functional call pipeline.
5.	./testcode.py 4  will test the Javascript function generator.
6.	./testcode.py 5  will test the multilingual Python, C and Javascript pipeline


If you get no differences reported for all these, then your MLSA installation is operating correctly and you can go ahead and use MLSA! 
A good place to start is with the mlcg.py program in bin. This program will invoke the multilingual call graph pipeline on the programs and/or folders you give it as argument. For example, in the MLSA mlsa/test folder if you type:

	mlcg.py test0

Then the multlingual pipeline is called for all the (C/C++, Python or Javascript) programs in test0 and a single call graph generated. Procedure calling between files in the same and different languages will be identified (for the limited set of interoperability calls that have been implemented) and the call graph will reflect this, but programs with no procedure calls in common are fine too. The resulting call graph is a forest of trees. Recursion is flagged after one full cycle and several other kind of interlanguage calls are flagged also.
To get deeper into MLSA you will need to know more about the individual filter programs and pipelines that have been implemented. You can also build new pipelines or add new filters.

Fordham University Multilingual Software Analysis Research Group 

multilingualsa@gmail.com
