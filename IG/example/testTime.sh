prog=$1
time ../../../bin/IG/cFunCall < $prog.cpp_ast.txt > ugh
time python ../../../bin/cFunCall.py $prog.cpp_ast.txt $prog.cpp c.csv f.csv