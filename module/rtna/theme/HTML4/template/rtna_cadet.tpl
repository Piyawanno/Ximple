<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="title_label"><?=$name?> <?=$surname?></h3>
<?=render_avatar($uid)?>
<p>
	<label><?=tt('birth date')?></label> : <?=$birth_date?>
</p>
