$(document).bind("ready", function(){
	initForm($(".currency_main"), function(form){
		form.spinbox({
			min  : 0,
			max  : 4294967295,
			step : 1
		});
	});
	
	initForm($(".currency_sub"), function(form){
		form.spinbox({
			min  : 0,
			max  : 99,
			step : 1
		});
	});
});

$(document).bind("submit", function(){
	var realCurrency = $('currency');
	var mainCurrency = $('currency_main');
	var subCurrency  = $('currency_sub');
});
