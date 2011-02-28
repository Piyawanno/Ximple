<?php if(!defined('XIMPLE_CMS')) die();?>
<div id="forum_content">
	<?php foreach($block['forum_top'] as $key => $item):?>
		<?=$item?>
	<?php endforeach?>
	<?php if(strlen($path)):?>
		<?=triamsob_render_box($path, null, 'forum_box')?>
	<?php endif?>
	<?=$notify?>
	<?=$body?>
	<?php foreach($block['forum_bottom'] as $key => $item):?>
		<?=$item?>
	<?php endforeach?>
</div>
