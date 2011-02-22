<?php
forum_switch();

execute_add_function('forum_entry_last_commented');

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
	$clause = 'WHERE section='.SECTION.' ORDER BY comment_time DESC LIMIT 5';
	$data = db_select('forum_entry', $column, $clause);
	foreach($data as $key => $value){
		$data[$key]['forum'] = forum_get_info($value['forum']);
		$data[$key]['writer'] = userinfo_get_info_by_id($value['writer']);
		$data[$key]['last_commentator_info'] = userinfo_get_info_by_id($value['last_commentator_id']);
		$data[$key]['write_time'] = date(cc('time_format'), strtotime($value['write_time']));
	}
	return render(array('data' => $data), 'lastcommented.tpl', 'lastcommented');
}
?>
