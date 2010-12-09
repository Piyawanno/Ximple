$.cleditor.buttons.advanceimage = {
	name: "advanceimage",
	image: "code.png",
	title: "Advance Image",
	command: "inserthtml",
	popupName: "code",
	popupClass: "cleditorPrompt",
	popupContent: '',
	buttonClick: advanceImageClick
};
 
$.cleditor.defaultOptions.controls = $.cleditor.defaultOptions.controls.replace("link", "advanceimage link");

function advanceImageClick(e, data){

}
