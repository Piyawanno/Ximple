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

