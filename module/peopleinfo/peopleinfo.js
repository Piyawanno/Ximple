function checkPeopleUser(event, ui){
	if(peopleUserNumber == 0 ||  peopleUserNumber == null){
		alert(peopleinfoRoleWarning);
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

$(document).ready(checkPeopleUser);
