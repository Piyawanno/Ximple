<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="list_label"><?=sprintf(tt('Evaluation Form for %s'), $evaluatee['login_name'])?></h3>
<p><?=$model['description']?></p>

<?=render_avatar($evaluatee, true)?>
<div class="form">
	<form enctype="multipart/form-data" method="post" action="<?=SECTION_URI.Q?>evaluation_save" name="ximpleform">
	<?php foreach($model['model'] as $name => $sub_model):?>
		<h3 class="title_label"><?=$name?></h3>
		<?php foreach($sub_model as $key => $value):?>
			<p>
				<label style="font-weight:bold;"><?=$value['name']?> (<?=$value['max']?>)</label>
			</p>
			<input name="result[<?=$key?>]" id="result_<?=$key?>" value="<?=$result[$key]?>"/>
			<script>
				$("#result_<?=$key?>").spinbox({
					min  : 0,
					max  : <?=$value['max']?>,
					step : 1,
				});
			</script>
			<p class="form_help"><?=$value['description']?></p>
		<?php endforeach?>
		<br />
	<?php endforeach?>
	<input name="status" type="submit" label="save as draft"/>
	</form>
</div>
