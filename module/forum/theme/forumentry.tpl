<?php if(!defined('XIMPLE_CMS')) die();?>
<div class="forum">
	<h3 class="title_label"><?=$topic?></h3>
	<table style="width:100%;"><tbody>
	<tr>
		<td>
			<?=$content?>
		</td>
		<?php if($show_avatar or $show_level):?>
			<td valign="top" align="center">
			<?php if($show_avatar):?>
				<?=render_avatar($writer)?>
			<?php endif?>
			<?php if($show_level):?>
				<?=forum_render_level($writer['id'])?>
			<?php endif?>
			</td>
		<?php endif?>
	</tr>
	</tbody></table>
	<p class="forum_info">
		<?=$write_time?> | <?=tt('by')?> <?=render_profile_link($writer)?>
	</p>
	<p class="forum_foot">
		<a>read <!--{ximple_read/forum_entry/<?=$id?>}--></a>
		<a href="<?=SECTION_URI.Q?>forum_print/<?=$id?>" onclick="ximplePrint(this); return false;"><?=tt('print')?></a>
		<?php if($editable):?>
			<a href="<?=SECTION_URI.Q?>forum_entry_edit/<?=$id?>"><?=tt('edit')?></a>
			<a href="<?=SECTION_URI.Q?>forum_entry_drop/<?=$id?>"><?=tt('drop')?></a>
		<?php endif?>
	</p>
</div>
