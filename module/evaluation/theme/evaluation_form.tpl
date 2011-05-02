<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="list_label"><?=sprintf(tt('Evaluation Form for %s'), $evaluatee['login_name'])?></h3>
<p><?=$model['description']?></p>
<?=render_avatar($evaluatee, true)?>
<?php foreach($model['model'] as $name => $sub_model):?>
	<h4><?=$name?></h4>
	<?php foreach($sub_model as $key => $value):?>
		<label><?=$value['name']?> (<?=$value['max']?>)</label>
		<input name="<?=$key?>" />
		<p class="form_help"><?=$value['description']?></p>
	<?php endforeach?>
<?php endforeach?>
