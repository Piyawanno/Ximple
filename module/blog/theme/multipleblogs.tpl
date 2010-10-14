<?php if(!defined('XIMPLE_CMS')) die();?>
<?php foreach($data as $key=>$value):?>
	<div class="blog">
		<h3 class="title_label"><a href="<?=render_uri('blog', $value)?>"><?=$value['topic']?></a></h3>
		<table width="100%" ><tbody><tr>
			<td><?=$value['intro']?></td>
			<?php if($show_category):?>
				<td valign="top" align="center">
					<?=render_category_icon($value['category'], 'blog')?>
				</td>
			<?php endif?>
		</tr></tbody></table>
		<p class="blog_info">
			<?=$value['publish_time']?> | <?=tt('by')?> <?=render_profile_link($value['writer'])?> | <?=tt('tags')?>
			<?php foreach($value['freetag'] as $tag):?>
				<a href="<?=SECTION_URI.Q?>blog/tag/<?=$tag?>" class="tag"><?=$tag?></a>
			<?php endforeach?>
		</p>
		<p class="blog_foot">
			<a>read <!--{ximple_read/blog/<?=$value['id']?>}--></a>
			<?php if(isset($value['comment_no'])):?>
				<a><?=tt('comments')?> <?=$value['comment_no']?></a>
			<?php else:?>
				<a><?=tt('no comment')?></a>
			<?php endif?>
			<?php if($value['editable']):?>
				<a href="<?=SECTION_URI.Q?>blog_edit/<?=$value['id']?>"><?=tt('edit')?></a>
				<a href="<?=SECTION_URI.Q?>blog_drop/<?=$value['id']?>"><?=tt('drop')?></a>
			<?php endif?>
			<a href="<?=SECTION_URI.Q?>blog/<?=$value['id']?>"><?=tt('read more')?></a>
		</p>
	</div>
<?php endforeach?>
