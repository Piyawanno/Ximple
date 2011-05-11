<?php
execute_add_class('peopleinfo', 'People');

include_once('PeopleModel.class.inc');
include_once('peopleinfo.tool.inc');

class People extends Control{
	function People(){
		$this->moduleTitle = tt('People');
		$this->moduleName = 'peopleinfo';
		$this->tableName = 'people';
		$this->setAdmin('peopleinfo_admin');
		$this->init(new PeopleModel());
	}
	
	public function write(){
		head_add_css('peopleinfo.css');
		head_add_js('module/peopleinfo/peopleinfo.js');
		head_add_js('include/external/sha1.js');
		
		$description  = tt("Only User with the Role of 'People Information Related' can be inserted into database. ");
		head_add_js_var('peopleinfoRoleWarning', $description.tt('Please user this form to insert new User.'));
		$description .= sprintf(tt('You can use <a href="%s">User Management</a> to add the Role to Users.'), SECTION_URI.Q.'user');
		
		$this->formMeta->description  = render_ajax_icon('addPeopleUser', 'files/icon/add.png', tt('Add new User'));
		$this->formMeta->description .= '<p>'.$description.'</p>';
		$form  = Control::write();
		$form .= '<div id="peopleinfo_user_dialog" title="'.tt('Add new User').'"></div>';
		return $form;
	}
}

?>
