var currentData = null;
$.cleditor.buttons.icon = {
	name: "icon",
	css: {
		background:'url('+rootURI+'include/external/cleditor/images/icon.gif) no-repeat 4px 4px',
	},
	title: "Insert Icon",
	command: "insertimage",
	popupName: "Icon",
	popupHover: true,
	popupClick: function(e, data) {
		data.value = currentData;
	}
};


var content = '<div style="max-width:150px;">';
for(i in iconArray){
	content += '<a href="#" onclick="return iconClick(\''+iconArray[i]+'\')"><img src="'+iconArray[i]+'" border="0"/>';
}
content += '</div>';
$.cleditor.buttons.icon.popupContent = content;


function iconClick(src){
	currentData = src;
	return false;
}
