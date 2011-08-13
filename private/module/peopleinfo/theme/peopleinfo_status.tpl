<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="list_label"><?=tt('People with status : ').$status?></h3>
<ul>
<?php foreach($data as $key => $value):?>
	<li><a href="<?=SECTION_URI.Q.'peopleinfo/'.$key?>"><?=$value?></a></li>
<?php endforeach?>
</ul>
