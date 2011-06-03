<?php
execute_add_extended_class('advertise', 'config', 'AdvertiseConfig');
include_once(ROOT_PATH.'include/class/ConfigControl.class.inc');
include_once('AdvertiseConfigModel.class.inc');

class AdvertiseConfig extends ConfigControl{
	function AdvertiseConfig(){
		$this->moduleName = 'advertise';
		$this->moduleExtension = 'config';
		$this->moduleTitle = tt('Advertise Configuration');
		
		$this->setAdmin('advertise_admin');
		$this->init(new AdvertiseConfigModel());
	}
	
	public function index(){
		document_set_path(tt('Advertise'), 'advertise');
		$this->formMeta->mode = 'advertise_config_save';
		$this->formMeta->title = $this->moduleTitle;
		return $this->render();
	}
	
	public function save(){
		$position = pp('advertise_block_position');
		foreach($position as $key => $value){
			if(strlen($value) == 0) unset($position[$key]);
		}
		config_set('advertise_block_position', $position);
		config_save();
		document_set_redirect('advertise_config');
		$this->updateBlock();
		execute_set_db();
	}
	
	public function updateBlock(){
		$position = pp('advertise_block_position');
		include_once(ROOT_PATH.'include/tool/block.tool.inc');
		foreach($position as $key => $value){
			block_drop('advertise_banner/'.$key);
			if(strlen($value)){
				block_add($value, 'advertise_banner/'.$key);
			}
		}
		$message = tt('All Advertise banners have been disabled. ');
		$message.= tt('Position of Advertise banners must be rearranged.');
		notify_add_warning($message);
	}
}
?>
