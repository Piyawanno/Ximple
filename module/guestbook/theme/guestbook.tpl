<?php if(!defined('XIMPLE_CMS')) die();?>
<h2 class="list_label"><?=tt('Guestbook')?></h2>
<?=render_write_icon('guestbook_write', tt('Please sign on our website.'))?>
<?php foreach($data as $key => $value):?>
<div class="guestbook">
	<h3 class="title_label"><?=$value['writer']?></h3>
	<p>
		<?=$value['guestbook']?>
	</p>
	<p class="guestbook_foot">	
		<?=$value['write_time']?>
		<?php if($is_admin):?>
			<a href="<?=SECTION_URI.Q?>guestbook_edit/<?=$value['id']?>">edit</a>
			<a href="<?=SECTION_URI.Q?>guestbook_drop/<?=$value['id']?>">drop</a>
		<?php endif?>
	</p>
</div>
<?php endforeach?>
