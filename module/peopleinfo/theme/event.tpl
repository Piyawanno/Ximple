<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="list_label"><?=tt('Information about').' : '.$data['event']?></h3>
<p>
	<?=$data['description']?>
</p>
<p>
	<strong><?=tt('by')?> : </strong>
	<?=render_profile_link($data['creator'])?> @
	</strong><?=$data['occur_date']?> (<?=tt('update').' '.$data['update_time']?>)
</p>
<p>
	<strong><?=tt('place')?> : </strong>
	<a href="<?=SECTION_URI.Q.'peopleinfo_event_place/place/'.$data['place']?>"><?=$data['place']?></a>
	<strong><?=tt('tags')?> : </strong>
	<?=render_tag(null, $data['freetag'], 'peopleinfo_event')?>
</p>
<?php if($editable):?>
	<p class="peopleinfo_operation">
		<a href="<?=SECTION_URI.Q.'peopleinfo_event_edit/'.$data['id']?>"><?=tt('edit')?></a>
	</p>
<?php endif?>
<h3 class="title_label"><?=tt('Related Information')?></h3>
<?=$information?>
