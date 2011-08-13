<?php
require_once('TabMenuModel.class.inc');
require_once('RequirementFileModel.class.inc');
require_once('RequirementLinkModel.class.inc');
require_once('requirement.tool.inc');

class RequirementModel extends Model{
	function RequirementModel(){
		$this->customer_name = $this->title(tt('your name'));
		$this->customer_name->listMode = 'requirement';
		$this->customer_email = $this->email(tt('your email address'));
		$this->get_date = $this->now();
		
		$help = tt('Please fill in form or insert links that have preferable contents.');
		$this->policy = $this->shortText(tt('company policy'), $help);
		$help = tt('Goal or what you expect form this Project.');
		$this->purpose = $this->shortText(tt('concept purpose'), $help);
		
		$this->tab_menu = $this->grid('');
		$this->tab_menu->setModel(new TabMenuModel());
		
		$help = tt('What should your website represent?');
		$this->representation = $this->plain(tt('representation'), $help);
		$help = tt('Which style do you expect from your website?');
		$option = requirement_get_expectation_option();
		$this->expectation = $this->checkbox(tt('expected style'), $option, $help);
		$this->expectation->isSerialize = true;
		$help = tt('Image files, which you would like to ues in your web site.');
		$this->file = $this->grid(tt('image files'), $help);
		$this->file->setModel(new RequirementFileModel());
		$help = tt('Link of your favourite websites.');
		$this->link = $this->grid(tt('example links'), $help);
		$this->link->setModel(new RequirementLinkModel());
		
		$this->section = $this->section();
	}
}
?>
