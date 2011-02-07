<?php if(!defined('XIMPLE_CMS')) die();?>
<div class="forum">
	<h3 class="title_label"><?=$topic?></h3>
	<table style="width:100%;"><tbody>
	<tr>
		<td>
			<?=$content?>
		</td>
		<?php if($show_avatar):?>
			<td valign="top" align="center">
				<?=render_avatar($writer)?>
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
			<a href="<?=SECTION_URI.Q?>forum_edit/<?=$id?>"><?=tt('edit')?></a>
			<a href="<?=SECTION_URI.Q?>forum_drop/<?=$id?>"><?=tt('drop')?></a>
		<?php endif?>
	</p>
</div>
