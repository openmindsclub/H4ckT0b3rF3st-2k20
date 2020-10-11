function Score(ques)
        {
        var score = 0;

        var question = document.getElementsByClassName('qu');
        var nbQuestion = question.length;
        var i = 0;
        while(i < nbQuestion)
        {
          var option = question[i].getElementsByTagName('input');
          var nbOption = option.length;
          var j = 0;
          while (j < nbOption)
          {
            if((option[j].type == 'radio') && (option[j].checked))
              score += parseInt(option[j].value);
            j ++;
          }
          i ++ ;
        }
        	var node = document.createElement("h2");
          var text = document.createTextNode("votre score est "+score+"/10");
          node.appendChild(text);
          var s = document.getElementById('sc');
          s.appendChild(node);
          s.style.display="block";

          var btn = document.getElementById('res');
          btn.style.display = "none";


        /*pour afficher les réponses juste en vert*/
        var r1 = document.getElementById("1");r1.style.backgroundColor="#0080008c"
        document.getElementById('2').style.backgroundColor="#0080008c";
        document.getElementById('3').style.backgroundColor="#0080008c";
        document.getElementById('4').style.backgroundColor="#0080008c";
        document.getElementById('5').style.backgroundColor="#0080008c";
        document.getElementById('6').style.backgroundColor="#0080008c";
        document.getElementById('7').style.backgroundColor="#0080008c";
        document.getElementById('8').style.backgroundColor="#0080008c";
        document.getElementById('9').style.backgroundColor="#0080008c";
        document.getElementById('10').style.backgroundColor="#0080008c";
        }
