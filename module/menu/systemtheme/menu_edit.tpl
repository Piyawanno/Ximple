<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="list_label"><?=tt('Menu Edit')?></h3>
<label><?=tt('Legend')?></label>
<ul>
	<li><img src="<?=ROOT_URI?>files/icon/move.png"/> : <?=tt('Sort by drag-and-drop')?></li>
	<li><img src="<?=ROOT_URI?>files/icon/edit.png"/> : <?=tt('Edit and Configure Menu')?></li>
	<li><img src="<?=ROOT_URI?>files/icon/stop.png"/> : <?=tt('Delete Menu')?></li>
</ul>
<p>
	<?=tt('You can use this form to sort Menus by drag-and-drop. Please, do not forget to click submit.')?>
</p>

<form action="<?=SECTION_URI.Q?>menu_save_sort" method="post">
	<ul id="menu_sort" class="sortable">
	<?php foreach($data as $id => $title):?>
	<li>
		<a name="menu_<?=$id?>" />
		<img src="<?=ROOT_URI?>files/icon/move.png" align="left"/> 
		<a href="<?=SECTION_URI.Q.'menu_edit/'.$id?>" style="text-decoration:none;">
			<img src="<?=ROOT_URI?>files/icon/edit.png" align="left" border="0"/>
		</a>
		<a href="<?=SECTION_URI.Q.'menu_drop/'.$id?>" style="text-decoration:none;">
			<img src="<?=ROOT_URI?>files/icon/stop.png" align="left" border="0"/>
		</a>
		<?=$title?>
		<input type="hidden" name="menu[]" value="<?=$id?>"/>
	</li>
	<?php endforeach?>
	</ul>
	<p>
		<a href="<?=SECTION_URI.Q?>menu_write" style="text-decoration:none;">
			<img src="<?=ROOT_URI?>files/icon/add.png" align="left" border="0" style="margin-right:15px;"/>
			<?=tt('Add new Menu')?>
		</a>
	</p>
	<input type="submit" value="<?=tt('save Menus')?>">
</form>

<script type="text/javascript">
$(function() {
	$("#menu_sort").sortable({
		dropOnEmpty: true,
	});
	$("#menu_sort").disableSelection();
});
</script>

