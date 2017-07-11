foo = BB.ApplicationServices.lookup;
bar("xyz", 3, 4);
foo("hellosvc", 2, 1);
if (1) {
    bar = foo;
}
bar("hellosvc2", 2, 1);
if (1) {
    //bar("hellosvc3", 2, 1);
}

a = "hellosvc4";
bar(a, 2, 1);
