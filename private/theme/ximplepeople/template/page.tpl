<?php if(!defined('XIMPLE_CMS')) die();?>
<?php $span=1;?>
<div class="page_container">
	<h3 class="title_label"><?=$topic?></h3>
	<!--{page_pre_index}-->
	<?=$content?>
	<!--{page_post_index}-->
	<?php if(isset($related_page)):?>
		<?=$related_page?>
	<?php endif?>
	<?php if($editable):?>
	<p>
		<a href="<?=SECTION_URI.Q?>page_edit/<?=$id?>/parent/<?=$parent?>"><?=tt('edit')?></a>
		<a href="<?=SECTION_URI.Q?>page_drop/<?=$id?>"><?=tt('drop')?></a>
	</p>
	<?php endif?>
</div>
