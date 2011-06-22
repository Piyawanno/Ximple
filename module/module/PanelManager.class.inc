<?php
class PanelManager{
	private $name;
	private $control;
	private $admin;
	private $item = array();
	private $role = array();
	
	function PanelManager($name){
		$this->name = $name;
	}
	
	public function setControl($control){
		$this->control = $control;
		$this->admin = $this->control->getAdmin();
	}
	
	public function append($mode, $label){
		$this->item[$mode] = $label;
	}
	
	public function appendRole($roleManager){
		$role = $roleManager->getRole();
		if($role != $this->admin) $this->role[] = $role;
	}
	
	public function submit(){
		foreach($this->item as $mode => $label){
			module_add_panel($this->name, $this->admin, $mode, $label);
			$method = $this->control->getAction($mode);
			echo($label.' (label)<br />');
			foreach($this->role as $role){
				echo($role.' (role)<br />');
				if($this->control->hasAccessMethod($role, $method)){
					module_add_panel($this->name, $role, $mode, $label);
				}
			}
		}
	}
	
	public function drop(){
		module_drop_panel($this->name);
	}
}
?>
