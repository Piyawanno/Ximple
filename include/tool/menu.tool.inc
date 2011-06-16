<?php

global $menu_activated;
$menu_activated = array();

function menu_render(){
	$column = array('id', 'title', 'uri', 'block');
	$clause = 'WHERE section='.SECTION.' ORDER BY sort_number';
	$data = db_select('menu', $column, $clause);
	if(cc('menu_include_block')){
		$block = menu_render_block($data);
		foreach($data as $key => $value){
			if($value['block'] != 0 and isset($block[$value['block']])){
				$data[$key]['block'] = $block[$value['block']];
			}
		}
	}
	$data = menu_check_module($data);
	$data = menu_translate($data);
	return render(array('data' => $data), 'menu.tpl', 'menu');
}

function menu_activate($mode){
	global $menu_activated;
	$menu_activated[] = $mode;
}

function menu_render_block($data){
	$block_id = '';
	foreach($data as $key => $value){
		if($value['block'] != 0){
			$block_id .= 'id = '.$value['block'].' OR ';
		}
	}
	$block = array();
	if(strlen($block_id)){
		$column = array('id', 'title', 'body', 'position', 'call_mode', 'appear_group', 'appear_module');
		$clause = 'WHERE '.substr($block_id, 0, -4);
		$block_data = db_select('block', $column, $clause);
		foreach($block_data as $key => $value){
			$block[$key] = block_render_item($value, 'submenu.tpl');
		}
	}
	return $block;
}

function menu_check_module($data){
	global $menu_activated;
	if(MODE == cc('index_mode')){
		foreach($data as $key => $value){
			$data[$key]['is_called_module'] = ($value['uri'] == SECTION_URI);
		}
	}elseif(count($menu_activated)){
		foreach($data as $key => $value){
			$data[$key]['is_called_module'] = in_array($value['uri'], $menu_activated);
		}
	}else{
		foreach($data as $key => $value){
			$splitted = split('/', $value['uri']);
			$splitted = split('_', $splitted[0]);
			$data[$key]['is_called_module'] = ($splitted[0] == MODULE);
		}
	}
	foreach($data as $key => $value){
		if(substr($value['uri'], 0, 7) != 'http://'){
			$data[$key]['uri'] = SECTION_URI.Q.$value['uri'];
		}
	}
	return $data;
}

function menu_add($mode, $title){
	$inser_data = array(
		'title' => (string) $title,
		'URI' => (string) $mode,
		'block' => 0,
		'sort_number' => 0,
		'section' => SECTION,
	);
	db_insert('menu', $inser_data);
}

function menu_drop($mode){
	db_drop_many('menu', "uri='".addslashes((string)$mode)."' AND section=".SECTION);
}

function menu_translate($data){
	$translated = array();
	foreach($data as $key => $value){
		$translated[$key] = translate_content($value, 'menu', $value['id']);
	}
	return $translated;
}
?>
