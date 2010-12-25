<?php
include_once(ROOT_PATH.'module/content/content.tool.inc');

class DirectoryConfigModel extends Model{
	function DirectoryConfigModel(){
		$this->show_item = new ShowItemColumn();
		$this->extension_mode = $this->char(tt('extension URI'));
		$this->page_list_label = $this->char(tt('label for list of pages'));
		$this->related_page_label  = $this->char(tt('label for related pages'));
		$option = array(
			'introduction' => tt('description with icon'),
			'related' => tt('show related pages by rendered page'),
			'sibling' => tt('show sibling pages by rendered page'),
			'avatar' => tt('writer avatar'),
			'category' => tt('category icon'),
		);
		$this->page_render_item = $this->checkbox(tt('show in rendered page'), $option);
		$this->show_page = new ShowPageColumn();
		
		$this->directory_list_label = $this->char(tt('label for list of sub-directories'));
		$this->show_directory = new ShowDirectoryColumn();
		
		$option = content_get_publishing_status();
		$this->publishing_status = $this->checkbox(tt('available publishing status for contributor'), $option);
		$this->publishing_status_default = $this->radio(tt('default comment permission for contributor'), $option);
		
		$option = array(5 => 5, 10 => 10, 15 => 15, 20 => 20, 50 => 50);
		$this->comment_page_length = $this->select(tt('number of shown comments per page'), $option);
		$this->comment_show_avatar = $this->enable(tt('enable avatar by comment'));
		$this->comment_write_label = $this->title(tt('label for comment write form'));
		$option = content_get_comment_permission();
		$this->comment_permission = $this->checkbox(tt('available publishing status for contributor'), $option);
		$this->comment_permission_default = $this->radio(tt('default publishing status for contributor'), $option);
		
	}
}

class ShowItemColumn extends ModelColumn{
	function ShowItemColumn(){
		$this->label =tt('shown item by rendered directory');
		$this->type = 'array';
		$this->form = 'checkbox';
		$this->isSortable = true;
		$this->option = array();
	}
	
	function triggerUpdateForm(){
		$this->getSelection();
	}
	
	function getSelection(){
		$option = directory_show_item_option();
		foreach($this->data as $key){
			$this->option[$key] = $option[$key];
		}
		
		foreach($option as $key => $value){
			if(!isset($this->option[$key])) $this->option[$key] = $value;
		}
	}
}

class ShowPageColumn extends ModelColumn{
	function ShowPageColumn(){
		$this->label = tt('select and sort pages shown in list');
		$this->type = 'array';
		$this->form = 'checkbox';
		$this->isSortable = true;
		$this->option = array();
	}
	
	function triggerUpdateForm(){
		$this->getSelection();
	}
	
	function getSelection(){
		$selection = array();
		$clause = 'WHERE (parent='.mid().") ";
		$item = db_select_single_column('page', 'topic', $clause);
		foreach($item as $id => $topic){
			$mode = 'page_edit/'.$id.'/parent/'.mid();
			$render  = render_icon($mode, 'files/icon/edit.png', '');
			$mode = 'page_drop/'.$id;
			$render .= render_icon($mode, 'files/icon/drop.png', '');
			$render .= '<a href="'.SECTION_URI.Q.'page/'.$id.'">'.$topic.'</a>';
			$selection[$id] = $render;
		}
		foreach($this->data as $id){
			if(isset($selection[$id])) $this->option[$id] = $selection[$id];
		}
		foreach($selection as $key => $value){
			if(!isset($this->option[$key])) $this->option[$key] = $value;
		}
	}
}

class ShowDirectoryColumn extends ModelColumn{
	function ShowDirectoryColumn(){
		$this->label = tt('select and sort sub-directories shown in list');
		$this->type = 'array';
		$this->form = 'checkbox';
		$this->isSortable = true;
		$this->option = array();
	}
	
	function triggerUpdateForm(){
		$this->getSelection();
	}
	
	function getSelection(){
		$selection = array();
		$clause = 'WHERE (parent='.mid().") ";
		$item = db_select_single_column('directory', 'name', $clause);
		foreach($item as $id => $topic){
			$mode = 'directory_edit/'.$id.'/parent/'.mid();
			$render  = render_icon($mode, 'files/icon/edit.png', '');
			$mode = 'directory_drop/'.$id;
			$render .= render_icon($mode, 'files/icon/drop.png', '');
			$render .= '<a href="'.SECTION_URI.Q.'directory/'.$id.'">'.$topic.'</a>';
			$selection[$id] = $render;
		}
		foreach($this->data as $id){
			$this->option[$id] = $selection[$id];
		}
		foreach($selection as $key => $value){
			if(!isset($this->option[$key])) $this->option[$key] = $value;
		}
	}
}
?>
