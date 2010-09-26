<?php
execute_add_function('flashblock');
execute_add_function('flashblock_config');
execute_add_function('flashblock_save');

function flashblock($arg){
	$column = array('id', 'mode', 'table_name', 'column_name', 'clause', 'item_number');
	$data = db_select('flashblock', $column, 'WHERE id='.((int)$arg['id']));
	$data = $data[$arg['id']];
	$clause = $data['clause'].' LIMIT '.$data['item_number'];
	$item = db_select_single_column($data['table_name'], $data['column_name'], $clause);
	$render_array = array(
		'mode' => $data['mode'],
		'item' => $item,
	);
	return render($render_array, 'module/flashblock/theme/flashblock.tpl', 'flashblock');
}

function flashblock_clear_cache($table){
	
}

function flashblock_add($reference, $mode, $name, $table, $column, $clause){
	include_once(ROOT_PATH.'include/tool/block.tool.inc');
	$data = array(
		'reference' => $reference,
		'mode' => $mode,
		'table_name' => $table,
		'column_name' => $column,
		'clause' => $clause,
		'section' => SECTION,
		'item_number' => 5,
	);
	$id = db_insert('flashblock', $data);
	block_add($name, 'flashblock/'.$id, cc('block_primary_position'), 'flashblock_config/'.$id, 'flashblock_save/'.$id);
}

function flashblock_drop($reference){
	include_once(ROOT_PATH.'include/tool/block.tool.inc');
	$clause = "reference='".$reference."' AND section=".SECTION;
	$id = db_select_single_column('flashblock', 'id', 'WHERE '.$clause, false);
	if(count($id)){
		db_drop_many('flashblock', $clause);
		block_drop('flashblock/'.$id[0]);
	}
}

function flashblock_config($arg){
	include_once(ROOT_PATH.'include/class/QuickFormRender.class.inc');
	include_once(ROOT_PATH.'include/class/Model.class.inc');
	$quickform = new QuickFormRender('block');
	$item_number_data = db_select_single_column('flashblock', 'item_number', 'WHERE id='.$arg['id'], false);
	$option = array(3 => 3, 5 => 5, 8 => 8, 10 => 10, 15 => 15);
	$item_number = Model::select(tt('number of shown items'), $option);
	$item_number->data = $item_number_data[0];
	$quickform->append('flashblock_item_number', $item_number);
	return $quickform->render();
}

function flashblock_save($arg){
	db_update('flashblock', array('item_number' => pp('flashblock_item_number')), $arg['id']);
}

?>
