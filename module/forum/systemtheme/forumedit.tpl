<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="list_label"><?=tt('Manage Forum')?></h3>
<label><?=tt('Legend')?></label>
<ul>
	<li><img src="<?=ROOT_URI?>files/icon/move.png"/> : <?=tt('Sort and select category by drag-and-drop')?></li>
	<li><img src="<?=ROOT_URI?>files/icon/edit.png"/> : <?=tt('Edit Forum')?></li>
</ul>
<p>
	<?=tt('You can use this form to sort and manage forums by drag-and-drop. Please, do not forget to click submit.')?>
</p>

<form action="<?=SECTION_URI.Q?>forum_save_sort" method="post" onsubmit="getPosition()">
<?php $sortable_id = "";?>
<?php foreach($position as $reference => $title):?>
<a name="position_<?=$reference?>" />
<fieldset>
	<legend><label><?=$title?></label></legend>
	<?php $sortable_id .= '#block_sort_'.$reference.', ';?>
	<ul id="block_sort_<?=$reference?>" class="sortable">
	<?php if(isset($data[$reference])):?>
		<?php foreach($data[$reference] as $block):?>
		<li>
			<a name="block_<?=$block['id']?>" />
			<img src="<?=ROOT_URI?>files/icon/move.png" align="left"/> 
			<a href="<?=SECTION_URI.Q.'block_edit/'.$block['id']?>" style="text-decoration:none;">
				<img src="<?=ROOT_URI?>files/icon/edit.png" align="left" border="0"/>
			</a>
			<?=$block['title']?>
			<input type="hidden" name="position[]" class="position_input" value=""/>
			<input type="hidden" name="block[]" value="<?=$block['id']?>"/>
			<input type="hidden" name="call_mode[]" value="<?=$block['call_mode']?>"/>
		</li>
		<?php endforeach?>
	<?php endif?>
	</ul>
	<a href="<?=SECTION_URI.Q?>block_write/position/<?=$reference?>" style="text-decoration:none;">
		<img src="<?=ROOT_URI?>files/icon/add.png" align="left" border="0" style="margin-right:15px;"/>
		<?=sprintf(tt('Add new block into %s'), $title)?>
	</a>
</fieldset>
<?php endforeach?>

<input type="submit" value="<?=tt('save blocks')?>" />
</form>

<script type="text/javascript">
$(function() {
	$("<?=substr($sortable_id, 0, -2)?>").sortable({
		connectWith: '.sortable',
		dropOnEmpty: true,
	});
	$("<?=substr($sortable_id, 0, -2)?>").disableSelection();
});

function getPosition(){
	<?php foreach($position as $reference => $title):?>
		$('#block_sort_<?=$reference?> li .position_input').attr('value', "<?=$reference?>");
	<?php endforeach?>
}
</script>

