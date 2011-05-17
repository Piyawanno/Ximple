<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="list_label"><?=tt('Information about').' : '.$data['people']['login_name']?></h3>
<?=render_avatar($data['people'], true)?>
<p>
	<strong><?=tt('status')?> : </strong><?=$data['status']?>
</p>
<p>
	<?=$data['profile']?>
</p>
<p>
	<?=tt('tags')?>
	<?=render_tag(null, $data['freetag'], 'peopleinfo')?>
</p>
<?=$information?>
