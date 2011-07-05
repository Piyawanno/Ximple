$(document).bind("ready", function(){
	initForm($(".timestamp_hour_form"), function(form){
		form.spinbox({ 
			min : 0,
			max : 24,
			step : 1
		});
	});
	
	initForm($(".timestamp_minute_form"), function(form){
		form.spinbox({ 
			min : 0,
			max : 60,
			step : 1
		});
	});
});
