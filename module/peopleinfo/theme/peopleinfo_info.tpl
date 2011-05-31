<?php if(!defined('XIMPLE_CMS')) die();?>
<?php if($show_header):?>
	<h3 class="list_label"><?=$data['topic']?></h3>
<?php endif?>
<p>
	<?=$data['content']?>
</p>

<?php if(count($data['event'])):?>
	<h4><?=tt('Related Events')?></h4>
	<ul>
	<?php foreach($data['event'] as $id => $event):?>
		<li>
			<a href="<?=SECTION_URI.Q.'peopleinfo_event/'.$event['event']['value']?>">
				<?=$event['event']['label']?>
			</a>
		</li>
	<?php endforeach?>
	</ul>
<?php endif?>

<?php if(count($data['people'])):?>
	<h4><?=tt('Related People')?></h4>
	<ul>
	<?php foreach($data['people'] as $id => $people):?>
		<li>
			<a href="<?=SECTION_URI.Q.'peopleinfo/'.$people['people']['value']?>">
				<?=$people['people']['label']?> (<?=$people['relation']['label']?>)
			</a>
		</li>
	<?php endforeach?>
	</ul>
<?php endif?>

<?php if(count($data['file'])):?>
	<h4><?=tt('Related Files')?></h4>
	<ul>
	<?php foreach($data['file'] as $id => $file):?>
		<li>
			<a href="<?=SECTION_URI.Q.'peopleinfo_info_file/'.$id?>" target="_blank">
				<?=$file['short_description']?>
			</a>
		</li>
	<?php endforeach?>
	</ul>
<?php endif?>

<?php if(count($image)):?>
	<h4><?=tt('Related Images')?></h4>
	<?php foreach($image as $id => $image):?>
		<p align="center"><a href="<?=SECTION_URI.Q.'peopleinfo_info_file/'.$id?>" target="_blank">
			<img src="<?=SECTION_URI.Q.'peopleinfo_info_file/'.$id?>" style="max-width:450px;" border="0"/>
			<br />
			<strong><?=$image['short_description']?></strong>
		</a></p>
	<?php endforeach?>
<?php endif?>


<p>
	<strong><?=tt('by')?> : </strong>
	<?=render_profile_link($data['creator'])?> @
	<?=$data['source_date']?> (<?=tt('update').' '.$data['update_time']?>)
</p>
<p>
	<strong><?=tt('tags')?> : </strong>
	<?=render_tag(null, $data['freetag'], 'peopleinfo_info')?>
</p>
<?php if($editable):?>
	<p class="peopleinfo_operation">
		<a href="<?=SECTION_URI.Q.'peopleinfo_info_edit/'.$data['id']?>"><?=tt('edit')?></a>
	</p>
<?php endif?>
