var grid_string = new Array();
var files_string = new Array();
var captchaLock = false;
var initedJQuery = false;
var imgCorrect = '<img class="warning_icon" src="'+rootURI+'files/icon/correct.png" />';
var imgWrong = '<img class="warning_icon" src="'+rootURI+'files/icon/stop.png" />';
var formLock = false;

function checkForm(notNull, label){
	if(formLock){
		alert(formNotCorrect);
		return false;
	}
	var ok = true;
	ok = ok && verifyCaptcha();
	if(!ok) return false;
	ok = ok && checkNotNull(notNull, label);
	if(ok) encryptPasswd();
	return ok;
}

function checkNotNull(notNull, label){
	var ok = true;
	var dataIn = null;
	try {
		for(var i in notNull){
			if(notNull[i].length){
				dataIn = $('#'+notNull[i]);
				if(dataIn.val().length == 0){
					ok=false;
					dataIn.css({'border':'2px solid red'});
					alert(pleaseFill+label[dataIn.attr('name')]);
					break;
				}
			}
		}
	}
	catch (e){
	}
	return ok;
}

function addFileInput(formID, formName){
	$('#'+formID+' ul').append('<li><input type="file" name="'+formName+'[]" size="25" ></li>');
	return false;
}

function preElementFormat(){
	var editors = tinyMCE.EditorManager.editors
	var children;
	var code;
	for(i in editors){
		children = editors[i].getBody().children;
		for(j in children){
			if(children[j].tagName == "PRE"){
				code = children[j].innerHTML;
				code = code.replace(/<br>/gi, '\n');
				code = code.replace(/</gi, "&lt;");
				code = code.replace(/>/gi, "&gt;");
				children[j].innerHTML = code;
			}
		}
	}
}

var translateForm;

function showTranslateDialog(){
	var translate = $('#translate_dialog');
	translateForm = translate.html();
	translate.dialog({
		bgiframe : true,
		autoOpen : false,
		modal : true,
		title : 'Translate-Form',
		width : 520,
		close : function(event, ui){$('#translate_dialog').html(translateForm);},
	});
	translate.dialog('open');
}

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
		initCLEditor();
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

function verifyCaptcha(){
	var ok = true;
	try{
		if(captchaLock == true && ok == true){
			ok = false;
			alert(captchaMessage);
		}
	}
	catch (e){
	}
	return ok;
}
