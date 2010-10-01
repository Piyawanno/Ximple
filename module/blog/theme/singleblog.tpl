<?php if(!defined('XIMPLE_CMS')) die();?>
<div class="blog">
	<h3 class="title_label"><?=$topic?></h3>
	<table><tbody>
	<tr>
		<td><?=$intro?></td>
		<?php if(cc('blog_show_avatar') or cc('blog_show_category')):?>
			<td valign="top" align="right">
				<?php if(cc('blog_show_avatar')):?>
					<?=render_avatar($writer)?>
				<?php endif?>
				<?php if(cc('blog_show_category')):?>
					<?=render_category_icon($category, 'blog')?>
				<?php endif?>
			</td>
		<?php endif?>
	</tr>
	<tr>
		<?php if(cc('blog_show_avatar') or cc('blog_show_category')):?>
			<td colspan="2">
		<?php else:?>
			<td>
		<?php endif?>
			<?=$content?>
		</td>
	</tr>
	</tbody></table>
	<p class="blog_info">
		<?=$publish_time?> | <?=tt('by')?> <?=render_profile_link($writer)?> | <?=tt('tags')?>
		<?php foreach($freetag as $key=>$tag):?>
			<a href="<?=SECTION_URI.Q?>blog/tag/<?=$tag?>" class="tag"><?=$tag?></a>
		<?php endforeach?>
		
	</p>
	<p class="blog_foot">
		<a>read <!--{ximple_read/blog/<?=$id?>}--></a>
		<a href="<?=SECTION_URI.Q?>blog_print/<?=$id?>" onclick="ximplePrint(this); return false;"><?=tt('print')?></a>
		<?php if($editable):?>
			<a href="<?=SECTION_URI.Q?>blog_edit/<?=$id?>"><?=tt('edit')?></a>
			<a href="<?=SECTION_URI.Q?>blog_drop/<?=$id?>"><?=tt('drop')?></a>
		<?php endif?>
	</p>
	<p style="magin:20px;text-align:center;">
		<?php if(count($back)):?>
			<a href="<?=render_uri('blog', $back[0])?>">&#171; <?=$back[0]['topic']?></a> | 
		<?php endif?>
		<?php if(count($next)):?>
			| <a href="<?=render_uri('blog', $next[0])?>"><?=$next[0]['topic']?> &#187;</a>
		<?php endif?>
	</p>
</div>
