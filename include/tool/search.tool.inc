<?php
global $search_page;
$search_page = false;

function search_set_page(){
	global $search_page;
	$search_page = true;
}

function search_add_source_page($content){
	global $search_page;
	if($search_page and MODE_ID != 0){
		$source = db_select('search_source', array('id'), "WHERE mode='".MODE."' AND mode_id=".MODE_ID);
		if(count($source) == 0){
			$data = array(
				'title' => document_get_title(),
				'description' => document_get_description(),
				'keyword' => document_get_keywords(),
				'content' => input_trim(strip_tags($content)),
				'mode' => MODE,
				'mode_id' => MODE_ID,
				'insert_time' => NOW,
			);
			db_insert('search_source', $data);
		}
	}
}

function search_add_source($mode, $mode_id, $title, $description, $keywords, $content){
	$data = array(
		'title' => $title,
		'description' => $description,
		'keyword' => $keywords,
		'content' => input_trim(strip_tags($content)),
		'mode' => $mode,
		'mode_id' => $mode_id,
		'insert_time' => NOW,
	);
	db_insert('search_source', $data);
}

function search_drop_source($mode=MODE, $mode_id=MODE_ID){
	db_drop_many('search_source', "mode='".$mode."' AND mode_id=".$mode_id);
}

function search_update_source($mode, $mode_id, $title, $description, $keywords, $content){
	$data = array(
		'title' => $title,
		'description' => $description,
		'keyword' => $keywords,
		'content' => input_trim(strip_tags($content)),
		'mode' => $mode,
		'mode_id' => $mode_id,
		'insert_time' => NOW,
	);
	db_update_many('search_source', $data, "mode='".$mode."' AND mode_id=".$mode_id);
}
?>
