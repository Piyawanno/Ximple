<?php
class FAQModel extends Model{
	function FAQModel(){
		$this->question = $this->title(tt('question'));
		$this->question_icon = $this->image('reference image','files/faq/');
		$this->category = $this->category('faq');
		$this->answer = $this->text(tt('answer'));
		$this->section = $this->section();
	}
}
?>
