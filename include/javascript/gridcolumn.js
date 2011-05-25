$(document).ready(function(){
	$(".del_grid_row").click( function(){
		$(this).parent().parent().remove();
		return false;
	});
	
	$(".add_grid_row").click( function(){
		var rel = $(this).attr("rel");
		var tab = $("#grid_form_"+rel);
		tab.append(grid_string[rel]);
		init_del_grid();
	});
	
	$('.email_grid_field').keyup(function(){
		var reg = /^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$/;
		if(!reg.test($(this).val())){
			$('#info_'+$(this).attr('rel')).css({color:'red'});
			$('#info_'+$(this).attr('rel')).html(imgWrong + emailNotOk);
			formLock = true;
		}else{
			$('#info_'+$(this).attr('rel')).html('');
		}
	});
});

function addGridRow(tableID){
	$('#'+tableID).append(gridRowArray[tableID]);
}

function delGridRow(anchor, dropMode){
	$(anchor).parent().parent().remove();
	if(dropMode.length){
		$.get(sectionURI+dropMode, function(){});
	}
}

