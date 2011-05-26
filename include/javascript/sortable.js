$(document).bind("ready", function(){
	$(".sortable_form").sortable({
		dropOnEmpty: true,
	});
	$(".sortable_form").disableSelection();
});
