<?php if(!defined('XIMPLE_CMS')) die();?>
<h1 id="list_label"><?=$name?></h1>
<p>
	<?=$description?>
</p>
<p class="operation_bar">
	<?php if($is_editable):?>
		<?=render_operation_link('rtna_building_edit', $id, tt('edit'))?>
		<?=render_operation_link('rtna_building_drop', $id, tt('drop'))?>
	<?php endif?>
</p>
