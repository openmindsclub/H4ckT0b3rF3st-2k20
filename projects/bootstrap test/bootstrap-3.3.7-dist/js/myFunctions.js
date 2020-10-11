

$(document).ready(function(){


		$("body").niceScroll({
			 cursorcolor: "#00A0B0",
			
		});

$(".icon-option").click(function(){
	$(".font-option").toggle();
});
	
var fontLI = $(".font-option ul li");

    fontLI
	.eq(0).css("fontFamily","Arial").end()
	.eq(1).css("fontFamily","Baskerville").end()
	.eq(2).css("fontFamily","Consolas").end()
	.eq(3).css("fontFamily","Gill Sans").end()
	.eq(4).css("fontFamily","Impact").end()
	.eq(5).css("fontFamily","Lucida Grande").end()
	
	
	
	fontLI.click(function(){
		
		$("link[href*='themes']").attr("href",$(this).attr("data-value"))
		//console.log($(this).attr("data-value"))
	});
	});

$(window).on('load',function(){
	
	$(".loading-overlay .loader").fadeOut(0,function(){
		$("body").css("overflow","auto");
		$(this).parent().fadeOut(0);
	});
});

 var scrollButton = $("#to-top")
 
 $(window).on("scroll",function(){
  
  
  if($(this).scrollTop()>=700)
   {
    scrollButton.show();
   }
  else
   {
    scrollButton.hide();
   }
  
  scrollButton.click(function(){
   $("html,body").stop().animate({scrollTop:0},600);
  });
 });