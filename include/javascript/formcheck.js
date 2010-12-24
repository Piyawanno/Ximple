var grid_string = new Array();
var files_string = new Array();
var captchaLock = false;
var initedJQuery = false;
var imgCorrect = '<img style="margin-left:15px;margin-right:10px;padding:0;" src="'+rootURI+'files/icon/correct.png" />';
var imgWrong = '<img style="margin-left:15px;margin-right:10px;padding:0;" src="'+rootURI+'files/icon/stop.png" />';
var formLock = false;

function changeCaptcha(captchaKey){
	captchaLock = true;
	generateTime = generateTime+10;
	var img = document.getElementById("captcha_img_"+captchaKey);
	img.src = sectionURI+'captcha/gentime/'+(generateTime);
	$("#captcha_input_"+captchaKey).attr('value', '');
	$("#captcha_info_"+captchaKey).html('');
}

function checkCaptcha(captchaKey){
	$.get(sectionURI+'captcha_check/value/'+($('#captcha_input_'+captchaKey).val())+'/gentime/'+generateTime, function(data){
		if(data.substring(0,6) == "<code>"){
			$('#captcha_info_'+captchaKey).html(imgCorrect + captchaCorrect);
			$('#captcha_info_'+captchaKey).attr('color', 'green');
			$('#captcha_code_'+captchaKey).attr('value', data);
			$('#captcha_gentime_'+captchaKey).attr('value', generateTime);
			captchaLock = false;
		}else{
			$('#captcha_info_'+captchaKey).html(imgWrong + captchaWrong);
			$('#captcha_info_'+captchaKey).attr('color', 'red');
			captchaLock = true;
		}
	})
}

$(document).ready(function (){
	$(".text").cleditor({
    	height		:	'400px',
    	width		:	'100%',
    	controls	:	"bold italic underline strikethrough subscript superscript | font size " +
						"style | color highlight removeformat | bullets numbering | outdent " +
						"indent quote | alignleft center alignright justify | undo redo | "+
						"rule advancedimage icon table link unlink | cut copy paste pastetext | print code source"
    });
    
    $(".shorttext").cleditor({
    	height		:	'400px',
    	width		:	'100%',
    	controls	:	"bold italic underline strikethrough bullets numbering quote link unlink icon paste pastetext source"
    });
    
	initDelGrid();
	$(".plaintext_container").resizable({
		minHeight: 120,
		minWidth: 400,
		resize : function(){
			$(this).children('textarea').width($(this).width() - 15).height($(this).height() - 30);
		},
	});

	$(".calendar_form").datepicker({ 
		dateFormat: "d MM yy"
	});

	$(".add_grid_row").click( function(){
		var rel = $(this).attr("rel");
		var tab = $("#grid_form_"+rel);
		tab.append(grid_string[rel]);
		init_del_grid();
	});

	$(".add_multi_files").click(function(){
		var rel = $(this).attr("rel");
		var tab = $("#multi_files_"+rel);
		tab.append('<input name="'+rel+'[]" size="40" type="file" style="margin-bottom:10px;"/><br />');
	});
	
	$('.checkedit').change(function(){
		var obj = $('#'+$(this).attr('rel'));
		obj.attr('disabled', !obj.attr('disabled'))
		
	});
	
	$(".sortable_form").sortable({
		dropOnEmpty: true,
	});
	
	$(".sortable_form").disableSelection();
	
	$('.auto_complete').keyup(function(){
		var words = $(this).val().split(',');
		var lastWord = jQuery.trim(words[words.length-1]);
		if(lastWord.length){
			var option = $('#complete_option');
			var pos = $(this).offset();
			option.css({
				 top: pos.top + $(this).height() + 4,
				 left: pos.left,
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
	
	$('body').click(function(){
		$('#complete_option').hide();
	});
	
	$('#user_login_name').keyup(function(){
		formLock = true;
		if($(this).val().length < 4){
			$('#info_user_login_name').css({color:'red'});
			$('#info_user_login_name').html(imgWrong + nameTooShort);
		}else if($(this).attr('rel') == 'install'){
			$('#info_user_login_name').html(imgCorrect);
			formLock = false;
		}else{
			var uri = '';
			if(insertUser) uri = 'userinfo_check_user_exists/login_name/';
			else uri = 'userinfo_check_user_exists/uid/'+uid+'/login_name/';
			$.get(sectionURI+uri+$(this).val(), function(data){
				if(data != 'not exist'){
					$('#info_user_login_name').html(imgWrong + nameExists);
				}else{
					$('#info_user_login_name').html(imgCorrect);
					formLock = false;
				}
			});
		}
	});
	
	$('.email_field').keyup(function(){
		var reg = /^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$/;
		if(!reg.test($(this).val())){
			$('#info_'+$(this).attr('id')).css({color:'red'});
			$('#info_'+$(this).attr('id')).html(imgWrong + emailNotOk);
			formLock = true;
		}else{
			var exist = false;
			if($(this).attr('id') == 'user_email'){
				var uri;
				if(insertUser){
					uri = sectionURI+'userinfo_check_email_exists/email/';
				}else{
					uri = sectionURI+'userinfo_check_email_exists/uid/'+uid+'/email/';
				}
				$.get(uri+$(this).val(), function(data){
					if(data != 'not exist'){
						exist = true;
						formLock = true;
						$('#info_user_email').css({color:'red'});
						$('#info_user_email').html(imgWrong + emailExists);
					}
				});
			}
			if(!exist){
				$('#info_'+$(this).attr('id')).html(imgCorrect);
				formLock = false;
			}else{
				formLock = true;
			}
		}
	});
	
	$('#user_password').keyup(function(){
		var len = $(this).val().length;
		
		var tooShort = (len > 0 && len < 8) || (len <= 0 && insertUser);
		if(tooShort){
			$('#info_user_password').css({color:'red'});
			$('#info_user_password').html(imgWrong + passwdTooShort);
			formLock = true;
		}else{
			$('#info_user_password').html(imgCorrect);
			formLock = false;
		}
		
		if(!tooShort && len){
			checkPasswdStrength();
			checkPasswdConfirm();
		}
		
	});
	$('#user_confirm_password').keyup(checkPasswdConfirm);
	
	$('#section_name').keyup(function(){
		formLock = true;
		if($(this).val().length < 4){
			$('#info_section_name').css({color:'red'});
			$('#info_section_name').html(imgWrong + nameTooShort);
		}else{
			var uri = sectionURI+'sectioninfo_check_name_exists/';
			if(sectionInsert) uri += 'name/';
			else uri += 'sid/'+sectionUpdateID+'/name/';
			$.get(uri+$(this).val(), function(data){
				if(data != 'not exist'){
					$('#info_section_name').html(imgWrong + nameExists);
				}else{
					$('#info_section_name').html(imgCorrect);
					formLock = false;
				}
			});
		}
	});
	
	$('#section_path').keyup(function(){
		formLock = true;
		var reg = /^[a-zA-Z0-9_\-]+$/;
		
		if($(this).val().length < 4){
			$('#info_section_path').css({color:'red'});
			$('#info_section_path').html(imgWrong + pathTooShort);
		}else if(!$(this).val().match(reg)){
			$('#info_section_path').css({color:'red'});
			$('#info_section_path').html(imgWrong + pathNotConformed);
		}else{
			var uri = sectionURI+'sectioninfo_check_path_exists/';
			if(sectionInsert) uri += 'path/';
			else uri += 'sid/'+sectionUpdateID+'/path/';
			$.get(uri+$(this).val(), function(data){
				if(data != 'not exist'){
					$('#info_section_path').html(imgWrong + pathExists);
				}else{
					$('#info_section_path').html(imgCorrect);
					formLock = false;
				}
			});
		}
	});
});

function checkPasswdStrength(){
	var len = $('#user_password').val().length;
	var passwd = $('#user_password').val();
	var strength = 0;
	var matchNumber = passwd.match(/\d+/);
	var matchBigChar = passwd.match(/[A-Z]+/);
	var matchSmallChar = passwd.match(/[a-z]+/);
	var matchSpecial = passwd.match(/\W/);
	if(matchNumber && matchBigChar && matchSmallChar && matchSpecial){
		if(len >= 12){
			$('#info_user_password').css({color:'#490'});
			$('#info_user_password').append(passwdVeryStrong);
		}else{
			$('#info_user_password').css({color:'#25a'});
			$('#info_user_password').append(passwdStrong);
		}
	}else if(matchNumber && matchBigChar && matchSmallChar){	
		$('#info_user_password').css({color:'#a80'});
		$('#info_user_password').append(passwdMedium);
	}else{
		$('#info_user_password').css({color:'#d40'});
		$('#info_user_password').append(passwdWeak);
	}
}

function checkPasswdConfirm(){
	if($('#user_password').val() != $('#user_confirm_password').val()){
		$('#info_user_confirm_password').css({color:'red'});
		$('#info_user_confirm_password').html(imgWrong + passwdMismatch);
		formLock = true;
	}else{
		$('#info_user_confirm_password').html(imgCorrect);
		formLock = false;
	}
}

function initDelGrid(){
	$(".del_grid_row").click( function(){
		$(this).parent().parent().remove();
		return false;
	});
}

function formCheck(notNull, label){
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

function checkNotNull(notNull, label){
	var ok = true;
	try {
		for(var i in notNull){
			if(notNull[i].length){
				var dataIn = document.getElementsByName(notNull[i])[0];
				if(dataIn.value.length == 0 && dataIn.className != "text" &&
				dataIn.className != "shorttext" && dataIn.className != "usershorttext"){
					ok=false;
					alert(pleaseFill+label[notNull[i]]);
					dataIn.style.border = "2px solid red";
					break;
				}
			}
		}
	}
	catch (e){
	}
	return ok;
}

function checkAllCheckBox(className){
	$('.checkbox_'+className).attr('checked', 'checked');
}

function checkNoneCheckBox(className){
	$('.checkbox_'+className).attr('checked', '');
}

function encryptPasswd(){
	if(!insertUser && $('#user_password').val().length == 0){
		alert(passwdNotChange);
	}
	if($('#user_password').val() == $('#user_confirm_password').val()){
		var passwd = $('#user_password').val();
		if(passwd.length){
			$('#user_password').val(hex_sha1(passwd));
			$('#user_confirm_password').val('');
		}
		$('#user_login_name_hash').val($('#user_login_name').val());
	}
}

var currentPath = null;
var currentLoaderID = null;

function showImageLoader(loaderID, path){
	currentLoaderID = loaderID;
	currentPath = path;
	var loader = $('#loader_'+loaderID);
	loader.dialog({
		bgiframe: true,
		autoOpen: false,
		height: 560,
		width:480,
		modal: true,
		title: 'Image Loader',
	});
	var uri = sectionURICommon+'?mode=imageloader_simple&dir='+path+'&loader_id='+loaderID;
	$.get(uri, function(data){
		loader.html(data);
	});
	loader.dialog('open');
}

function submitImageLoader(){
	$('#image_upload_form').ajaxSubmit({success : refreshImageLoader});
	return false;
}

function refreshImageLoader(){
	var loader = $('#loader_'+currentLoaderID);
	var uri = sectionURICommon+'?mode=imageloader_simple&dir='+currentPath+'&loader_id='+currentLoaderID;
	$.get(uri, function(data){
		loader.html(data);
		$('#loader_info').html(uploadSuccess);
		loader.dialog('open');
	});
}

function loaderChangeImage(loaderID, src, rel){
	$('#input_'+loaderID).val(rel);
	$('#image_'+loaderID).attr('src', src);
	$('#loader_'+loaderID).dialog('close');
}

function addFileInput(formID, formName){
	$('#'+formID+' ul').append('<li><input type="file" name="'+formName+'[]" size="35" ></li>');
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

// Not verified

function getAntikey(crypt1,crypt2,genTime){
	http.open("GET", rootURI+"ajax.php?mode=_ajax_get_antikey&section="+sectionID+"&crypt1="+crypt1+"&crypt2="+crypt2+"&gen_time="+genTime,true);
	http.onreadystatechange = getAntikeyResponse;
	http.send(null);
}

function getAntikeyResponse(){
	if (http.readyState == 4) {
		if(http.responseText == "Mask as Spam"){
			window.location.href = "#antikey_begin_form";
			alert(wrongAntiKeyMessage);
			location.reload(true);
		}else{
			var realAntikey = document.getElementById("antikey_form");
			var preAntikey = document.getElementById("antikey_pre_form");
			
			preAntikey.style.display = "none";
			realAntikey.style.display = "block";
			
			var cryptMatrix = http.responseText.split(",");
			document.getElementsByName("crypt1")[0].value = cryptMatrix[0];
			document.getElementsByName("crypt2")[0].value = cryptMatrix[1];
			document.getElementsByName("crypt3")[0].value = cryptMatrix[2];
			document.getElementsByName("crypt_time")[0].value = cryptMatrix[3];
		}
	}
}


