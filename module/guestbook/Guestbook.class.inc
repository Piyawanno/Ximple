<?php
execute_add_class('guestbook', 'Guestbook');
include('GuestbookModel.class.inc');

class Guestbook extends Control{
	function Guestbook(){
		$this->moduleTitle = tt('Guestbook');
		$this->moduleName = 'guestbook';
		$this->tableName = 'guestbook';
		$this->setAccess();
		$this->init(new GuestbookModel());
		$this->formMeta->isCaptcha = true;
		$this->writeLabel = sprintf(tt('Sign on %s'), cc('section_name'));
		document_set_path($this->moduleTitle, $this->moduleName);
	}
	
	public function index(){
		head_add_css('guestbook.css');
		$this->selectPage($this->column, 1, 'WHERE section='.SECTION.' ORDER BY id DESC');
		$rednerArray = array(
			'is_admin' => authority_group('guestbook_admin'),
			'data' => $this->data
		);
		$render  = render($rednerArray, 'guestbook.tpl', 'guestbook');
		$render .= $this->pager->render('guestbook');
		return $render;
		
	}
	
	private function setAccess(){
		$this->setAdmin('guestbook_admin');
		
		$this->addAccessMethod('guest', 'index');
		$this->addAccessMethod('guest', 'write');
		$this->addAccessMethod('guest', 'insert');
	}
}
?>
