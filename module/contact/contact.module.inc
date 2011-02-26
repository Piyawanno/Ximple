<?php
contact_switch_load();

function contact_switch_load(){
	$splitted = split('_', MODE);
	if(count($splitted) > 1 and $splitted[1] == 'config'){
		include('ContactConfig.class.inc');
	}else{
		include('Contact.class.inc');
	}
}
?>
