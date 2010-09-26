<?php
execute_add_function('enlightened');

function enlightened(){
	head_add_css('enlightened.css');
	$news = enlightened_get_featured_blog();
	$blog = enlightened_get_last_blog();
	$item = enlightened_get_last_page();
	$download = enlightened_get_last_download();
	$render_array = array(
		'news' => $news,
		'item' => $item,
		'download' => $download,
		'blog' => $blog,
	);
	return render($render_array, 'enlightened.tpl', 'enlightened');
}

function enlightened_get_featured_blog(){
	$date  = date('Y-m-d');
	$where = "WHERE (section=".SECTION." AND publishing_status=1 AND publish_time <='".$date."')";
	$column = array('id', 'topic', 'intro', 'writer', 'publish_time', 'uri');
	return db_select('blog', $column, $where." ORDER BY id DESC");
}

function enlightened_get_last_page(){
	$tags = enlightened_get_first_order_tag();
	$date = date('Y-m-d');
	$column = array('id', 'topic', 'icon', 'introduction', 'writer', 'publish_time', 'uri');
	$p = "WHERE (freetag LIKE '%s,%%'AND section = %d AND publishing_status = 1 AND publish_time <= '%s') ORDER BY id DESC";
	$page = array();
	foreach($tags as $tag){
		$clause = sprintf($p, $tag, SECTION, $date);
		$page[$tag] = db_select('page', $column, $clause);
	}
	return $page;
}

function enlightened_get_last_blog(){
	$date  = date('Y-m-d');
	$where = "WHERE (section=".SECTION." AND publishing_status=0 AND publish_time <='".$date."')";
	$column = array('id', 'topic', 'intro', 'writer', 'publish_time', 'uri');
	$data = array_values(db_select('blog', $column, $where." ORDER BY id DESC LIMIT 1"));
	if(isset($data[0])) return $data[0];
	else return null;
}

function enlightened_get_last_download(){
	$date  = date('Y-m-d');
	$column = array('id', 'name', 'description', 'uploader', 'upload_time', 'category');
	$data = array_values(db_select('download', $column, "WHERE section=".SECTION." ORDER BY id DESC LIMIT 1"));
	$map = array(8 => 3, 9 => 8, 10 => 4, 11 => 5, 12 => 6, 13 => 7, 14 => 2);
	if(isset($map[$data[0]['category']])){
		$user_info = userinfo_get_info_by_id($map[$data[0]['category']]);
		$data[0]['avatar'] = $user_info['avatar'];
	}
	if(isset($data[0])) return $data[0];
	else return null;
}

function enlightened_get_first_order_tag(){
	return array('บทความ', 'สัมมนา-บทสัมภาษณ์', 'แถลงการณ์', 'เอกสารประวัติศาสตร์', 'ไฟล์เสียง-ภาพ', 'บทความนักศึกษา', 'บทความแนะนำ');
}

function enlightened_get_user_info($news, $blog, $last_item, $download){
	$user = array();
	foreach($news as $key => $value){
		$user[]['user'] = $value['writer'];
	}
	foreach($last_item as $key => $value){
		foreach($value as $index => $item){
			$user[]['user'] = $item['writer'];
		}
	}
	if(isset($blog['writer'])) $user[]['user'] = $blog['writer'];
	if(isset($download['uploader'])) $user[]['user'] = $download['uploader'];
	
	$userinfo = userinfo_get_info($user, 'user');
	$user = array();
	foreach($userinfo as $key => $value){
		$user[$value['user']['id']] = $value['user'];
	}
	return $user;
}
?>
