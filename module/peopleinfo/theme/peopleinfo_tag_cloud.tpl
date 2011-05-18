<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="title_label"><?=tt('Tag cloud of People')?></h3>
<ul class="peopleinfo_tag_cloud">
<?php foreach($data['people'] as $key => $value):?>
	<li><?=render_tag_cloud('peopleinfo', $value)?></li>
<?php endforeach?>
</ul>

<h3 class="title_label"><?=tt('Tag cloud of Event')?></h3>
<ul class="peopleinfo_tag_cloud">
<?php foreach($data['event'] as $key => $value):?>
	<li><?=render_tag_cloud('peopleinfo_event', $value)?></li>
<?php endforeach?>
</ul>

<h3 class="title_label"><?=tt('Tag cloud of Information')?></h3>
<ul class="peopleinfo_tag_cloud">
<?php foreach($data['information'] as $key => $value):?>
	<li><?=render_tag_cloud('peopleinfo_info', $value)?></li>
<?php endforeach?>
</ul>
