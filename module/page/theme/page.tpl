<?php if(!defined('XIMPLE_CMS')) die();?>
<?php $span=1;?>
<div class="page_container">
	<h3 class="title_label"><?=$topic?></h3>
	<!--{page_pre_index}-->
	<p class="directory_element_label" style="display:none;"><?=tt('index page')?></p>
	<div class="directory_element" id="page_content">
	<table><tbody>
	<?php if($show_introduction):?>
		<tr>
			<td><?=$introduction?></td>
			<?php if($show_avatar or $show_category):?>
			<?php $span=2;?>
			<td valign="top" align="right">
				<?php if($show_avatar):?>
					<?=render_avatar($writer)?>
				<?php endif?>
				<?php if($show_category):?>
					<?=render_category_icon($category, 'page')?>
				<?php endif?>
			</td>
			<?php endif?>
		</tr>
	<?php endif?>
	<tr>
		<td colspan="<?=$span?>">
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
	</div>
	<!--{page_post_index}-->
	<?php if(isset($related_page)):?>
		<?=$related_page?>
	<?php endif?>
	<p class="page_info">
		<?=$publish_time?> |
		<?php if(strlen($author_name)) :?>
			<?=tt('written by')?> <?=$author_name?> |
			<?=tt('edited by')?> <?=render_profile_link($writer)?> |
		<?php else :?>
			<?=tt('by')?> <?=render_profile_link($writer)?> |
		<?php endif?>
		<?=tt('tags')?>
		<?php foreach($freetag as $key=>$tag):?>
			<a href="<?=SECTION_URI.Q?>page/tag/<?=$tag?>" class="tag"><?=$tag?></a>
		<?php endforeach?>
	</p>
	<p class="page_foot">
		<a>read <!--{ximple_read/page/<?=$id?>}--></a>
		<a href="<?=SECTION_URI.Q?>page_print/<?=$id?>/parent/<?=$parent?>" onclick="ximplePrint(this); return false;"><?=tt('print')?></a>
		<?php if($editable):?>
			<a href="<?=SECTION_URI.Q?>page_edit/<?=$id?>/parent/<?=$parent?>"><?=tt('edit')?></a>
			<a href="<?=SECTION_URI.Q?>page_drop/<?=$id?>"><?=tt('drop')?></a>
		<?php endif?>
	</p>
	<p style="magin:20px;text-align:center;">
		<?php if(isset($back)):?>
			<a href="<?=render_uri('page', $back)?>">&#171; <?=$back['topic']?></a> |
		<?php endif?>
		<?php if(isset($next)):?>
			| <a href="<?=render_uri('page', $next)?>"><?=$next['topic']?>&#187; </a>
		<?php endif?>
	</p>
</div>
