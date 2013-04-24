<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="list_label"><?=$title?></h3>
<?php foreach($data as $key => $value):?>
	<?php $width = 70*$value['value']/$total;?>
	<div style="height:18px;width:<?=$width?>%;background:<?=$color?>;display:inline-block;"></div>
	<?=render_operation_link('develcard_report', $key, $value['label'].' ('.$value['value'].')')?>
	<div style="height:3px;"></div>
<?php endforeach?>

