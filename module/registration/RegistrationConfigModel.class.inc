<?php
class RegistrationConfigModel extends Model{
	function RegistrationConfigModel(){
		$this->registration_enable = $this->enable(tt('regitration enable'));
		$this->registration_page = $this->shorttext(tt('text in reristration page'));
		$this->registration_reply = $this->shorttext(tt('auto reply text'));
	}
}
?>
