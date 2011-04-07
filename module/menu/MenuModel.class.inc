<?php

class MenuModel extends Model{
	function MenuModel(){
		$this->title = $this->title(tt('menu title'));
		$this->title->enableTranslate();
		$this->uri = $this->char(tt('URI'), tt('Absolute URI e.g. http://www.wikipedia.org or Ximple internal URI e.g. blog/111.'));
		$this->uri->isNotNull = true;
		$this->block = new MenuBlock();
		$this->sort_number = $this->hidden(0, 'int');
		$this->section = $this->section();
	}
}

class MenuBlock extends ModelColumn{
	function MenuBlock(){
		$this->type = 'int';
		if(cc('menu_include_block')){
			$this->label = tt('includes Block');
			$this->form = 'select';
			$p = tt('Use <a href="%s">block interface</a> for Block configuration.');
			$this->help = sprintf($p, SECTION_URI.Q.'block');
			$this->option = array();
		}else{
			$this->form = 'hidden';
			$this->defaultData = 0;
		}
	}
	
	public function triggerInsertForm(){
		$this->getBlock();
	}
	
	public function triggerUpdateForm(){
		$this->getBlock();
	}
	
	private function getBlock(){
		if($this->form == 'select'){
			$this->option = db_select_single_column('block', 'title', 'WHERE section='.SECTION, true);
			$this->option[0] = cc('None');
			ksort($this->option);
		}
	}
}

?>
