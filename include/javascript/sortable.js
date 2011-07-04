$(document).bind("ready", function(){
	initForm($(".sortable"), function(form){
		form.sortable({
			dropOnEmpty: true
		});
		form.disableSelection();
	});
});
