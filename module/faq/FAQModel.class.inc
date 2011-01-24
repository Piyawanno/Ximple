<?php
class FAQModel extends Model{
	function FAQModel(){
		
		$this->question = $this->title(tt('question'));
		$this->question->isList = true;
		$this->question->isReachable = true;
		$this->category = $this->category('faq');
		$this->category->isList = true;
		$this->category->isReachable = true;
		$this->question_icon = $this->image('reference image','files/faq/');
		$this->answer = $this->text(tt('answer'));
#		$statusOption = array(
#			0 => tt('disable'),
#			1 => tt('enable')
#			);
#		$this->status = $this->select(tt('status'), $statusOption);
		$this->status = $this->enable(tt('status'));
		$this->status->isList = true;
		$this->status->isReachable = true;
		$this->section = $this->section();
	}
}
?>
