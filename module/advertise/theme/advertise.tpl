<?php if(!defined('XIMPLE_CMS')) die();?>
<h3><a href="<?=SECTION_URI.Q.'advertise_redirect/'.$id?>"><?=$name?></a></h3>
<img src="<?=ROOT_URI.$banner?>" alt="<?=$name?>"/>
<p><label><?=tt('position')?></label> : <?=$position?></p>
<p><label><?=tt('clicks')?></label> : <!--{ximple_read/advertise/<?=$id?>}--></p>
<p><label><?=tt('advertising desciption')?></label></p>
<p><?=$description?></p>
<p><label><?=tt('customer description')?></label></p>
<p><?=$customer?></p>
<p>
	<a href="<?=SECTION_URI.Q.'advertise_edit/'.$id?>"><?=tt('edit')?></a> |
	<a href="<?=SECTION_URI.Q.'advertise_drop/'.$id?>"><?=tt('drop')?></a>
</p>
