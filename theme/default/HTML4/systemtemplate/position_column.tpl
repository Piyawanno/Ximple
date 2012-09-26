<?php if(!defined('XIMPLE_CMS')) die();?>
<table id="<?=$form_id?>_table" class="position_table" rel="<?=$form_id.':'.$data?>">
	<tr>
		<td class="position_cell" id="<?=$form_id?>_0" rel="0"><?=tt('top left')?></td>
		<td class="position_cell" id="<?=$form_id?>_1" rel="1"><?=tt('top middle')?></td>
		<td class="position_cell" id="<?=$form_id?>_2" rel="2"><?=tt('top right')?></td>
	</tr>
	
	<tr>
		<td class="position_cell" id="<?=$form_id?>_3" rel="3"><?=tt('center left')?></td>
		<td class="position_cell" id="<?=$form_id?>_4" rel="4"><?=tt('center middle')?></td>
		<td class="position_cell" id="<?=$form_id?>_5" rel="5"><?=tt('center right')?></td>
	</tr>
	
	<tr>
		<td class="position_cell" id="<?=$form_id?>_6" rel="6"><?=tt('bottom left')?></td>
		<td class="position_cell" id="<?=$form_id?>_7" rel="7"><?=tt('bottom middle')?></td>
		<td class="position_cell" id="<?=$form_id?>_8" rel="8"><?=tt('bottom center')?></td>
	</tr>
</table>
<div class="position_cell_active" style="display:none;"></div>
<div class="position_cell_passive" style="display:none;"></div>
