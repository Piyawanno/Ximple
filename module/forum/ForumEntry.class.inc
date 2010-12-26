<?php
if(execute_get_class('forum') == null)  execute_add_class('forum', 'ForumEntry');
include_once(ROOT_PATH.'module/content/Content.class.inc');
include_once('forum.tool.inc');
include('ForumEntryModel.class.inc');

class ForumEntry extends Content{
	function ForumEntry(){
		$this->tableName = 'forum_entry';
		$this->moduleName = 'forum_entry';
		$this->moduleTitle = tt('Forum Entry');
		$this->init(new ForumEntryModel());
		document_set_path(tt('Forum'), 'forum');
		menu_activate('forum');
	}
}
?>
