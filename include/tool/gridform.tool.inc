<?php
global $grid_row_array;
$grid_row_array = array();

function gridform_render($form_id, $name, $modelCol){
	head_add_css('list.css');
	$grid_id = $form_id.'_'.$name;
	$render  = gridform_render_head($grid_id, $modelCol);
	$render .= gridform_render_data_row($grid_id, $modelCol);
	$grid_row = gridform_render_row($grid_id, $modelCol);
	gridform_add_grid_row($grid_id, $grid_row);
	$render .= gridform_render_foot($grid_id, $grid_row, $modelCol);
	return $render;
}


function gridform_render_row($grid_id, $modelCol){
	$grid_row = '<tr>';
	foreach($modelCol->getMember() as $key => $value){
		$value->data = null;
		$grid_row .= gridform_render_row_form($grid_id, $key, $value);
	}
	$grid_row.= gridform_drop_icon($modelCol->dropMode);
	$grid_row.= '</tr>';
	$grid_row = str_replace("\n", "", $grid_row);
	return $grid_row;
}

function gridform_render_data_row($grid_id, $modelCol){
	$render = '';
	foreach($modelCol->data as $key => $data){
		$render .= '<tr>';
		foreach($modelCol->getMember() as $memberName => $member){
			$member->data = $data[$memberName];
			$form = gridform_render_row_form($grid_id, $memberName, $member);
			if($modelCol->hasDBRow){
				$form = str_replace('[]', '[id_'.$key.']', $form);
			}
			$render .= $form;
		}
		$render .= gridform_drop_icon($modelCol->dropMode, $key);
		$render .= '</tr>';
	}
	return $render;
}

function gridform_render_row_form($grid_id, $column, $modelCol){
	if($modelCol->isGridForm){
		$functionName = 'form_render_grid_'.$modelCol->form;
		if($modelCol->form != 'hidden'){
			return '<td>'.$functionName($grid_id, $column, $modelCol).'</td>';
		}else{
			return $functionName($grid_id, $column, $modelCol);
		}
	}else{
		return null;
	}
}

function gridform_render_head($grid_id, $modelCol){
	$render  = '<div class="list">';
	$render .= '<span id="info_'.$grid_id.'"></span>';
	$render .= '<table width="100%" id="'.$grid_id.'"><tr>';
	foreach($modelCol->getMember() as $key => $value){
		if($value->isGridForm){
			$render .= '<th>'.$value->label.'</th>';
		}
	}
	$render .= '<th width="36">&#160;</th>';
	return $render;
}

function gridform_render_foot($grid_id, $grid_row, $modelCol){
	$render  = '';
	if(count($modelCol->data) == 0){
		$render .= $grid_row;
	}
	$render .= '</tr></table>';
	$render .= '</div>';
	$render .= gridfrom_add_icon($grid_id);
	return $render;
}

function gridform_add_grid_row($grid_id, $grid_row){
	global $grid_row_array;
	$grid_row_array[$grid_id] = str_replace('"', "\\\"", $grid_row);
}

function gridform_get_row_array(){
	global $grid_row_array;
	return $grid_row_array;
}

function gridfrom_add_icon($grid_id){
	return '
		<a onclick="addGridRow(\''.$grid_id.'\');return false;" href="#" class="write_icon">
			<img src="'.ROOT_URI.'files/icon/add.png" border="0" align="left" />
			'.tt('add new row').'
		</a>';
}

function gridform_drop_icon($drop_mode, $id=null){
	if($id) $drop_mode .= '/'.$id.'/confirm/true';
	else $drop_mode = '';
	return '
		<td>
			<a onclick="delGridRow(this, \''.$drop_mode.'\');return false;" href="#">
			<img src="'.ROOT_URI.'files/icon/drop.png" border="0" align="left" />
		</td>';
}

function form_render_grid_none($form_id, $name, $modelCol){
	return null;
}

function form_render_grid_hidden($form_id, $name, $modelCol){
	$p = '<input name="%s"[] value="%s" type="hidden"/>';
	return sprintf($p, $name, $modelCol->data);
}

function form_render_grid_char($form_id, $name, $modelCol){
	$p = '<input name="%s[]" value="%s" size="25" maxlength="80"/>';
	return sprintf($p, $name, $modelCol->data);
}

function form_render_grid_email($form_id, $name, $modelCol){
	head_add_js_var('emailNotOk', tt('Your Email address is not conformed.'));
	$p = '<input name="%s[]" value="%s" size="25" maxlength="80" class="email_grid_field" rel="%s"/>';
	return sprintf($p, $name, $modelCol->data, $form_id);
}

function form_render_grid_file($form_id, $name, $modelCol){
	$p = '<input name="%s[]" size="25" type="file"/>';
	return sprintf($p, $name);
}

function form_render_grid_select($form_id, $name, $modelCol){
	$render = '<select name="'.$name.'[]">';
	foreach($modelCol->option as $key => $value){
		$selected = $modelCol->data == $key ? 'selected="selected"' : '';
		$render .= '<option value="'.$key.'" '.$selected.'>'.$value.'</option>';
	}
	$render .= '</select>';
	return $render;
}
?>
