$.cleditor.buttons.quote = {
	name: "quote",
	image: "quote.png",
	title: "Quote",
	command: "inserthtml",
	buttonClick: quoteClick
};
 
function quoteClick(e, data){
	alert(data.editor.selectedHTML());
	var html = '<blockquote>'+data.editor.selectedHTML()+'</blockquote>';
	data.editor.execCommand(data.command, html, null, data.button);
}
