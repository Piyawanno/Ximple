<?php if(!defined('XIMPLE_CMS')) die();?>
<div class="page_container">
	<?php foreach($item as $id => $value):?>
		<h4><a href="<?=render_uri('page', $value)?>"><?=$value['topic']?></a></h4>
		<?php if(strlen($value['icon'])):?>
			<img src="<?=ROOT_URI.$value['icon']?>" align="left" style="margin-right:10px;">
		<?php endif?>
		<div class="page_tag_content">
			<?=$value['introduction']?>
		</div>
		<p class="page_info">
			<?=$value['publish_time']?> | <?=tt('by')?> <?=render_profile_link($value['writer'])?> | <?=tt('tags')?>
			<?php foreach($value['freetag'] as $key=>$tag):?>
				<a href="<?=SECTION_URI.Q?>page/tag/<?=$tag?>" class="tag"><?=$tag?></a>
			<?php endforeach?>
		</p>
		<p class="page_foot">
			<a>read <!--{ximple_read/page/<?=$id?>}--></a>
			<?php if(isset($value['comment_no'])):?>
				<a><?=tt('comments')?> <?=$value['comment_no']?></a>
			<?php else:?>
				<a><?=tt('no comment')?></a>
			<?php endif?>
			<?php if($value['editable']):?>
				<a href="<?=SECTION_URI.Q?>page_edit/<?=$id?>/parent/<?=$value['parent']?>"><?=tt('edit')?></a>
				<a href="<?=SECTION_URI.Q?>page_drop/<?=$id?>"><?=tt('drop')?></a>
			<?php endif?>
		</p>
		<p style="clear:both;"></p>
	<?php endforeach?>
</div>
