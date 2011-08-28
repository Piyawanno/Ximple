<?php
abstract class OverlayControl extends Control{
	public function init($modelObject){
		Control::init($modelObject);
		$this->setAction();
	}
	
	public function overlayWrite(){
		execute_set_ajax();
		$this->formMeta->isAjax = true;
		$this->formMeta->ajaxFunction = 'overlaySubmitForm';
		return $this->write();
	}
	
	public function overlayEdit(){
		execute_set_ajax();
		$this->formMeta->isAjax = true;
		$this->formMeta->ajaxFunction = 'overlaySubmitForm';
		return $this->edit();
	}
	
	public function overlayRefresh(){
		
	}
	
	private function setAction(){
		$this->addAction($this->fullModuleName.'_overlay_write', 'overlayWrite');
		$this->addAction($this->fullModuleName.'_overlay_edit', 'overlayEdit');
		$this->addAction($this->fullModuleName.'_overlay_refresh', 'overlayRefresh');
	}
}
?>
