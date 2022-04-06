$(document).ready(function(){
	x =0;
	$(".next-button").click(function(){
		x = (x<=400)?(x+100):0;
		$("figure").css("left",-x+"%");
	});
	$(".prev-button").click(function(){
		x = (x>=100)?(x-100):500;
		$("figure").css("left",-x+"%");
	});

});