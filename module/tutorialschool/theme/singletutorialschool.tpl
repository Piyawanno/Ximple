<?php if(!defined('XIMPLE_CMS')) die();?>
<div class="tutorialschool">
	<h3 class="title_label"><?=$topic?></h3>
	<table  style="width:100%;"><tbody>
	<tr>
		<td>
			<?php if(strlen($icon)):?>
				<img src="<?=ROOT_URI.$icon?>" align="left" style="margin:10px;" alt="TutorialSchool Icon" />
			<?php endif?>
			<?=$intro?>
		</td>
		<?php if($show_avatar or $show_category):?>
			<td valign="top" align="center">
				<?php if($show_avatar):?>
					<?=render_avatar($writer)?>
				<?php endif?>
				<?php if($show_category):?>
					<?=render_category_icon($category, 'tutorialschool')?>
				<?php endif?>
			</td>
		<?php endif?>
	</tr>
	<tr>
		<td colspan="2">
			<?=$content?>
		</td>
	</tr>
	</tbody></table>
	<p class="tutorialschool_info">
		<?=$publish_time?> | <?=tt('by')?> <?=render_profile_link($writer)?> | <?=tt('tags')?>
		<?=render_tag($category, $freetag, 'tutorialschool')?>
	</p>
	<p class="tutorialschool_foot">
		<a>read <!--{ximple_read/tutorialschool/<?=$id?>}--></a>
		<a href="<?=SECTION_URI.Q?>tutorialschool_print/<?=$id?>" onclick="ximplePrint(this); return false;"><?=tt('print')?></a>
		<?php if($editable):?>
			<a href="<?=SECTION_URI.Q?>tutorialschool_edit/<?=$id?>"><?=tt('edit')?></a>
			<a href="<?=SECTION_URI.Q?>tutorialschool_drop/<?=$id?>"><?=tt('drop')?></a>
		<?php endif?>
	</p>
	<p style="magin:20px;text-align:center;">
		<?php if(count($back) and $show_sibling):?>
			<a href="<?=render_uri('tutorialschool', $back[0])?>">&#171; <?=$back[0]['topic']?></a> | 
		<?php endif?>
		<?php if(count($next) and $show_sibling):?>
			| <a href="<?=render_uri('tutorialschool', $next[0])?>"><?=$next[0]['topic']?> &#187;</a>
		<?php endif?>
	</p>
</div>
