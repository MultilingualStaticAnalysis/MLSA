function displayWelcome(n){
    return 1;
}

$.ajax({
    type: "POST",
    url: "~/login.py",
    data: { param: text}
}).done(function( o ) {
 // do something
});
displayWelcome(name);
