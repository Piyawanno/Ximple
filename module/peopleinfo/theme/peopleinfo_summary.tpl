<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="title_label"><?=tt('Last updated People')?></h3>
<ul>
	<?php foreach($people as $key => $value):?>
		<li><a href="<?=SECTION_URI.Q.'/peopleinfo/'.$key?>"><?=$value['people']['login_name']?></a> @ <?=$value['update_time']?></li>
	<?php endforeach?>
</ul>
<p style="margin-bottom:40px;">
	<?=sprintf(tt('<a href="%s">List all People</a>'), SECTION_URI.Q.'peopleinfo')?>
</p>

<h3 class="title_label"><?=tt('Last updated Events')?></h3>
<ul>
	<?php foreach($event as $key => $value):?>
		<li><a href="<?=SECTION_URI.Q.'/peopleinfo_event/'.$key?>"><?=$value['event']?></a> @ <?=$value['update_time']?></li>
	<?php endforeach?>
</ul>
<p style="margin-bottom:40px;">
	<?=sprintf(tt('<a href="%s">List all Events</a>'), SECTION_URI.Q.'peopleinfo_event')?>
</p>

<h3 class="title_label"><?=tt('Last updated Information')?></h3>
<ul>
	<?php foreach($information as $key => $value):?>
		<li><a href="<?=SECTION_URI.Q.'/peopleinfo_info/'.$key?>"><?=$value['topic']?></a> @ <?=$value['update_time']?></li>
	<?php endforeach?>
</ul>
<p style="margin-bottom:40px;">
	<?=sprintf(tt('<a href="%s">List all Information</a>'), SECTION_URI.Q.'peopleinfo_info')?>
</p>
