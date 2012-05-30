<?php
class CategoryModel extends Model{
	function CategoryModel($mode){
		$this->category = $this->title(tt('category'));
		$this->category->enableTranslate();

		$this->pic_drop = $this->enable(tt('delete category picture'));
		$this->pic_drop->data = 0;
		$this->pic_drop->isForm = false;
		$this->pic_drop->isDB = false;
		
		$this->pic = $this->image(tt('picture'), 'files/category/', 150);
		$this->pic->isList = true;
		
		$this->description = $this->shortText(tt('description'));
		$this->description->isList = true;
		$this->description->isReachable = true;
		$this->description->enableTranslate();
		$this->mode = $this->hidden($mode, 'char');
		$this->section = $this->section();
	}
	
	function triggerUpdateForm($data){
		if(strlen($data['pic']) and is_file(ROOT_PATH.$data['pic'])){
			$this->pic_drop->isForm = true;
		}
	}
}
?>
