var currentPath = null;
var currentLoaderID = null;
var currentWidth = null;
var currentHeight = null;

function showImageLoader(loaderID, path, width, height, isResize){
	currentLoaderID = loaderID;
	currentPath = path;
	currentWidth = width;
	currentHeight = height;
	var loader = $('#loader_'+loaderID);
	loader.dialog({
		bgiframe: true,
		autoOpen: false,
		height: 560,
		width:520,
		modal: true,
		title: 'Image Loader'
	});
	var uri = sectionURICommon+'?mode=imageloader_simple&dir='+path;
	uri += '&loader_id='+loaderID+'&width='+width+'&height='+height+'&isResize'+isResize;
	$.get(uri, function(data){
		loader.html(data);
	}, 'html');
	loader.dialog('open');
}

function submitImageLoader(){
	$('#image_upload_form').ajaxSubmit({success : refreshImageLoader});
	return false;
}

function refreshImageLoader(data){
	var loader = $('#loader_'+currentLoaderID);
	var uri = sectionURICommon+'?mode=imageloader_simple&dir='+currentPath;
	uri += '&loader_id='+currentLoaderID+'&width='+currentWidth+'&height'+currentHeight;
	$.get(uri, function(data){
		loader.html(data);
		$('#loader_info').html(uploadSuccess);
		loader.dialog('open');
	}, 'html');
}

function loaderChangeImage(loaderID, src, rel){
	$('#input_'+loaderID).val(rel);
	$('#image_'+loaderID).attr('src', src);
	$('#loader_'+loaderID).dialog('close');
}
