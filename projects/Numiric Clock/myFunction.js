function updateDate(){
  var date = new Date(),
      settime = document.getElementById("settime"),
      setdate = document.getElementById("setdate");
       if(date.getSeconds() < 10){
      settime.innerHTML= date.getHours() + ":"+ date.getMinutes()+ ":"+"0"+ date.getSeconds();
       }else if(date.getSeconds() > 10){
        settime.innerHTML= date.getHours() + ":"+ date.getMinutes()+ ":"+ date.getSeconds();
       
      }else if(date.getMinutes() < 10){
        settime.innerHTML= date.getHours() + ":"+"0" +date.getMinutes()+ ":"+ date.getSeconds();
         }else if(date.getMinutes() > 10){
          settime.innerHTML= date.getHours() + ":"+ date.getMinutes()+ ":"+ date.getSeconds();
         
        }else if(date.getHours() < 10){
          settime.innerHTML= "0"+date.getHours() + ":"+date.getMinutes()+ ":"+ date.getSeconds();
           }else{
            settime.innerHTML= date.getHours() + ":"+ date.getMinutes()+ ":"+ date.getSeconds();
           };

           setdate.innerHTML = date.getDate()+"/"+parseInt(date.getMonth()+1) +"/"+ date.getUTCFullYear();
}

setInterval(updateDate,1000);
onload = updateDate();

function getcolor(){
  var getcolor = document.getElementById("setcolor").value;
  localStorage.setItem("color",getcolor);
  document.getElementById("time").style.background= localStorage.getItem("color");
  document.getElementById("body").style.background= localStorage.getItem("color");
}

function setcolor(){
  document.getElementById("setcolor").value = localStorage.getItem("color");
  document.getElementById("time").style.background= localStorage.getItem("color");
  document.getElementById("body").style.background= localStorage.getItem("color");
}

setInterval(setcolor,100);