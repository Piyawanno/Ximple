$.cleditor.buttons.quote = {
	name: "quote",
	image: "quote.png",
	title: "Quote",
	command: "inserthtml",
	buttonClick: quoteClick
};
 
$.cleditor.defaultOptions.controls = $.cleditor.defaultOptions.controls.replace("link", "quote link");

function quoteClick(e, data){
	var html = '<blockquote>'+data.editor.selectedText()+'</blockquote><br />';
	data.editor.execCommand(data.command, html, null, data.button);
}
