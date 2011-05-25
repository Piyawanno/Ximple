$(document).ready(
	$(".add_multi_files").click(function(){
		var rel = $(this).attr("rel");
		var tab = $("#multi_files_"+rel);
		tab.append('<input name="'+rel+'[]" size="40" type="file" style="margin-bottom:10px;"/><br />');
	});
);
