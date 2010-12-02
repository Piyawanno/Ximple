<?php if(!defined('XIMPLE_CMS')) die();?>
<div class="form">
	<form enctype="multipart/form-data" method="post" action="<?=SECTION_URI.Q.$meta->mode?>" name="ximpleform" onsubmit="return formCheck(notNull<?=$meta->id?>, label<?=$meta->id?>)" id="<?=$meta->id?>">
	<h2 class="list_label"><?=$meta->title?></h2>
	<?=$meta->description?>
	<select style="display:none;position:absolute;" id="complete_option" multiple="multiple" size="5">
	</select>
	<?php $is_require_label = false;?>
	<?php foreach($form as $key => $value):?>
		<?php if(isset($label[$key])):?>
			<p>
				<label style="font-weight:bold;"><?=$label[$key]?></label>
				<?php if(in_array($key, $not_null)):?>
					<span style="color:red;font-weight:bold;">*</span>
					<?php $is_require_label = true;?>
				<?php endif?>
			</p>
		<?php endif?>
		<?=$value?>
		<?php if(isset($help[$key])): ?>
			<p class="form_help"><?=$help[$key]?></p>
		<?php endif?>
	<?php endforeach?>
	<?php foreach($meta->additionalForm as $key => $value):?>
		<?=$value?>
	<?php endforeach?>
	<?=$config?>
	<!--{additional_form}-->
	<?php if($is_require_label):?>
		<p>
			<span style="color:red;font-weight:bold;">*</span>
			<?=tt('required fields')?>
		</p>
	<?php endif?>
	<input type="submit" value="<?=$meta->submitLabel?>"/>
	</form>
</div>
