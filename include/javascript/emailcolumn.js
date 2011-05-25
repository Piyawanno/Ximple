$(document).ready(function(){
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
				if(isInstalled){
					$.get(uri+$(this).val(), function(data){
						if(data != 'not exist'){
							exist = true;
							formLock = true;
							$('#info_user_email').css({color:'red'});
							$('#info_user_email').html(imgWrong + emailExists);
						}
					});
				}else{
					exist = false;
				}
			}
			if(!exist){
				$('#info_'+$(this).attr('id')).html(imgCorrect);
				formLock = false;
			}else{
				formLock = true;
			}
		}
	});
});
