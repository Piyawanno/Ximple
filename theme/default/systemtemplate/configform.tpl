<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 onclick="hideSub('sub_config_<?=$id?>')" class="config_head"><?=$title?></h3>
<?php if($show):?>
	<div class="subform" id="sub_config_<?=$id?>">
<?else:?>
	<div class="subform" id="sub_config_<?=$id?>" style="display:none;">
<?endif?>
	<?php if(strlen($description)): ?>
		<p><?=$description?></p>
	<?php endif?>
	<?php foreach($form as $key => $value):?>
		<?php if(isset($label[$key])): ?>
			<p><label style="font-weight:bold;"><?=$label[$key]?>
			<?php if(in_array($key, $not_null)):?>
				<span style="color:red;font-weight:bold;">*</span>
			<?php endif?>
			</label></p>
		<?php endif?>
		<?=$value?>
		<?php if(isset($help[$key])): ?>
			<p class="form_help"><?=$help[$key]?></p>
		<?php endif?>
	<?php endforeach?>
</div>
