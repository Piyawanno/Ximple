<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="list_label"><?=tt('Develcard of : ').$user['login_name']?></h3>
<?=render_avatar($user)?>
<h4 class="title_label"><?=tt('List of DevelCards')?></h4>
<ul>
	<li><?=render_operation_link('develcard_reporter_list', $user['id'], tt('DevelCards reported by : ').$user['login_name'])?></li>
	<li><?=render_operation_link('develcard_resolver_list', $user['id'], tt('DevelCards in duty of : ').$user['login_name'])?></li>
</ul>
<h4 class="title_label"><?=tt('Deadline & End Date Calendar')?></h4>
<?=$calendar?>
<?=$point?>
