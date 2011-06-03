$(document).bind("ready", function(){
	$('#peopleinfo_people_name').keyup(function(){
		formLock = true;
		if($(this).val().length < 4){
			$('#info_peopleinfo_people_name').css({color:'red'});
			$('#info_peopleinfo_people_name').html(imgWrong + nameTooShort);
		}else if($(this).attr('rel') == 'install'){
			$('#info_peopleinfo_people_name').html(imgCorrect);
			formLock = false;
		}else{
			var uri = '';
			if(insertPeople) uri = 'userinfo_check_user_exists/login_name/';
			else uri = 'userinfo_check_user_exists/uid/'+uid+'/login_name/';
			$.get(sectionURI+uri+$(this).val(), function(data){
				if(data != 'not exist'){
					$('#info_peopleinfo_people_name').html(imgWrong + nameExists);
				}else{
					$('#info_peopleinfo_people_name').html(imgCorrect);
					formLock = false;
				}
			});
		}
	});
});


function checkPeopleUser(event, ui){
	if(peopleUserNumber == 0 ||  peopleUserNumber == null){
		addPeopleUser();
	}
}

function addPeopleUser(){
	var userDialog = $('#peopleinfo_user_dialog');
	var uri = sectionURI+'peopleinfo_user_write';
	userDialog.load(uri);
	userDialog.dialog({
		bgiframe: true,
		autoOpen: false,
		height: 640,
		width: 560,
		modal: true,
		close : checkPeopleUser,
	});
	userDialog.dialog('open');
	return false;
}

function submitPeopleUserForm(form, notNull, label){
	var userDialog = $('#peopleinfo_user_dialog');
	if(checkForm(notNull, label)){
		var uri = sectionURI+'peopleinfo_user_get';
		$(form).ajaxSubmit({success : function(){
			peopleUserNumber += 1;
			userDialog.dialog('close');
			$('#peopleinfo_people').load(uri);
		}});
	}
	return false;
}
