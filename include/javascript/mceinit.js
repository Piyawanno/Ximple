// Notice: The simple theme does not use all options some of them are limited to the advanced theme
	var plugins;
	if(navigator.appName == "Netscape"){
		plugins = "autosave,table,advimage,emotions,iespell,inlinepopups,media,highlight";
	}else{
		plugins = "autosave,table,advimage,emotions,iespell,inlinepopups,media";
	}
	tinyMCE.init( {
		editor_selector : "shorttext",
		mode : "textareas",
		theme : "advanced",
		plugins : plugins,
		theme_advanced_buttons1 : "code,highlight,bold,italic,underline,link,anchor,unlink,forecolor,backcolor,blockquote,emotions,bullist,help",
 		theme_advanced_buttons2 : "",
 		theme_advanced_buttons3 : "",
		theme_advanced_toolbar_location : "top",
		theme_advanced_toolbar_align : "left",
		remove_script_host : false,
		theme_advanced_resizing : true,
		relative_urls: false,
		apply_source_formatting : false,
		theme_advanced_resizing : true,
	});
	
	tinyMCE.init( {
		editor_selector : "usershorttext",
		mode : "textareas",
		theme : "advanced",
		plugins : plugins,
		theme_advanced_buttons1 : "code,highlight,image,media,bold,italic,underline,link,anchor,unlink,forecolor,backcolor,blockquote,emotions,bullist,help",
 		theme_advanced_buttons2 : "",
 		theme_advanced_buttons3 : "",
		theme_advanced_toolbar_location : "top",
		theme_advanced_toolbar_align : "left",
		remove_script_host : false,
		theme_advanced_resizing : true,
		relative_urls: false,
		apply_source_formatting : false,
		theme_advanced_resizing : true,
	});

	tinyMCE.init( {
		editor_selector : "text",
		mode : "textareas",
		theme : "advanced",
		extended_valid_elements : "iframe[src|width|height|name|align]",
		plugins : plugins,
		theme_advanced_buttons1 : "code,highlight,bold,italic,underline,separator,link,unlink,anchor,separator,forecolor,backcolor,emotions,separator, justifyleft,justifycenter,justifyright,,outdent,indent,blockquote,table,charmap,hr",
 		theme_advanced_buttons2 : "image,media,separator,bullist,numlist,formatselect,fontsizeselect,seperator,sub,sup,separator,cleanup,help",
 		theme_advanced_buttons3 : "",
		theme_advanced_toolbar_location : "top",
		theme_advanced_toolbar_align : "left",
		remove_script_host : false,
		theme_advanced_resizing : true,
		relative_urls: false,
		apply_source_formatting : false,
		remove_linebreaks : true,
		theme_advanced_resizing : true,
		cleanup_on_startup : false,
		oninit : 'preElementFormat',
	});
