if (!isIE7()) {
	$(document).bind("ready", function(){
		$(".text").cleditor({
			height		:	'400px',
			width		:	'100%',
			controls	:	"bold italic underline strikethrough subscript superscript | font size " +
							"style | color highlight removeformat | bullets numbering | outdent " +
							"indent quote | alignleft center alignright justify | undo redo | "+
							"rule image advancedimage icon table link unlink | cut copy paste pastetext | print code source"
		});
	
		$(".shorttext").cleditor({
			height		:	'250px',
			width		:	'100%',
			controls	:	"bold image italic underline strikethrough bullets numbering quote link unlink icon paste pastetext source"
		});
	
		$(".usershorttext").cleditor({
			height		:	'250px',
			width		:	'100%',
			controls	:	"bold image advancedimage italic underline strikethrough bullets numbering quote link unlink icon paste pastetext code source"
		});
	});
}
