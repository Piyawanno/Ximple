tinyMCEPopup.requireLangPack();

var HighlightDialog = {
	init : function(ed) {
		var node = tinyMCEPopup.editor.selection.getNode();
		var code = node.innerHTML;
		code = code.replace(/<br>/gi, '\n');
		code = code.replace(/\&lt;/, "<");
		code = code.replace(/\&gt;/, ">");
		tinyMCEPopup.resizeToInnerSize();
		if(node.tagName == "PRE"){
			document.getElementById("hightlight_lang").value = node.getAttribute("lang");
			document.getElementById("hightlight_code").value = code;
		}
	},

	insert : function(form) {
		var dom = tinyMCEPopup.editor.dom;
		var code = form.code.value;
		var node = tinyMCEPopup.editor.selection.getNode();
		var editor = tinyMCEPopup.editor;
		code = code.replace(/</gi, "&lt;");
		code = code.replace(/>/gi, "&gt;");
		if(node.tagName == "PRE"){
			node.innerHTML = code;
		}else{
			tinyMCEPopup.execCommand('mceInsertContent', false,	dom.createHTML('pre', {lang : form.language.value}, code));
		}
		tinyMCE.execCommand("mceCleanup");
		var content = editor.getContent();
		content = content.replace(/<p>\&nbsp;<\/p>[\s]*<pre/, "<pre");
		editor.setContent(content);
		tinyMCEPopup.close();
	}
};

tinyMCEPopup.onInit.add(HighlightDialog.init, HighlightDialog);
