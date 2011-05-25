$(document).ready(function(){$(document).trigger("ready");});
	$('.checkedit').change(function(){
		var obj = $('#'+$(this).attr('rel'));
		obj.attr('disabled', !obj.attr('disabled'));
	});
);
