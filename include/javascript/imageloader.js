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
		title: 'Image Loader'
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
