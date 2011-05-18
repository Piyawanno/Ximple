<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="list_label"><?=$module.' ('.tt('tagged by').' : '.$tag.')'?></h3>
<ul>
<?php foreach($data as $key => $value):?>
	<li><a href="<?=SECTION_URI.Q.$mode.'/'.$key?>"><?=$value?></a></li>
<?php endforeach?>
</ul>
