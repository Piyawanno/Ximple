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
?>
