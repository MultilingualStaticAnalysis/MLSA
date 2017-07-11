/* 
Create a JavaScript Date object for the current date and time,
then extract the desired parts, then join them again in the desired format.
*/
var currentDate = new Date(), 
      month = currentDate.getMonth() + 1,
      day = currentDate.getDate(),
      year = currentDate.getFullYear(),
      date = month + "/" + day + "/" + year;
      
// Output the date to the above HTML element
document.getElementById("date").innerHTML = date;
