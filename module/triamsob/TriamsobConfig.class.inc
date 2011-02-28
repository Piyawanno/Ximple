<?php
include_once(ROOT_PATH.'include/class/ConfigControl.class.inc');
include('TriamsobConfigModel.class.inc');

class TriamsobConfig extends ConfigControl{
	function TriamsobConfig(){
		$this->moduleName = 'triamsob_config';
		$this->moduleTitle = tt('Triamsob Configuration');
		$this->init(new TriamsobConfigModel());
	}
	
	public function index(){
		document_set_path(tt('Triamsob'), 'triamsob');
		$this->formMeta->mode = 'triamsob_config_save';
		$this->formMeta->title = $this->moduleTitle;
		return $this->render();
	}
}
?>
