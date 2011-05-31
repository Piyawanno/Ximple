<?php
class FAQModel extends Model{
	function FAQModel(){
		$this->question = $this->title(tt('question'));
		$this->question->isList = true;
		$this->question->isReachable = true;
		
		$this->category = $this->category('faq');
		$this->question_icon = $this->imageLoader(tt('reference image'),'files/faq/');
		$this->answer = $this->text(tt('answer'));
		
		$this->status = $this->enable(tt('status'));
		$this->status->isList = true;
		$this->status->isReachable = true;
		
		$this->section = $this->section();
	}
}
?>
