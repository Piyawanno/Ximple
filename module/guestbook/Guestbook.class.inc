<?php
execute_add_class('guestbook', 'Guestbook');
include('GuestbookModel.class.inc');

class Guestbook extends Control{
	function Guestbook(){
		$this->moduleTitle = tt('Guestbook');
		$this->moduleName = 'guestbook';
		$this->tableName = 'guestbook';
		$this->addAccessMethod('guest', 'index');
		$this->addAccessMethod('guest', 'write');
		$this->addAccessMethod('guest', 'insert');
		$this->setAdmin('guestbook_admin');
		$this->init(new GuestbookModel());
		$this->formMeta->isCaptcha = true;
		$this->writeLabel = sprintf(tt('Sign on %s'), cc('section_name'));
	}
	
	function index(){
		$this->selectPage($this->column, 10, 'WHERE section='.SECTION.' ORDER BY id DESC');
		head_add_css('guestbook.css');
		document_set_title($this->moduleTitle);
		$rednerArray = array(
			'is_admin' => authority_group('guestbook_admin'),
			'data' => $this->data
		);
		$render  = render($rednerArray, 'guestbook.tpl', 'guestbook');
		$render .= $this->pager->render('guestbook');
		return $render;
	}
}
?>
