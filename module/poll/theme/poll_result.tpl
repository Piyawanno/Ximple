<?php if(!defined('XIMPLE_CMS')) die();?>
<?php foreach($choises as $id => $value):?>
	<div class="poll_choise_label">
		<?=$value['choise']?> (<?=$value['voted_number']?> : <?=$value['percent']?>%)
	</div>
	<div class="poll_choise" style="width:<?=$value['percent']?>%;"></div>
<?php endforeach?>
