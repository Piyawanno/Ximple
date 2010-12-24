$.cleditor.buttons.advancedimage = {
	name: "advancedimage",
	image: "image.png",
	title: "Advance Image",
	command: "inserthtml",
	buttonClick: advanceImageClick
};

function advanceImageClick(e, data){
	var loader = $("#advancedloader");
	loader.dialog({
		bgiframe: true,
		autoOpen: false,
		height: 560,
		width:480,
		modal: true,
		title: 'Image Loader',
	});
	loader.dialog('open');
}
