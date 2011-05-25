<?php
require_once('CharColumn.class.inc');
class EmailColumn extends CharColumn{
	function renderForm($formID){
		head_add_js_var('emailNotOk', tt('Your Email address is not conformed.'));
		head_add_js('include/javascript/emailcolumn.js');
		$this->setFormAttribute('class', 'email_field');
		return CharColumn::renderForm($formID);
	}
}
?>
