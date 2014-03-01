<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="list_label"><?=$title?></h3>
<div class="develcard_icon_bar">
	<?=$personal_icon?>
	<?=$report_icon?>
	<?=$write_icon?>
</div>

<h4 class="small_label"><?=tt('List of Resolvers')?></h3>
<ul class="develcard_personal_list">
<?php foreach($resolver as $uid => $name):?>
	<li><?=render_operation_link('develcard_personal', $uid, $name)?></li>
<?php endforeach?>
</ul>
<div style="clear:both;height:20px;"></div>

<h4 class="small_label"><?=tt('List of Reporters')?></h4>
<ul class="develcard_personal_list">
<?php foreach($reporter as $uid => $name):?>
	<li><?=render_operation_link('develcard_personal', $uid, $name)?></li>
<?php endforeach?>
</ul>
<div style="clear:both;height:20px;"></div>

<?php if(strlen($description)) : ?><p><?=$description?></p><?php endif?>
<?php foreach($data as $id => $card):?>
<div class="develcard_item" style="border-left:4px solid <?=$card['priority_color']?>;">
	<h4><a href="<?=SECTION_URI.Q.'develcard/'.$id?>"><?=$card['topic']?></a></h4>
	<p>
		<label><?=tt('priority')?> : </label><?=$card['priority']['label']?>
		<label><?=tt('status')?> : </label>
		<?=render_operation_link($card['status_uri'], null, $card['status']['label'])?>

		<label><?=tt('type')?> : </label>
		<?=render_operation_link($card['type_uri'], null, $card['type']['label'])?>
	</p>

	<p>
		<label><?=tt('dead line')?> : </label>
		<?=$card['deadline']?> (<?=$card['residual_time']?>)
	</p>
	<p>
		<label><?=tt('resolvers')?> : </label>
		<?php foreach($card['resolver'] as $uid => $resolver):?>
			<?=render_operation_link('develcard_personal', $resolver['id'], $resolver['resolver']['label'])?>, 
		<?php endforeach?>
	</p>

	<p class="operation_bar">
		<?=render_operation_link('develcard', $id, tt('see detail'))?>
		<?=render_operation_link('develcard_edit', $id, tt('edit'))?>
		<?=render_operation_link('develcard_drop', $id, tt('drop'))?>
	</p>
</div>
<?php endforeach?>
