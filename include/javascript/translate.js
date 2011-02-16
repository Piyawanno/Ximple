var translateForm;

function selectTranslateLanguage(languageSelect){
	var translate = $('#translate_dialog');
	var language = $(languageSelect).val();
	translate.html('<div style="text-align:center;padding:50px;"><img src="'+rootURI+'files/icon/loader.gif"/></div>');
	if(translateModuleName == null){
		var uri = sectionURI+modeName;
	}else{
		var uri = sectionURI+translateModuleName+'_translate_form';
	}
	uri += '/module_id/'+modeID;
	uri += '/language/'+language;
	$.get(uri, function(data){
		translate.html(data);
	});
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
