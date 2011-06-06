<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="list_label"><?=tt('Information about').' : '.$data['name']?></h3>
<p align="center">
	<?=$data['avatar']?>
</p>
<p>
	<?=$data['profile']?>
</p>
<p>
	<strong><?=tt('status')?> : </strong>
	<a href="<?=SECTION_URI.Q.'peopleinfo_status/status/'.$data['status']['value']?>"><?=$data['status']['label']?></a>
	<strong><?=tt('tags')?></strong>
	<?=render_tag(null, $data['freetag'], 'peopleinfo')?>
</p>
<?php if($editable):?>
	<p class="peopleinfo_operation">
		<a href="<?=SECTION_URI.Q.'peopleinfo_edit/'.$data['id']?>"><?=tt('edit')?></a>
	</p>
<?php endif?>
<h3 class="title_label"><?=tt('Related Information')?></h3>
<?=$information?>
