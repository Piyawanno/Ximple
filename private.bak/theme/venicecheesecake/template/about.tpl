<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="list_label"><?=$title?></h3>
<p><?=$body?></p>
<?php if($is_admin):?>
<p align="right">
	<a href="<?=SECTION_URI.Q?>about_edit/<?=SECTION?>">edit</a>
</p>
<?php endif?>
