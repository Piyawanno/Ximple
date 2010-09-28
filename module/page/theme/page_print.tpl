<?php if(!defined('XIMPLE_CMS')) die();?>
<?php foreach($sort as $key => $value):?>
	<h2><?=$parent_name?></h2>
	<h3><?=$data[$value]['topic']?></h3>
	<?=$data[$value]['content']?>
<?php endforeach?>
