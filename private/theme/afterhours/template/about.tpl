<?php if(!defined('XIMPLE_CMS')) die();?>
<div>
	<h3 class="list_label" style="display:none;"><?=$title?></h3>
	<p><?=$body?></p>
</div>
<?php if($is_admin):?>
<p align="right">
	<a href="<?=SECTION_URI.Q?>about_edit/<?=SECTION?>">edit</a>
</p>
<?php endif?>
