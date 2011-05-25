<?php

function form($form_id, $model){
	global $grid_row_array;
	document_init_form();
	form_get_head();
	$render = array();
	if(is_array($model)){
		foreach($model as $name => $modelCol){
			$func = 'form_render_'.$modelCol->form;
			$render[$name] = $func($form_id, $name, $modelCol);
		}
	}
	if(function_exists('gridform_get_row_array')){
		head_add_js_array('gridRowArray', gridform_get_row_array());
	}
	return $render;
}

function form_get_head(){
	head_add_css('form.css');
	head_add_css('include/external/cleditor/jquery.cleditor.css');
	head_add_js('include/external/jquery/jquery-form.js');
	head_add_js('include/javascript/formcheck.js');
	head_add_js_var('uploadSuccess', tt('image successfully uploaded'));
	head_add_js_var('pleaseFill', tt('Please, fill the required field : '));
	head_add_js_var('formNotCorrect', tt('Any field in the form is not correctly filled. Please correct it and try again.'));
	head_add_js_var('isInstalled', true);
}

function form_render_grid($form_id, $name, $modelCol){
	require_once('gridform.tool.inc');
	return gridform_render($form_id, $name, $modelCol);
}

function form_render_captcha($form_id, $name, $modelCol){
	$gentime = time();
	head_add_js_var('generateTime', $gentime);
	head_add_js_var('captchaMessage', tt('Please insert code from image before submit.'));
	head_add_js_var('captchaCorrect', tt('Code from image is correct.'));
	head_add_js_var('captchaWrong', tt('Code from image is wrong.'));
	head_add_js_var('captchaLock', true);
	return '
	<input name="captcha_gentime_'.$name.'" type="hidden" value="'.$gentime.'"/>
	<input name="captcha_code_'.$name.'" id="captcha_code_'.$name.'" type="hidden" value="" />
	<input name="'.$name.'" size="25" maxlength="6" onkeyup="checkCaptcha(\''.$name.'\')" id="captcha_input_'.$name.'"/>
	<font id="captcha_info_'.$name.'" style="font-weight:bold;"></font>
	<br /><br />
	<img src="'.SECTION_URI.Q.'captcha/gentime/'.$gentime.'" style="padding:0;" border="0" id="captcha_img_'.$name.'"/>
	<a href="javascript:changeCaptcha(\''.$name.'\', '.$gentime.')">
		<img src="'.ROOT_URI.'files/icon/refresh.png" style="padding:0;margin:auto auto 16px 16px;" border="0"/>
	</a>
	';
}
?>
