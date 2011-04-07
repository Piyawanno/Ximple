<?php
forum_switch();

execute_add_function('forum_entry_last_commented');
execute_add_function('forum_entry_last_commented_config');
execute_add_function('forum_entry_last_commented_config_save');

function forum_switch(){
	$splitted = split('_', MODE);
	if(count($splitted) > 1 and $splitted[1] == 'config'){
		include('ForumConfig.class.inc');
	}elseif(count($splitted) > 1 and $splitted[1] == 'entry'){
		include('ForumEntry.class.inc');
	}else{
		include('Forum.class.inc');
	}
}

function forum_entry_last_commented(){
	include_once('forum.tool.inc');
	$column = array(
		'id',
		'topic',
		'comment_time',
		'writer',
		'writer_name',
		'forum',
		'write_time',
		'last_commentator',
		'last_commentator_id',
	);
	$number = cc('forum_last_commented_number');
	if(empty($number)) $number = 5;
	$clause = 'WHERE section='.SECTION.' ORDER BY comment_time DESC LIMIT '.$number;
	$data = db_select('forum_entry', $column, $clause);
	foreach($data as $key => $value){
		$data[$key]['forum'] = forum_get_info($value['forum']);
		$data[$key]['writer'] = userinfo_get_info_by_id($value['writer']);
		$data[$key]['last_commentator_info'] = userinfo_get_info_by_id($value['last_commentator_id']);
		$data[$key]['write_time'] = date(cc('time_format'), strtotime($value['write_time']));
	}
	return render(array('data' => $data), 'lastcommented.tpl', 'lastcommented');
}

function forum_entry_last_commented_config(){
	require_once(ROOT_PATH.'include/class/QuickFormRender.class.inc');
	$formRender = new QuickFormRender('forum_last_commented');
	$option = array(5 => 5, 10 => 10, 15 => 15, 20 => 20, 30 => 30, 40 => 40, 50 => 50);
	$number = Model::select(tt('number of last commented enties'), $option);
	$number->data = cc('forum_last_commented_number');
	$formRender->append('forum_last_commented_number', $number);
	return $formRender->render();
}

function forum_entry_last_commented_config_save(){
	config_set('forum_last_commented_number', pp('forum_last_commented_number'));
	config_save();
}
?>
