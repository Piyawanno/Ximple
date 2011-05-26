$(document).bind("ready", function(){
	$('.color_picker').each(function(){
		if(!$(this).attr('initialized')){
			formID = this.attr('id');
			$("#picker_"+formID).farbtastic("#"+formID);
			$("#picker_"+formID).dialog({
				bgiframe : true,
				autoOpen : false,
				modal : true,
				width : 220,
				height : 250,
				title : selectColorLabel,
			});
			$("#"+formID).click(function(){$("#picker_"+formID).dialog("open");});
		}
		$(this).attr('initialized', true);
	});
});
