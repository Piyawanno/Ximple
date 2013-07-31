<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="list_label"><?=tt('Report sorted by month')?></h3>
<ul>
	<?php foreach($month as $key => $value):?>
		<li><?=render_operation_link('develcard_report', $key, $value)?></li>
	<?php endforeach?>
</ul>
