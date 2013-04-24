<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="small_label"><?=tt('sorted by status')?></h3>
<ul>
	<li><?=render_operation_link('develcard_reporter_list', $user_id, tt('all'))?></li>
	<?php foreach($status as $key => $value):?>
		<li><?=render_operation_link('develcard_reporter_list', $user_id.'/status/'.$key, $value)?></li>
	<?php endforeach?>
</ul>
