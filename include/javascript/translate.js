var translateForm;

function selectTranslateLanguage(languageSelect){
	var translate = $('#translate_dialog');
	var language = $(languageSelect).val();
	if(translateModuleName == null){
		var uri = sectionURI+moduleName+'_translate_form';
	}else{
		var uri = sectionURI+translateModuleName+'_translate_form';
	}
	uri += '/module_id/'+modeID;
	uri += '/language/'+language;
	$.get(uri, function(data){
		translate.html(data);
	});
	translate.html(translateForm);
}

function submitTranslateForm(form, notNull, label){
	var translate = $('#translate_dialog');
	if(checkForm(notNull, label)){
		$(form).ajaxSubmit({success : function(){
			translate.html(translateForm);
			translate.dialog('close');
		}});
	}
	return false;
}
