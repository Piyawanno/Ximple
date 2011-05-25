<?php
abstract class FormModelRender{
	protected $render = array();
	protected abstract function getFormColumn();
	protected function renderFormModel($id){
		$modelArray = $this->getFormColumn();
		foreach($modelArray as $name => $model){
			if(!isset($mode->name)) $model->name = $name;
			$this->render[$name] = $model->renderForm($id);
		}
		return $this->render;
	}
}
?>
