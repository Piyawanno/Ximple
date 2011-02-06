<?php
function forum_get_allowed_id(){
	$forum_permission = db_select_single_column('forum', 'allowed_group', 'WHERE section='.SECTION);
	$allowed_id = array();
	foreach($forum_permission as $key => $value){
		$group = unserialize($value);
		if(authority(array(), $group) or authority_group('forum_admin')){
			$allowed_id[] = $key;
		}
	}
	return $allowed_id;
}

function forum_get_info($forum_id){
	$clause = 'WHERE id='.((int) $forum_id);
	$forum = db_select('forum', array('category', 'name', 'description'), $clause);
	return $forum[0];
}

function forum_set_path($forum_id){
	$forum = forum_get_info($forum_id);
	$category_id = $forum['category'];
	$clause = 'WHERE id='.$category_id;
	$category = db_select('category', array('category'), $clause);
	document_set_path($category[0]['category'], 'forum/category/'.$category_id);
	document_set_path($forum['name'], 'forum_entry_list/forum/'.$forum_id);
}

function forum_set_panel(){
	menu_drop('forum_entry');
	module_drop_panel('Forum');
	module_drop_panel('Forum Entry');
	menu_add('forum', tt('Forum'));
	list($adminGroup, $editorGroup, $contributorGroup) = content_get_group('forumentry');
	module_add_panel('Forum', $adminGroup, 'category/module/forum', 'Forum category');
	module_add_panel('Forum', $adminGroup, 'forum_entry_write', 'write new Forum entry');
	module_add_panel('Forum', $adminGroup, 'forum_entry_contributor_list', 'list my Forum entry');
	module_add_panel('Forum', $adminGroup, 'forum_entry_editor_list', 'list Forum entry in Section');
	module_add_panel('Forum', $adminGroup, 'forum_config', 'configure Forum');
	module_add_panel('Forum', $adminGroup, 'forum_manage', 'sort and manage Forum');
	
	module_add_panel('Forum', $editorGroup, 'forum_entry_write', 'write new Forum entry');
	module_add_panel('Forum', $editorGroup, 'forum_entry_contributor_list', 'list my Forum entry');
	module_add_panel('Forum', $editorGroup, 'forum_entry_editor_list', 'list Forum entry in Section');
	
	module_add_panel('Forum', $contributorGroup, 'forum_entry_write', 'write new Forum entry');
	module_add_panel('Forum', $contributorGroup, 'forum_entry_contributor_list', 'list my Forum entry');
}

function forum_render_marked_entry($entry_id, $label){
	if(!empty($entry_id)){
		$column = array('topic', 'writer', 'write_time');
		$cluase = "WHERE id=".((int) $entry_id);
		$data = db_select('forum_entry', $column, $clause);
		$data = $data[0];
		$render = '<p><label>'.$label.' : </label>';
		$render.= '<a href="'.SECTION_URI.Q.'forum_entry/'.$entry_id.'">'.$data['topic'].'</a> ';
		$render.= tt('by').' '.render_profile_link(userinfo_get_info_by_id($data['writer'])).' ';
		$redner.= '@ '.date(cc('time_format'), $data['write_time']).'</p>';
		return $render;
	}
}
?>
