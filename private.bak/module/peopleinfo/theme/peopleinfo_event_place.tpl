<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="list_label"><?=tt('Events occured in : ').$place?></h3>
<ul>
<?php foreach($data as $key => $value):?>
	<li><a href="<?=SECTION_URI.Q.'peopleinfo_event/'.$key?>"><?=$value['event']?></a></li>
<?php endforeach?>
</ul>
