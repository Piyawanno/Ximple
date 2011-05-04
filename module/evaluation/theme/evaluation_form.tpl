<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="list_label"><?=sprintf(tt('Evaluation Form for %s'), $data['evaluatee']['login_name'])?></h3>
<p><?=$model['description']?></p>

<?=render_avatar($data['evaluatee'], true)?>
<div class="form">
	<form enctype="multipart/form-data" method="post" action="<?=SECTION_URI.Q.'evaluation_save/'.$data['id']?>" name="ximpleform">
	<input type="hidden" name="status" id="evaluation_status" />
	<p>
		<label style="font-weight:bold;"><?=tt('your opinion')?></label>
		<textarea name="opinion" class="shorttext"><?=$data['opinion']?></textarea>
	</p>
	<?php foreach($model['model'] as $name => $sub_model):?>
		<h3 class="title_label"><?=$name?></h3>
		<?php foreach($sub_model as $key => $value):?>
			<p>
				<label style="font-weight:bold;display:block;"><?=$value['name']?> (<?=$value['max']?>)</label>
				<input name="result[<?=$result[$key]['id']?>]" id="result_<?=$key?>" value="<?=$result[$key]['result']?>"/>
			</p>
			<script>
				$("#result_<?=$key?>").spinbox({
					max  : <?=$value['max']?>,
				});
			</script>
			<p class="form_help"><?=$value['description']?></p>
		<?php endforeach?>
		<br />
	<?php endforeach?>
	<input type="submit" value="<?=tt('save as draft')?>" onclick="return setDraft();"/>
	<input type="submit" value="<?=tt('permanently save')?>" onclick="return setFinish();"/>
	</form>
</div>

<script>
	function setDraft(){
		$('#evaluation_status').val('1');
		return true;
	}
	
	function setFinish(){
		$('#evaluation_status').val('2');
		return true;
	}
</script>
