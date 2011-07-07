<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="list_label"><?=tt('Meeting Calendar')?> : <?=$month?></h3>
<?=$write_icon?>
<?=$calendar?>
<h4 class="small_label"><?=tt('List of Meeting')?></h4>
<ul>
<?php foreach($data as $key => $value):?>
	<li>
		<?=render_operation_link('meeting', $key, $value['topic'])?>
		@ <?=$value['start_date']?> - <?=$value['end_date']?>
	</li>
<?php endforeach?>
</ul>
