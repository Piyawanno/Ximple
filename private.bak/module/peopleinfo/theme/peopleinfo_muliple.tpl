<?php if(!defined('XIMPLE_CMS')) die();?>
<?php foreach($pages as $id => $page):?>
	<h3 onclick="hideSub('info_<?=$id?>')" class="config_head"><?=$page['topic']?></h3>
	<div class="subform" id="info_<?=$id?>" style="display:none;">
		<?=$page['page']?>
	</div>
<?php endforeach?>
