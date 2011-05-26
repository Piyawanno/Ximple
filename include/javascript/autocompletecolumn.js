$(document).bind("ready", function(){
	$('.auto_complete').each(function(){
		if(!$(this).attr('initialized')){
			$(this).keyup(function(){
				var words = $(this).val().split(',');
				var lastWord = jQuery.trim(words[words.length-1]);
				if(lastWord.length){
					var option = $('#complete_option');
					var pos = $(this).offset();
					option.css({
						top: pos.top + $(this).height() + 4 + autoCompleteTop,
						left: pos.left + autoCompleteLeft,
						width: $(this).width() + 2,
					});
					$('#complete_option option').remove();
					option.attr('rel', $(this).attr('id'));
					$.get(sectionURI+$(this).attr('rel')+'/wildcard/'+lastWord, function(data){
						if(data.length){
							option.append(data);
							option.show();
						}
					});
				}
			});
		}
		$(this).attr('initialized', true);
	});
	
	if(!$('#complete_option').attr('initialized')){
		$('#complete_option').click(function(){
			var input = $('#'+$(this).attr('rel'));
			var value = '';
			var words = input.val().split(',');
			for(var i=0; i< words.length -1 ;i++){
				value += words[i]+', '
			}
			value += $(this).val();
			input.val(value);
			$(this).hide();
		});
	}
	$('#complete_option').attr('initialized', true);
	
	$('body').click(function(){
		$('#complete_option').hide();
	});
});
