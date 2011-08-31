var currentOverlayDialog;

function overlayWrite(formID, moduleName){
	var uri = sectionURI+moduleName+'_overlay_write';
	var overlayDialog = overlayOpenDialog(formID, moduleName);
	alert(uri);
	overlayDialog.css({
		'text-align' : 'left',
	});
	currentOverlayDialog = overlayDialog;
	$.get(uri, function(data){
		overlayDialog.html(data);
	});
	return false;
}

function overlayInsertForm(form, notNull, label){
	if(checkForm(notNull, label)){
		$(form).ajaxSubmit({success : function(data){
			data = data.split('/');
			var dataID = data[1];
			var inputName = 'overlay_grid_'+data[0];
			$(this).append('<input type="hidden" name="'+inputName+'" value="'+dataID+'" />');
			currentOverlayDialog.dialog('close');
		}});
	}
	return false;
}

function overlayEdit(formID, moduleName){
	var overlayDialog = overlayOpenDialog(formID, moduleName);
	var uri = sectionURI+moduleName+'_overlay_edit';
	currentOverlayDialog = overlayDialog;
	$.get(uri, function(data){
		overlayDialog.html(data);
	});
}

function overlayUpdateForm(form, notNull, label){
	if(checkForm(notNull, label)){
		$(form).ajaxSubmit({success : function(data){
			currentOverlayDialog.dialog('close');
		}});
	}
	return false;
}


function overlayDrop(){
	
}

function overlayRefresh(formID, moduleName){
	var overlayTable = $('#overlay_'+formID+'_'+moduleName+'_table');
	var uri = sectionURI+moduleName+'_overlay_refresh';
	overlayTable.html('<img src="'+rootURI+'files/icon/loader.gif"/></div>');
	$.get(uri, function(data){
		overlayTable.html(data);
	});
}

function overlayOpenDialog(formID, moduleName){
	var overlayDialog = $('#overlay_'+formID+'_'+moduleName+'_dialog');
	overlayDialog.dialog({
		bgiframe : true,
		autoOpen : false,
		modal : true,
		width : 520,
	});
	overlayDialog.dialog('open');
	return overlayDialog;
}
