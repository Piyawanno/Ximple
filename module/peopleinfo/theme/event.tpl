<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="list_label"><?=tt('Information about').' : '.$data['event']?></h3>
<p>
	<strong><?=tt('place')?> : </strong><?=$data['place']?>
</p>
<p>
	<strong><?=tt('date')?> : </strong><?=$data['occur_date']?>
</p>
<p>
	<?=$data['description']?>
</p>
<p>
	<strong><?=tt('tags')?> : </strong>
	<?=render_tag(null, $data['freetag'], 'peopleinfo_event')?>
</p>
<?=$information?>
