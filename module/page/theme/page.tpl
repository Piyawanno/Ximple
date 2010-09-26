<?php if(!defined('XIMPLE_CMS')) die();?>
<div class="page">
	<h3 class="title_label"><?=$topic?></h3>
	<!--{page_pre_index}-->
	<p class="directory_element_label" style="display:none;"><?=tt('index page')?></p>
	<table class="directory_element" id="page_body"><tbody>
	<tr>
		<?php if($show_introduction):?>
			<td><?=$introduction?></td>
			<?php if($show_avatar or $show_category):?>
			<td valign="top" align="right">
				<?php if($show_avatar):?>
					<?=render_avatar($writer)?>
				<?php endif?>
				<?php if($show_category):?>
					<?=render_category_icon($category, 'page')?>
				<?php endif?>
			</td>
			<?php endif?>
		<?php endif?>
	</tr>
	<tr>
		<td colspan="2">
			<?=$content?>
		</td>
		<?php if(($show_avatar or $show_category) and !$show_introduction):?>
			<td valign="top" align="right">
				<?php if($show_avatar):?>
					<?=render_avatar($writer)?>
				<?php endif?>
				<?php if($show_category):?>
					<?=render_category_icon($category, 'blog')?>
				<?php endif?>
			</td>
		<?php endif?>
	</tr>
	</tbody></table>
	<!--{page_post_index}-->
	<?php if(isset($related_page)):?>
		<?=$related_page?>
	<?php endif?>
	<p class="page_info">
		<?=$publish_time?> | <?=tt('by')?> <?=render_profile_link($writer)?> | <?=tt('tags')?>
		<?php foreach($freetag as $key=>$tag):?>
			<a href="<?=SECTION_URI.Q?>page/tag/<?=$tag?>" class="tag"><?=$tag?></a>
		<?php endforeach?>
	</p>
	<p class="page_foot">
		<a>read <!--{ximple_read/page/<?=$id?>}--></a>
		<?php if($editable):?>
			<a href="<?=SECTION_URI.Q?>page_edit/<?=$id?>/parent/<?=$parent?>"><?=tt('edit')?></a>
			<a href="<?=SECTION_URI.Q?>page_drop/<?=$id?>"><?=tt('drop')?></a>
		<?php endif?>
	</p>
	<p align="center" style="magin:20px;">
		<?php if(isset($back)):?>
			<a href="<?=render_uri('page', $back)?>">&#171; <?=$back['topic']?></a> |
		<?php endif?>
		<?php if(isset($next)):?>
			| <a href="<?=render_uri('page', $next)?>"><?=$next['topic']?>&#187; </a>
		<?php endif?>
	</p>
</div>
