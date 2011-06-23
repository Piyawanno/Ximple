$(document).bind("ready", function(){
	$(".sortable").sortable({
		dropOnEmpty: true
	});
	$(".sortable").disableSelection();
});
