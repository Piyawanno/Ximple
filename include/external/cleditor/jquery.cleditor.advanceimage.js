$.cleditor.buttons.advanceimage = {
	name: "advanceimage",
	image: "image.png",
	title: "Advance Image",
	command: "inserthtml",
	buttonClick: advanceImageClick
};
 
$.cleditor.defaultOptions.controls = $.cleditor.defaultOptions.controls.replace("link", "advanceimage link");

function advanceImageClick(e, data){
	
}
