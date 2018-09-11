doxygen -g
sed 's/EXTRACT_ALL            = NO/EXTRACT_ALL            = YES/' Doxyfile > DoxyfileTemp
sed 's/EXTRACT_PRIVATE        = NO/EXTRACT_PRIVATE        = YES/' DoxyfileTemp > Doxyfile
sed 's/EXTRACT_STATIC         = NO/EXTRACT_STATIC         = YES/' Doxyfile > DoxyfileTemp
sed 's/RECURSIVE              = NO/RECURSIVE              = YES/' DoxyfileTemp > Doxyfile
sed 's/INLINE_SOURCES         = NO/INLINE_SOURCES         = YES/' Doxyfile > DoxyfileTemp
sed 's/CALL_GRAPH             = NO/CALL_GRAPH             = YES/' DoxyfileTemp > Doxyfile
sed 's/HAVE_DOT               = NO/HAVE_DOT               = YES/' Doxyfile > DoxyfileTemp
sed 's/DOT_CLEANUP            = YES/DOT_CLEANUP            = NO/' DoxyfileTemp > Doxyfile
rm DoxyfileTemp
#doxygen Doxyfile
