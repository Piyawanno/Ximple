<?php

function form($form_id, $model){
	document_init_form();
	$render = array();
	head_add_css('form.css');
	head_add_js('include/external/jquery/jquery-form.js');
	head_add_js('include/external/tinymce/tiny_mce.js');
	head_add_js('include/javascript/mceinit.js');
	head_add_js('include/javascript/formcheck.js');
	head_add_js_var('uploadSuccess', tt('image successfully uploaded'));
	head_add_js_var('pleaseFill', tt('Please, fill the required field : '));
	head_add_js_var('formNotCorrect', tt('Any field in the form is not correctly filled. Please correct it and try again.'));
	foreach($model as $name => $modelCol){
		$func = 'form_render_'.$modelCol->form;
		$render[$name] = $func($form_id, $name, $modelCol);
	}
	return $render;
}

function form_render_none($form_id, $name, $modelCol){
	return null;
}

function form_render_char($form_id, $name, $modelCol){
	$p = '<input name="%s" id="%s" value="%s" size="35" maxlength="80"/><span id="info_%s"></span>';
	return sprintf($p, $name, $form_id.'_'.$name, $modelCol->data, $form_id.'_'.$name);
}

function form_render_email($form_id, $name, $modelCol){
	head_add_js_var('emailNotOk', tt('Your Email address is not conformed.'));
	$p = '<input name="%s" id="%s" value="%s" size="35" maxlength="80" class="email_field"/><span id="info_%s"></span>';
	return sprintf($p, $name, $form_id.'_'.$name, $modelCol->data, $form_id.'_'.$name);
}

function form_render_password($form_id, $name, $modelCol){
	$p = '<input name="%s" id="%s" value="%s" size="35" type="password"/><span id="info_%s"></span>';
	return sprintf($p, $name, $form_id.'_'.$name, $modelCol->data, $form_id.'_'.$name);
}

function form_render_file($form_id, $name, $modelCol){
	$p = '<input name="%s" id="%s" size="35" type="file"/><span id="info_%s"></span>';
	return sprintf($p, $name, $form_id.'_'.$name, $form_id.'_'.$name);
}

function form_render_hidden($form_id, $name, $modelCol){
	$p = '<input name="%s" id="%s" value="%s" type="hidden"/><span id="info_%s"></span>';
	return sprintf($p, $name, $form_id.'_'.$name, $modelCol->data, $form_id.'_'.$name);
}

function form_render_text($form_id, $name, $modelCol){
	$p = '<textarea name="%s" id="%s" style="width:100%%;" rows="20" cols="" class="text">%s</textarea><span id="info_%s"></span>';
	return sprintf($p, $name, $form_id.'_'.$name, $modelCol->data, $form_id.'_'.$name);
}

function form_render_shorttext($form_id, $name, $modelCol){
	$p = '<textarea name="%s" id="%s" style="width:100%%;" rows="10" cols="" class="%s">%s</textarea><span id="info_%s"></span>';
	if(authority_is_guest()) return sprintf($p, $name, $form_id.'_'.$name, "shorttext", $modelCol->data, $form_id.'_'.$name);
	else return sprintf($p, $name, $form_id.'_'.$name, "usershorttext", $modelCol->data, $form_id.'_'.$name);
}

function form_render_plain($form_id, $name, $modelCol){
	$p = '
	<div class="plaintext_container" style="width:100%%;height:150px;border:1px solid #eee;">
		<textarea name="%s" id="%s" class="plaintext" style="width:98%%;height:120px;margin:5px;">%s</textarea>
		<span id="info_%s"></span>
	</div>';
	return sprintf($p, $name, $form_id.'_'.$name, $modelCol->data, $form_id.'_'.$name);
}

function form_render_calendar($form_id, $name, $modelCol){
	if($modelCol->data) $formatted_date = date('d F Y', strtotime($modelCol->data));
	else $formatted_date = date('d F Y');
	$p = '<input type="text" name="%s" id="%s" value="%s" class="calendar_form"><span id="info_%s"></span>';
	return sprintf($p, $name, $form_id.'_'.$name, $formatted_date, $form_id.'_'.$name);
}

function form_render_radio($form_id, $name, $modelCol){
	$render = '<ul class="form_radio" id="'.$form_id.'_'.$name.'">';
	$p = '<li><input type="radio" name="%s" value="%s" %s style="border:none;" />%s</li>';
	foreach($modelCol->selection as $key => $value){
		$checked = $key == $modelCol->data ? 'checked="checked"' : '';
		$render .= sprintf($p, $name, $key, $checked, $value, $form_id.'_'.$key);
	}
	$render .= '</ul><span id="info_'.$form_id.'_'.$name.'"></span><p style="clear:both;">';
	return $render;
}

function form_render_select($form_id, $name, $modelCol){
	$render = '<select name="'.$name.'" id="'.$form_id.'_'.$name.'">';
	foreach($modelCol->selection as $key => $value){
		$selected = $modelCol->data == $key ? 'selected="selected"' : '';
		$render .= '<option value="'.$key.'" '.$selected.'>'.$value.'</option>';
	}
	$render .= '</select><span id="info_'.$form_id.'_'.$name.'"></span>';
	return $render;
}

function form_render_imageloader($form_id, $name, $modelCol){
	$id = $form_id.'_'.$name;
	if(strlen($modelCol->data)) $image_src = ROOT_URI.$modelCol->data;
	else $image_src = ROOT_URI.'files/icon/loader.png';
	$render = '
	<input type="hidden" name="'.$name.'" id="input_'.$id.'" value="'.$modelCol->data.'" />
	<a href="#" onclick="showImageLoader(\''.$id.'\', \''.$modelCol->path.'\');return false;">
		<img src="'.$image_src.'" border="0" id="image_'.$id.'" alt="image"/>
	</a>
	<div id="loader_'.$id.'" style="display:none;"></div>';
	return $render;
}

function form_render_multi_files($form_id, $name, $modelCol){
	$render = '<div id="multi_files_'.$name.'">';
	for($i=0;$i<5;$i++){
		$render .= '<input name="'.$name.'[]" size="40" type="file" style="margin-bottom:10px;"/><br />';;
	}
	$render .= '</div>';
	$render .= '<input type="button" class="add_multi_files" value="'.tt('more file').'" rel="'.$name.'"/>';
	$render .= '<span id="info_'.$form_id.'_'.$name.'"></span>';
	return $form;
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
	<input name="'.$name.'" size="35" maxlength="6" onkeyup="checkCaptcha(\''.$name.'\')" id="captcha_input_'.$name.'"/>
	<font id="captcha_info_'.$name.'" style="font-weight:bold;"></font>
	<br /><br />
	<img src="'.SECTION_URI.Q.'captcha/gentime/'.$gentime.'" style="padding:0;" border="0" id="captcha_img_'.$name.'"/>
	<a href="javascript:changeCaptcha(\''.$name.'\', '.$gentime.')">
		<img src="'.ROOT_URI.'files/icon/refresh.png" style="padding:0;margin:auto auto 16px 16px;" border="0"/>
	</a>
	';
}

function form_render_group($form_id, $name, $modelCol){
	$excepted = '';
	if($modelCol->isExceptedAdmin) $excepted .= ' AND id!=1 ';
	if($modelCol->isExceptedGuest) $excepted .= ' AND id!=2 ';
	$group = db_select('groups', array('id', 'name'), 'WHERE ((section='.SECTION.' OR id <=3) '.$excepted.')');
	$modelCol->selection = array();
	foreach($group as $key => $value){
		$modelCol->selection[$key] = $value['name'];
	}
	return form_render_checkbox($form_id, $name, $modelCol);
}

function form_render_color($form_id, $name, $modelCol){
	head_add_js('include/external/farbtastic/farbtastic.js');
	head_add_css('include/external/farbtastic/farbtastic.css');
	if(empty($modelCol->data)) $color = '#d7e3f4';
	else $color = $modelCol->data;
	$id = $form_id.'_'.$name;
	$out  = '<div id="picker_'.$id.'"></div>';
	$out .= '<input name="'.$name.'" id="'.$id.'" value="'.$color.'" size="35" maxlength="7"/>';
	$out .= '<span id="info_'.$form_id.'_'.$name.'"></span>';
	$out .= '<script type="text/javascript">
				$("#picker_'.$id.'").farbtastic("#'.$id.'");
				
				$("#picker_'.$id.'").dialog({
					bgiframe: true,
					autoOpen: false,
					modal: true,
					width:220,
					height:250,
					title:"'.tt('Select color').'",
				});
				
				$("#'.$id.'").click(function(){$("#picker_'.$id.'").dialog("open");});
			</script>';
	return $out;
}

function form_render_autocomplete($form_id, $name, $modelCol){
	$p = '<input name="%s" value="%s" size="35" maxlength="80" class="auto_complete" id="%s" rel="%s"/>';
	return sprintf($p, $name, $modelCol->data, $form_id.'_'.$name, $modelCol->ajaxMode);
}

function form_render_checkbox($form_id, $name, $modelCol){
	list($sortable, $img) = form_get_sortable($modelCol);
	$render = '<div class="checkbox_list"><ul '.$sortable.'>';
	$p = '<li>'.$img.'<input type="checkbox" name="%s[]" class="checkbox_%s" value="%s" %s style="border:none;" />%s</li>';
	foreach($modelCol->selection as $key => $value){
		if(is_array($modelCol->data) and in_array($key, $modelCol->data)){
			$checked = 'checked="checked"';
		}else{
			$checked = '';
		}
		$render .= sprintf($p, $name, $name, $key, $checked, $value);
	}
	$render .= '</ul><span id="info_'.$form_id.'_'.$name.'"></span></div><p style="clear:both;"></p>';
	if(count($modelCol->selection) > 1){
		$render .= '<a href="javascript:checkAllCheckBox(\''.$name.'\')">'.tt('check all').'</a> | ';
		$render .= '<a href="javascript:checkNoneCheckBox(\''.$name.'\')">'.tt('check none').'</a></p>';
	}
	return $render;
}

function form_render_checkedit($form_id, $name, $modelCol){
	list($sortable, $img) = form_get_sortable($modelCol);
	$render = '<div class="checkedit_list"><ul '.$sortable.'>';
	$p1 = '<li>'.$img.'<input type="checkbox" name="check_%s[]" class="checkedit" value="%s" %s style="border:none;" rel="%s"/>';
	$p2 = '<input id="%s" name="%s[]" size="35" value="%s" %s/></li>';
	$i = 0;
	foreach($modelCol->selection as $key => $value){
		if(is_array($modelCol->data) and in_array($key, $modelCol->data)){
			$checked = 'checked="checked"';
			$disabled = '';
		}else{
			$checked = '';
			$disabled = 'disabled="disabled"';
		}
		$id = $form_id.'_'.$name.$i;
		$render .= sprintf($p1, $name, $key, $checked, $id);
		$render .= sprintf($p2, $id, $name, $value, $disabled);
		$i++;
	}
	$render .= '</ul><span id="info_'.$form_id.'_'.$name.'"></span></div>';
	return $render;
}

function form_render_multiplefiles($form_id, $name, $modelCol){
	$render  = '<div class="multiplefiles_list" id="'.$form_id.'_'.$name.'">';
	$render .= '<p><a onclick="return addFileInput(\''.$form_id.'_'.$name.'\', \''.$name.'\')" href="#">'.tt('Upload More File').'</a></p>';
	$render .= '<ul>';
	for($i=0;$i<6;$i++){
		$render .= '<li><input type="file" name="'.$name.'[]" size="35" ></li>';	
	}
	$render .= '</ul>';
	$render .= '<span id="info_'.$form_id.'_'.$name.'" style="clear:both;display:block;"></span>';
	$render .= '</div>';
	return $render;
}

function form_get_sortable($modelCol){
	if($modelCol->isSortable){
		$sortable = 'class="sortable_form"';
		$img = '<img src="'.ROOT_URI.'files/icon/move.png" />';
	}else{
		$sortable = '';
		$img = '';
	}
	return array($sortable, $img);
}

?>
