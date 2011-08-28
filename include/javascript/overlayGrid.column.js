var currentOverlayDialog;

function overlayWrite(formID, moduleName){
	var overlayDialog = overlayOpenDialog(formID, moduleName);
	var uri = sectionURI+moduleName+'_overlay_write';
	currentOverlayDialog = overlayDialog;
	$.get(uri, function(data){
		overlayDialog.html(data);
	});
}

function overlaySubmitForm(form, notNull, label){
	if(checkForm(notNull, label)){
		$(form).ajaxSubmit({success : function(){
			currentOverlayDialog.dialog('close');
		}});
	}
	return false;
}

function overlayEdit(formID, moduleName){
	var overlayDialog = overlayOpenDialog(formID, moduleName);
	var uri = sectionURI+moduleName+'_overlay_drop';
	currentOverlayDialog = overlayDialog;
	$.get(uri, function(data){
		overlayDialog.html(data);
	});
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
