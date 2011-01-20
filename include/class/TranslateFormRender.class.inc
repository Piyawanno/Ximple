<?php
class TranslateFormRender extends FormRender{
	function TranslateFormRender($modelConnector, $formMeta){
		FormRender::FormRender($modelConnector, $formMeta);	
	}
	
	protected function getFormColumn(){
		$this->modelConnector->getTranslateFormColumn();
	}
}
?>
