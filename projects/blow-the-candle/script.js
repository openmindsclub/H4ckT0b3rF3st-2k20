// set up text to print, each item in array is new line
var aText = new Array(
    "blow the candle to make a wish",
    "ily and you're welcome"
    );
var bText = new Array(
        "SIKE !",
        "birthdays are just a capitalist ploy to brain wash the masses into buying more cake",
        "and to distract you from the fact that you still have a soutenance to prepare"
);

    var iSpeed = 100; // time delay of print out
    var iIndex = 0; // start printing array at this posision
    var iArrLength = aText[0].length; // the length of the text array
    var iScrollAt = 20; // start scrolling up at this many lines

    var iTextPos = 0; // initialise text position
    var sContents = ''; // initialise contents variable
    var iRow; // initialise current row

    function typewriter1()
    {
     sContents =  ' ';
     iRow = Math.max(0, iIndex-iScrollAt);
     var destination = document.getElementById("typedtext1");

     while ( iRow < iIndex ) {
      sContents += aText[iRow++] + '<br />';
     }
     destination.innerHTML = sContents + aText[iIndex].substring(0, iTextPos) + "_";
     if ( iTextPos++ == iArrLength ) {
      iTextPos = 0;
      iIndex++;
      if ( iIndex != aText.length ) {
       iArrLength = aText[iIndex].length;
       setTimeout("typewriter1()", 500);
      }
     } else {
      setTimeout("typewriter1()", iSpeed);
     }
    }

    function typewriter2()
    {
     sContents =  ' ';
     iRow = Math.max(0, iIndex-iScrollAt);
     var destination = document.getElementById("typedtext2");

     while ( iRow < iIndex ) {
      sContents += bText[iRow++] + '<br />';
     }
     destination.innerHTML = sContents + bText[iIndex].substring(0, iTextPos) + "_";
     if ( iTextPos++ == iArrLength ) {
      iTextPos = 0;
      iIndex++;
      if ( iIndex != bText.length ) {
       iArrLength = bText[iIndex].length;
       setTimeout("typewriter2()", 500);
      }
     } else {
      setTimeout("typewriter2()", iSpeed);
     }
    }

    typewriter1();
    typewriter2();
