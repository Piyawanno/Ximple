<?php if(!defined('XIMPLE_CMS')) die();?>
<?php if($show_function):?><div class="avatar_container"><?php endif?>
<a href="<?=$profile_uri?>">
	<img src="<?=$avatar_uri?>" border="0" />
</a>
<?php if($show_function):?>
	<p><?=$profile_link?></p>
	<?php if(!$is_guest):?>
		<div class="avatar_icon_container">
			<?php foreach($icon as $key => $value):?>
				<a href="<?=SECTION_URI.Q.$key?>"><img src="<?=ROOT_URI.$value?>" border="0" class="avatar_icon"/></a>
			<?php endforeach?>
		</div>
	<?php endif?>
	</div>
<?php endif?>
	
