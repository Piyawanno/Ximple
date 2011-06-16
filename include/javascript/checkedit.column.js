$(document).bind("ready", function(){
	$('.checkedit').each(function(){
		if(!$(this).attr('initialized')){
			$(this).change(function(){
				var obj = $('#'+$(this).attr('rel'));
				obj.attr('disabled', !obj.attr('disabled'));
			});
		}
		$(this).attr('initialized', true);
	});
});
