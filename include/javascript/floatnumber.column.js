addReady(function(){
	floatnumberInit();
});

function floatnumberInit(){
	initForm($(".floatnumber_main"), function(form){
		form.spinbox({
			min  : 0,
			max  : 4294967295,
			step : 1
		});
	});
	
	initForm($(".floatnumber_sub"), function(form){
		form.spinbox({
			min  : 0,
			max  : 99,
			step : 1
		});
	});
}

function toInt(value){
	return parseFloat($(value).val());
}


$(document).bind("submit", function(){
	var mainCurrencyValue = new Array();
	var subCurrencyValue = new Array();
	
	$('.floatnumber_main').each(function(index, element){
		mainCurrencyValue[index] = toInt(element);
	});
	
	$('.floatnumber_sub').each(function(index, element){
		subCurrencyValue[index] = toInt(element);
	});
	
	$('.floatnumber').each(function(index, element){
		$(element).val(mainCurrencyValue[index] + 0.01*subCurrencyValue[index]);
	});
});

gridInitFunction['floatnumber'] = floatnumberInit;

