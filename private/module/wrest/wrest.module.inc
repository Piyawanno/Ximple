<?php
execute_add_function('wrest');
execute_add_function('wrest_config');
execute_add_function('wrest_config_save');

define('WREST_MEMBER_GROUP', 9);

function wrest(){
	document_set_path(tt('WREST'));
	head_add_css('wrest.css');
	$data = array(
		'meeting' => wrest_get_meeting(),
		'forum' => wrest_get_forum(),
		'news' => wrest_get_news(),
		'article' => wrest_get_article(),
	);
	$mode = array(
		'meeting' => 'meeting',
		'forum' => 'forum_entry',
		'news' => 'blog',
		'article' => 'blog',
	);
	
	$label = array(
		'meeting' => tt('Meeting'),
		'forum' => tt('Forum'),
		'news' => tt('News'),
		'article' => tt('Article'),
	);
	$render = '';
	$renderArray = array();
	foreach($data as $key => $value){
		$renderArray['mode'] = $mode[$key];
		$renderArray['label'] = $label[$key];
		$renderArray['data'] = $value;
		$render .= render($renderArray, 'wrest.tpl', 'wrest');
	}
	return $render;
}

function wrest_config($params, $result){
	$result[tt('WREST')] = array(
		'wrest_news_category' => Model::select(tt('news category'), wrest_get_blog_categrory()),
		'wrest_news_number' => Model::spin(tt('news number'), 3, 20, 1),
		'wrest_article_category' => Model::select(tt('article category'), wrest_get_blog_categrory()),
		'wrest_article_number' => Model::spin(tt('article number'), 3, 20, 1),
		'wrest_meeting_number' => Model::spin(tt('meeting number'), 3, 20, 1),
		'wrest_forum_number' => Model::spin(tt('forum number'), 3, 20, 1),
		'wrest_word_count' => Model::spin(tt('words count'), 3, 20, 1),
	);
	return $result;
}

function wrest_config_save(){
	config_set('wrest_news_category', pp('wrest_news_category'));
	config_set('wrest_news_number', pp('wrest_news_number'));
	config_set('wrest_article_category', pp('wrest_article_category'));
	config_set('wrest_article_number', pp('wrest_article_number'));
	config_set('wrest_meeting_number', pp('wrest_meeting_number'));
	config_set('wrest_forum_number', pp('wrest_forum_number'));
	config_set('wrest_word_count', pp('wrest_word_count'));
}

function wrest_init_member(){
	$csv = io_read_file(dirname(__FILE__).'/members.csv');
	$raws = explode("\n", $csv);
	execute_set_db();
	foreach($raws as $raw){
		$columns = explode(',', $raw);
		if(isset($columns[1]) and strlen($columns[1])) $login_name = $columns[1];
		else $login_name = $columns[0];
		
		if(strlen($columns[0]) and !wrest_check_user_exist($login_name, $columns[0])){
			wrest_insert_user($login_name, $columns[0]);
		}
	}
}

function wrest_check_user_exist($login_name, $email){
	$clause = "WHERE email='$email' OR login_name='$login_name'";
	return count(db_select_single_column('users', 'id', $clause));
}

function wrest_insert_user($login_name, $email){
	$data = array(
		'email' => $email,
		'login_name' => $login_name,
		'section' => SECTION,
		'login_name_hash' => sha1($login_name),
		'email_hash' => sha1($email),
	);
	$uid = db_insert('users', $data);
	$data = array(
		'groups' => WREST_MEMBER_GROUP,
		'users' => $uid,
		'section' => SECTION,
	);
	db_insert('map', $data);
}

function wrest_get_meeting(){
	$clause = 'WHERE SECTION='.SECTION.' AND publishing_status < 2 ';
	$clause.= 'ORDER BY meeting_date DESC LIMIT '.cc('wrest_meeting_number');
	$column = array('id', 'topic', 'content', 'icon');
	$data = db_select('meeting', $column, $clause);
	foreach($data as $key => $value){
		$data[$key]['summary'] = wrest_word_wrap($value['content']);
	}
	return $data;
}

function wrest_get_forum(){
	$clause = 'WHERE SECTION='.SECTION.' AND publishing_status < 2 ';
	$clause.= 'ORDER BY comment_time DESC LIMIT '.cc('wrest_forum_number');
	$column = array('id', 'topic', 'content');
	$data = db_select('forum_entry', $column, $clause);
	foreach($data as $key => $value){
		$data[$key]['summary'] = wrest_word_wrap($value['content']);
		$data[$key]['icon'] = 'private/module/wrest/theme/talk.png';
	}
	return $data;
}

function wrest_get_news(){
	return wrest_get_blog(cc('wrest_news_category'));
}

function wrest_get_article(){
	return wrest_get_blog(cc('wrest_article_category'));
}

function wrest_get_blog($category){
	$clause = 'WHERE SECTION='.SECTION.' AND category='.$category.' AND publishing_status < 2 ';
	$clause.= 'ORDER BY publish_time DESC LIMIT '.cc('wrest_meeting_number');
	$column = array('id', 'topic', 'intro', 'icon');
	$data = db_select('blog', $column, $clause);
	foreach($data as $key => $value){
		$data[$key]['summary'] = wrest_word_wrap($value['intro']);
	}
	return $data;
}

function wrest_word_wrap($content){
	$content = strip_tags($content);
	$splitted = explode(' ', $content);
	$wrapped = '';
	$count = cc('wrest_word_count');
	for($i=0; $i < $count; $i++){
		if(isset($splitted[$i])) $wrapped .= $splitted[$i].' ';
	}
	return $wrapped.' ...';

}

function wrest_get_blog_categrory(){
	$clause = 'WHERE section='.SECTION." AND mode='blog'";
	return db_select_single_column('category', 'category', $clause);
}
?>
