// Puts the text to scroll into variable called sent - SECTION A
// uses length propert to assess its length and put into variable slen
// initalizes a,b,n, and subsent variables
var sent = "This is a demonstration of a banner moving from the left to right. It makes use of the substring property of Javascript to make an interesting display";
var slen = sent.length;
var siz = 25;
var a = -3, b = 0;
var subsent = "x";

// Creates a function to capture substrings of sent - SECTION B
function makeSub(a,b) {
    subsent = sent.substring(a,b) ;
    return subsent;
}

//Creates a function that increments the indexes of the substring - SECTION C 
//each time and calls the makeSub() function to geneate strings
//a indicates start of substring and siz indicates size of string required
function newMake() {
    a = a + 3;
    b = a + siz;
    makeSub(a,b);
    return subsent;
}

//function uses loop to get changing substrings of target - SECTION D
//repeatedly calls newMake to get next substring
//uses setTimeout() command to arrange for substrings to display 
// at specified times
function doIt() {
    for (var i = 1; i <= slen ; i++) {
	setTimeout("document.z.textdisplay.value = newMake()", i*300);
	setTimeout("window.status = newMake()", i*300);
	newMake();
    }
}

doIt();
