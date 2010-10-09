<?php
class PageDirectoryModel extends Model{
	function PageDirectoryModel($parent){
		$this->name = $this->title(tt('directory name'));
		$this->name->listMode = 'directory';
		$this->uri = $this->char(tt('URI'));
		$this->category = $this->category('page');
		$this->index_page = new PageColumn();
		$this->icon = $this->imageLoader(tt('icon'), 'files/directory/');
		$this->description = $this->shortText(tt('description'));
		$this->permission = $this->group(tt('editor group'));
		$this->permission->isExceptedGuest = true;
		$this->permission->isExceptedAdmin = true;
		$this->permission->help = tt('User-Groups, which can create Sub-Directory and Page in this Directory.');
		$this->parent = $this->hidden($parent, 'int');
		$this->owner = $this->owner();
		$this->owner->label = tt('created by');
		$this->configuration = new ConfigureColumn();
		$this->create_time = $this->now();
		$this->section = $this->section();
	}
}

class ConfigureColumn extends ModelColumn{
	function ConfigureColumn(){
		$this->type = 'array';
		$this->form = 'none';
		$this->isSerialize = true;
		$this->defaultData = directory_default_configuration();
	}
	
	function triggerPreUpdate(){
		$this->isDB = false;
	}
}

class PageColumn extends ModelColumn{
	function PageColumn(){
		$this->form = 'hidden';
		$this->type = 'int';
	}
	
	public function triggerInsertForm(){
		$this->defaultData = 0;
	}
	
	public function triggerUpdateForm(){
		$this->label = tt('index page');
		$this->form = 'select';
		$this->selection = db_select_single_column('page', 'topic', 'WHERE parent='.mid());
	}
}
?>
