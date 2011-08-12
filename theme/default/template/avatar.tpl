<?php if(!defined('XIMPLE_CMS')) die();?>
<div class="avatar_container">
	<a href="<?=$profile_uri?>">
		<img src="<?=$avatar_uri?>" border="0" />
	</a>
	<p><?=$profile_link?></p>
	<div class="avatar_icon_container">
		<?php foreach($icon as $key => $value):?>
			<a href="<?=SECTION_URI.Q.$key?>"><img src="<?=ROOT_URI.$value?>" border="0" class="avatar_icon"/></a>
		<?php endforeach?>
	</div>
</div>
