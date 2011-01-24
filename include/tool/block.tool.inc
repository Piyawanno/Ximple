<?php

function block_render(){
	$data = block_get_data();
	if(count($data) == 0){
		$data = block_init_default();
	}
	$render = array();
	$block_tpl = cc('block_tpl');
	foreach($data as $key => $value){
		$value = translate_content($value, 'block', $value['id']);
		$pos = $value['position'];
		$item = block_render_item($value, 'block_'.$pos.'.tpl');
		if($item) $render[$pos][] = $item;
	}
	$position = cc('block_position');
	foreach($position as $key => $value){
		if(!isset($render[$key])) $render[$key] = array();
	}
	return $render;
}

function block_init_default(){
	include_once(ROOT_PATH.'module/module/module.tool.inc');
	$position = cc('block_primary_position');
	block_add(tt('Navigation'), 'sysblock_navigation', $position, 'sysblock_navigation_config', 'sysblock_navigation_save', 0);
	block_add(tt('Control Panel'), 'sysblock_panel', $position, 999);
	block_add(tt('Login'), 'sysblock_login', $position, 1000);
	block_add(tt('Language Selection'), 'sysblock_translate', 'foot');
	block_add(tt('Execution Info'), 'sysblock_execute_info', 'foot');
	return block_get_data();
}

function block_get_data(){
	$column = array('id', 'title', 'body', 'position', 'call_mode', 'appear_group', 'appear_module');
	$clause = 'WHERE section='.SECTION.' AND position != \'disabled\' ORDER BY sort_number';
	return db_select('block', $column, $clause);
}

function block_render_item($item, $tpl){
	if(block_check_permision($item)){
		$body = block_get_body($item);
		if(!empty($body)){
			$render_data = array(
				'title' => $item['title'],
				'body' => $body,
			);
			return render($render_data, $tpl, 'block_item');
		}
	}
	return null;
}

function block_get_body($item){
	$body = $item['body'];
	if(strlen($item['call_mode'])){
		$body .= execute_string($item['call_mode']);
	}
	return $body;
}

function block_check_permision($item){
	$appear_module = unserialize($item['appear_module']);
	$appear_group = unserialize($item['appear_group']);
	if(count($appear_module) == 0 or in_array(MODULE, $appear_module)){
		if(in_array(2, $appear_group)){
			return true;
		}
		if(count(array_intersect(ss('login_group'), $appear_group))){
			return true;
		}
	}
	return false;
}

function block_add_navigation($mode, $title){
	config_append_assc('navigation', $mode, $title);
	config_append('navigation_enabled', $mode);
}

function block_drop_navigation($mode){
	config_drop_assc('navigation', $mode);
	config_drop_by_value('navigation_enabled', $mode);
}

function block_add($title, $call_mode, $position='disabled', $form_mode='', $save_mode='', $sort_number=1){
	$insert_data = array(
		'title' => (string) $title,
		'config_form_mode' => (string) $form_mode,
		'config_save_mode' => (string) $save_mode,
		'call_mode' => (string) $call_mode,
		'position' => $position,
		'appear_module' => (string) serialize(array()),
		'appear_group' => (string) serialize(array(2)),
		'body' => '',
		'sort_number' => $sort_number,
		'section' => SECTION,
	);
	db_insert('block', $insert_data);
}

function block_drop($call_mode){
	db_drop_many('block', "call_mode='".addslashes((string)$call_mode)."'");
}
?>
