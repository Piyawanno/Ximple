<?php
class FAQModel extends Model{
	function FAQModel(){
		$this->question = $this->title(tt('question'));
		$this->question->isList = true;
		$this->question->listMode = 'faq#';
		$this->question->isReachable = true;
		$this->category = $this->category('faq');
		
		$option = array(
			0 => tt('draft'),
			1 => tt('publish'),
		);
		$this->status = $this->select(tt('status'), $option);
		$this->status->isList = true;
		$this->answer = $this->text(tt('answer'));
		$this->section = $this->section();
	}
}
?>
