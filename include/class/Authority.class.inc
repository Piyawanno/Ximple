<?php

abstract class Authority{
	private $accesMethod = array();
	private $adminGroup;
	private $owner;
	private $action = array();
	
	public function getAction($mode){
		if(isset($this->action[$mode])){
			return $this->action[$mode];
		}else{
			return null;
		}
	}
	
	public function isCallable($methodName){
		if(authority_user($this->owner)){
			return true;
		}elseif(array_key_exists($methodName, $this->accesMethod)){
			$gidArray = $this->accesMethod[$methodName];
			if(in_array('guest', $gidArray)) return true;
			if(in_array('user', $gidArray) and !authority_is_guest()) return true;
			foreach($gidArray as $gid){
				if(authority_group($gid)) return true;
			}
		}elseif(!empty($this->adminGroup)){
			return authority_group($this->adminGroup);
		}else{
			return false;
		}
	}
	
	public function prepareMethod($methodName){
	}
	
	protected function setOwner($owner){
		$this->owner = $owner;
	}
	
	protected function setAdmin($gid){
		$this->adminGroup = $gid;
	}
	
	protected function addAccessMethod($gid, $methodName){
		$this->accesMethod[$methodName][] = $gid;
	}
	
	protected function addAction($mode, $methodName){
		$this->action[$mode] = $methodName;
	}
}

?>
