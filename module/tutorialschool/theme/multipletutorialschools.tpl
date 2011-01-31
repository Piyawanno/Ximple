<?php if(!defined('XIMPLE_CMS')) die();?>
<?php foreach($data as $key=>$value):?>
	<div class="tutorialschool">
		<h3 class="title_label"><a href="<?=render_uri('tutorialschool', $value)?>"><?=$value['topic']?></a></h3>
		<table width="100%" ><tbody><tr>
			<td>
				<?php if(strlen($value['icon'])):?>
					<img src="<?=ROOT_URI.$value['icon']?>" align="left" style="margin:10px;" alt="TutorialSchool Icon" />
				<?php endif?>
				<?=$value['intro']?>
			</td>
			<?php if($show_category):?>
				<td valign="top" align="center">
					<?=render_category_icon($value['category'], 'tutorialschool')?>
				</td>
			<?php endif?>
		</tr></tbody></table>
		<p class="tutorialschool_info">
			<?=$value['publish_time']?> | <?=tt('by')?> <?=render_profile_link($value['writer'])?> | <?=tt('tags')?>
			<?=render_tag($value['category'], $value['freetag'], 'tutorialschool')?>
		</p>
		<p class="tutorialschool_foot">
			<a>read <!--{ximple_read/tutorialschool/<?=$value['id']?>}--></a>
			<?php if(isset($value['comment_no'])):?>
				<a><?=tt('comments')?> <?=$value['comment_no']?></a>
			<?php else:?>
				<a><?=tt('no comment')?></a>
			<?php endif?>
			<?php if($value['editable']):?>
				<a href="<?=SECTION_URI.Q?>tutorialschool_edit/<?=$value['id']?>"><?=tt('edit')?></a>
				<a href="<?=SECTION_URI.Q?>tutorialschool_drop/<?=$value['id']?>"><?=tt('drop')?></a>
			<?php endif?>
			<a href="<?=SECTION_URI.Q?>tutorialschool/<?=$value['id']?>"><?=tt('read more')?></a>
		</p>
	</div>
<?php endforeach?>
