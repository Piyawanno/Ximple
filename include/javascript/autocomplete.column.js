var autoCompleteCurrentInput;

addReady(function(){
	gridInitFunction['auto_complete'] = gridInitAutoComplete;
	initForm($('.auto_complete'), initAutoComplete);
	
	initForm($('#complete_option'), function(form){
		form.click(function(){
			var input = autoCompleteCurrentInput;
			var value = '';
			if(autoCompleteUseCommaColumn[input.attr('name')]){
				var words = input.val().split(',');
				for(var i=0; i< words.length -1 ;i++){
					value += words[i]+', '
				}
			}
			value += $(this).val();
			input.val(value);
			$(this).hide();
		});
	});
	
	$('body').click(function(){
		$('#complete_option').hide();
	});
});

function gridInitAutoComplete(){
	initForm($('.auto_complete'), initAutoComplete);
}

function initAutoComplete(form){
	form.keyup(function(){
		if(autoCompleteUseCommaColumn[$(this).attr('name')]){
			var words = $(this).val().split(',');
			var lastWord = jQuery.trim(words[words.length-1]);
		}else{
			var lastWord = $(this).val();
		}
		if(lastWord.length){
			var option = $('#complete_option');
			var pos = $(this).offset();
			option.html('');
			option.css({
				top: pos.top + $(this).height() + 4 + autoCompleteTop,
				left: pos.left + autoCompleteLeft,
				width: $(this).width() + 2,
			});
			$('#complete_option option').remove();
			autoCompleteCurrentInput = $(this);
			var uri = sectionURI+$(this).attr('alt')+'/wildcard/'+lastWord;
			$.get(uri, function(data){
				if(data.length){
					option.append(data);
					option.show();
				}
			}, 'html');
		}
	});
}
