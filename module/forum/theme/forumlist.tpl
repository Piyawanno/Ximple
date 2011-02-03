<?php if(!defined('XIMPLE_CMS')) die();?>
<div class="forum">
<div class="list">
	<h4 class="list_label"><?=sprintf(tt('List of Forum Entry in %s'), $forum_name)?></h4>
	<p><?=$forum_description?></p>
	<p><?=render_write_icon('forum_entry_write/forum/'.gg('forum'), sprintf(tt('Write new Forum Entry in %s'), $forum_name))?></p>
	<table width="100%">
		<tr>
			<th></th>
			<th><?=tt('topic')?></th>
			<th><?=tt('reads')?></th>
			<th><?=tt('comments')?></th>
			<th><?=tt('last commented')?></th>
		</tr>
	</table>
	<ul style="float:left;">
		<li><img src="<?=ROOT_URI?>module/forum/theme/default.png" /> : <?=tt('regular topic')?></li>
		<li><img src="<?=ROOT_URI?>module/forum/theme/stick.png" /> : <?=tt('stick topic')?></li>
		<li><img src="<?=ROOT_URI?>module/forum/theme/new.png" /> : <?=tt('new topic')?></li>
	</ul>
	<ul style="float:left;">
		<li><img src="<?=ROOT_URI?>module/forum/theme/lock.png" /> : <?=tt('locked topic (uncommentable)')?></li>
		<li><img src="<?=ROOT_URI?>module/forum/theme/hot.png" /> : <?=tt('hot topic (more than 15 comments)')?></li>
		<li><img src="<?=ROOT_URI?>module/forum/theme/veryhot.png" /> : <?=tt('very hot topic (more than 25 comments)')?></li>
	</ul>
</div>
</div>
