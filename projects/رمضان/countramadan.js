function count(){
    
    var now = new Date(),
    evenDate = new Date("april 23,2020 00:00:00"),
    current = now.getTime(),
    eventTime = evenDate.getTime(),
    remTime = eventTime - current,
    s = Math.floor(remTime/1000),
    m = Math.floor(s/60),
    h = Math.floor(m/60),
    d = Math.floor(h/24),

    h = h %24; 
    m = m % 60; 
    s= s % 60;

    h = (h<10) ? "0"+h : h;
    m = (m<10) ? "0"+m : m;
    s = (s<10) ? "0"+s : s;


    document.getElementById('days').innerHTML = d;
     document.getElementById('hours').innerHTML = h;
      document.getElementById('min').innerHTML = m;
       document.getElementById('sec').innerHTML = s;
       setTimeout( count, 1000);
   }
   count();

   
  