addReady(function(){
	$('.position_table').each(function(index){
		var data = $(this).attr('rel').split(':');
		var passiveCell = $('.position_cell_passive');
		var activeCell = $('.position_cell_active');
		$('#'+data[0]).val(data[1]);
		$('#'+data[0]+'_'+data[1]).css({
			'border' : activeCell.css('border'),
			'background' : activeCell.css('background')
		});
		$('.position_cell').click(function(){
			var value = $(this).attr('rel');
			var cellData = $(this).attr('id');
			var formID = cellData.substring(0, cellData.length - 2);
			for(var i=0; i < 9; i++){
				$('#'+formID+'_'+i).css({
					'border' : passiveCell.css('border'),
					'background' : passiveCell.css('background')
				});
			}
			
			$('#'+formID+'_'+value).css({
				'border' : activeCell.css('border'),
				'background' : activeCell.css('background')
			});
			
			$('#'+data[0]).val(value);
			
		});
	});
});
