var captchaLock = false;
var initedJQuery = false;
var imgCorrect = '<img class="warning_icon" src="'+rootURI+'files/icon/correct.png" />';
var imgWrong = '<img class="warning_icon" src="'+rootURI+'files/icon/stop.png" />';
var formLock = false;

function checkForm(notNull, label){
	formatTextIE7();
	if(formLock){
		alert(formNotCorrect);
		return false;
	}
	var ok = true;
	ok = ok && verifyCaptcha();
	if(!ok) return false;
	ok = ok && checkNotNull(notNull, label);
	$(document).trigger("submitform");
	return ok;
}

function formatTextIE7(){
	if(isIE7()){
		$('textarea').each(function(index){
			$(this).val($(this).val().replace('\n', '<br />'));
		});
	}
}

function checkNotNull(notNull, label){
	var ok = true;
	var dataIn = null;
	try {
		for(var i in notNull){
			dataIn = $('#'+notNull[i]);
			if(dataIn.val().length == 0){
				ok=false;
				dataIn.css({'border':'2px solid red'});
				alert(pleaseFill+label[dataIn.attr('name')]);
				break;
			}
		}
	}
	catch (e){
	}
	return ok;
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

function showTranslateDialog(){
	var translate = $('#translate_dialog');
	translateForm = translate.html();
	translate.dialog({
		bgiframe : true,
		autoOpen : false,
		modal : true,
		title : 'Translate-Form',
		width : 520,
		close : function(event, ui){
			$('#translate_dialog').html(translateForm);
		}
	});
	translate.dialog('open');
}
