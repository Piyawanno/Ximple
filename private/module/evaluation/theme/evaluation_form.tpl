<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="list_label"><?=sprintf(tt('Evaluation Form for %s'), $data['evaluatee']['login_name'])?></h3>
<p><?=$model['description']?></p>
<style>
	.evaluate_input, .evaluate_head, .evaluate_description{
		padding:0;
		margin:0;
	}
	
	.evaluate_description{
		color:#666;
	}
</style>
<?=render_avatar($data['evaluatee'], true)?>
<div class="form">
	<form enctype="multipart/form-data" method="post" action="<?=SECTION_URI.Q.'evaluation_save/'.$data['id']?>" name="ximpleform" onsubmit="return checkResult()">
	<input type="hidden" name="status" id="evaluation_status" />
	<input type="hidden" name="model" value="<?=$model_name?>" />
	<?=$pre_addition_form?>
	<br /><br />
	<?php foreach($model['model'] as $name => $sub_model):?>
		<h3 class="title_label"><?=$name?></h3>
		<?php foreach($sub_model as $key => $value):?></p>
			<h4 class="evaluate_head" id="head_<?=$key?>"><?=$value['name']?> (<?=tt('maximum').' : '.$value['max']?>)</h4>
			<p class="evaluate_description"><?=$value['description']?></p>
			<p class="evaluate_input">
			<?php if($status != 0):?>
				<input class="evaluate_result" name="result[<?=$result[$key]['id']?>]" id="result_<?=$key?>" value="<?=$result[$key]['result']?>" size="5" rel="<?=$key?>"/>
			<?php else :?>
				<input class="evaluate_result" name="result[<?=$result[$key]['id']?>]" id="result_<?=$key?>" size="5" rel="<?=$key?>"/>
			<?php endif?>
			</p>
			<script>
				$("#result_<?=$key?>").spinbox({
					max  : <?=$value['max']?>,
				});
			</script>
			<br />
		<?php endforeach?>
		<br />
	<?php endforeach?>
	<?=$post_addition_form?>
	<p>
		<input type="submit" value="<?=tt('save as draft')?>" onclick="return setDraft();"/>
		<input type="submit" value="<?=tt('permanently save')?>" onclick="return setFinish();"/>
	</p>
	</form>
</div>

<script>
	function checkResult(){
		var resultOK = true;
		$('.evaluate_result').each(function(){
			if($(this).val().length == 0 && resultOK){
				alert(pleaseFill+$('#head_'+$(this).attr('rel')).html())
				$(this).css({'border':'2px solid red'});
				resultOK = false;
			}
		});
		return resultOK;
	}
	
	function setDraft(){
		$('#evaluation_status').val('1');
		return true;
	}
	
	function setFinish(){
		$('#evaluation_status').val('2');
		return true;
	}
</script>
