<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="list_label"><?=tt('DevelCard Report of').' : '.$title?></h3>

<h4 class="title_label"><?=tt('Created DevelCard')?></h4>
<p><b><?=tt('total submitted DevelCard')?> : <?=$create_data['total']?></b></p>

<h5 class="small_label"><?=tt('sorted by tag')?></h5>
<?php foreach($create_data['tag'] as $key => $value):?>
	<?php $width = 70*$value/$create_data['total'];?>
	<div style="height:18px;width:<?=$width?>%;background:<?=$tag_color?>;display:inline-block;"></div>
	<?=render_operation_link('develcard_report/tag', $key, $key.' ('.$value.')')?>
	<div style="height:3px;"></div>
<?php endforeach?>


<h5 class="small_label"><?=tt('sorted by status')?></h5>
<?php foreach($create_data['status'] as $key => $value):?>
	<?php $width = 70*$value/$create_data['total'];?>
	<div style="height:18px;width:<?=$width?>%;background:<?=$status_color?>;display:inline-block;"></div>
	<?=$status[$key].' ('.$value.')'?>
	<div style="height:3px;"></div>
<?php endforeach?>


<h5 class="small_label"><?=tt('sorted by type')?></h5>
<?php foreach($create_data['type'] as $key => $value):?>
	<?php $width = 70*$value/$create_data['total'];?>
	<div style="height:18px;width:<?=$width?>%;background:<?=$type_color?>;display:inline-block;"></div>
	<?=render_operation_link('develcard_report/type', $key, $type[$key].' ('.$value.')')?>
	<div style="height:3px;"></div>
<?php endforeach?>

<h4 class="title_label"><?=tt('Closed DevelCard')?></h4>

<p><b><?=tt('total submitted DevelCard')?> : <?=$end_data['total']?></b></p>

<h5 class="small_label"><?=tt('sorted by tag')?></h5>
<?php foreach($end_data['tag'] as $key => $value):?>
	<?php $width = 70*$value/$end_data['total'];?>
	<div style="height:18px;width:<?=$width?>%;background:<?=$tag_color?>;display:inline-block;"></div>
	<?=render_operation_link('develcard_report/tag', $key, $key.' ('.$value.')')?>
	<div style="height:3px;"></div>
<?php endforeach?>


<h5 class="small_label"><?=tt('sorted by status')?></h5>
<?php foreach($end_data['status'] as $key => $value):?>
	<?php $width = 70*$value/$end_data['total'];?>
	<div style="height:18px;width:<?=$width?>%;background:<?=$status_color?>;display:inline-block;"></div>
	<?=$status[$key].' ('.$value.')'?>
	<div style="height:3px;"></div>
<?php endforeach?>


<h5 class="small_label"><?=tt('sorted by type')?></h5>
<?php foreach($end_data['type'] as $key => $value):?>
	<?php $width = 70*$value/$end_data['total'];?>
	<div style="height:18px;width:<?=$width?>%;background:<?=$type_color?>;display:inline-block;"></div>
	<?=render_operation_link('develcard_report/type', $key, $type[$key].' ('.$value.')')?>
	<div style="height:3px;"></div>
<?php endforeach?>
