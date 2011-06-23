<?php if(!defined('XIMPLE_CMS')) die();?>
<div class="develcard">
	<h3 class="title_label"><?=$data['topic']?></h3>
	<a href="<?=SECTION_URI.Q?>develcard_edit/<?=$data['id']?>"><?=tt('edit')?><a/> | 
	<a href="<?=SECTION_URI.Q?>develcard_drop/<?=$data['id']?>"><?=tt('delete')?><a/>
</div>
