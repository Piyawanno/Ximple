$(document).bind("ready", function(){
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
	$(document).trigger('ready');
}

function delGridRow(anchor, dropMode){
	$(anchor).parent().parent().remove();
	if(dropMode.length){
		$.get(sectionURI+dropMode, function(){});
	}
}

