<?php
class BlockModel extends Model{
	function BlockModel(){
		$this->title = $this->title(tt('title'));
		$this->title->enableTranslate();
		$this->config_form_mode = $this->hidden();
		$this->config_save_mode = $this->hidden();
		$this->call_mode = $this->hidden();
		$this->position = new BlockPosition();
		$this->sort_number = $this->hidden();
		$this->sort_number->type = 'int';
		
		$this->appear_module = $this->checkbox(tt('appear by module'), cc('module_name'));
		$this->appear_module->isSerialize = true;
		$this->appear_module->help = tt('Check none to allow Block appeared everywhere.');
		
		$help = tt('Above option (appear by module) is deactivated.').' ';
		$help.= tt('Only Ximple URI e.g. blog/111 is allowed.').' ';
		$help.= tt('Use comma to separate multiple URIs.');
		$this->appear_uri = $this->char(tt('appear by URI'), $help);
		
		$this->appear_group = $this->group(tt('appear by group'));
		$this->appear_group->help = tt('Check guest to allow Block appeared for everybody.');
		
		$this->body = $this->shorttext(tt('custom text'));
		$this->body->enableTranslate();
		$this->section = $this->section();
	}
}

class BlockPosition extends ModelColumn{
	function BlockPosition(){
		$this->form = 'hidden';
		$this->type = 'char';
	}
	
	function triggerInsertForm(){
		$position = gg('position');
		if(isset($position) and array_key_exists($position, cc('block_position'))){
			$this->defaultData = $position;
		}else{
			$this->defaultData = 'disabled';
		}
	}
}
?>
