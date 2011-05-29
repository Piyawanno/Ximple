<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="title_label"><?=tt('Last updated People')?></h3>
<ul>
	<?php foreach($people as $key => $value):?>
		<li><a href="<?=SECTION_URI.Q.'/peopleinfo/'.$key?>"><?=$value['people']['login_name']?></a> @ <?=$value['update_time']?></li>
	<?php endforeach?>
</ul>
<p style="margin-bottom:40px;">
	<a href="<?=SECTION_URI.Q.'peopleinfo'?>"><?=tt('List all People')?></a>
</p>

<h3 class="title_label"><?=tt('Last updated Events')?></h3>
<ul>
	<?php foreach($event as $key => $value):?>
		<li><a href="<?=SECTION_URI.Q.'/peopleinfo_event/'.$key?>"><?=$value['event']?></a> @ <?=$value['update_time']?></li>
	<?php endforeach?>
</ul>
<p style="margin-bottom:40px;">
	<a href="<?=SECTION_URI.Q.'peopleinfo_event'?>"><?=tt('List all Events')?></a>
</p>

<h3 class="title_label"><?=tt('Last updated Information')?></h3>
<ul>
	<?php foreach($information as $key => $value):?>
		<li><a href="<?=SECTION_URI.Q.'/peopleinfo_info/'.$key?>"><?=$value['topic']?></a> @ <?=$value['update_time']?></li>
	<?php endforeach?>
</ul>
<p style="margin-bottom:40px;">
	<a href="<?=SECTION_URI.Q.'peopleinfo_info'?>"><?=tt('List all Information')?></a>
</p>

