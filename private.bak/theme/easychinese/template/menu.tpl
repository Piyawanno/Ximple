<?php if(!defined('XIMPLE_CMS')) die();?>
<ul id="menu">
<?php foreach($data as $key => $item):?>
	<?php if($item['is_called_module']):?>
		<li><a href="<?=$item['uri']?>" id="active_page" rel="submenu_<?=$key?>"><?=$item['title']?></a></li>
	<?php else:?>
		<li><a href="<?=$item['uri']?>" rel="submenu_<?=$key?>"><?=$item['title']?></a></li>
	<?php endif?>
<?php endforeach?>
</ul>
