$.cleditor.buttons.advanceimage = {
	name: "advanceimage",
	image: "image.png",
	title: "Advance Image",
	command: "inserthtml",
	buttonClick: quoteClick
};
 
$.cleditor.defaultOptions.controls = $.cleditor.defaultOptions.controls.replace("link", "advanceimage link");

function quoteClick(e, data){
	
}
