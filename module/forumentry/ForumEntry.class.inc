<?php
execute_add_class('forumentry', 'ForumEntry');
include_once(ROOT_PATH.'module/content/Content.class.inc');
include('ForumEntryModel.class.inc');
include(ROOT_PATH.'module/forum/forum.tool.inc');

class ForumEntry extends Content{
	function ForumEntry(){
		$this->tableName = 'forumentry';
		$this->moduleName = 'forumentry';
		$this->moduleTitle = tt('Forum Entry');
		$this->init(new ForumEntryModel());
		document_set_path(tt('Forum'), 'forum');
		menu_activate('forum');
	}
}
?>
