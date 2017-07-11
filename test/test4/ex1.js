// Wait for DOM to load
document.addEventListener("DOMContentLoaded", function(event) {

// Put the drop down into a variable
var e = document.getElementById("jumpmenu");
  
// Wait for user to select an option
e.addEventListener("change", function() {
  
    // Put the selected value into a variable
    selectedURL = this.options[this.options.selectedIndex].value;
      
    // Check that the value is not null
    if (this.value != "null") {
      
	// Display the confirm box and put the response into a variable
        var confirmLeave = confirm("Are you sure?");
        
        // If user clicked "OK"
        if (confirmLeave==true) { 
        
	    // Load the selected URL
	    document.location.href = selectedURL; 
        }
        // If user clicked "Cancel"
        else { 
          return false;
        }
    }     
      
});
  
});
