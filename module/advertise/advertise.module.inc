<?php
advertise_switch();

function advertise_switch(){
	$splitted = split('_', MODE);
	if(count($splitted) > 1 and $splitted[1] == 'config'){
		include('AdvertiseConfig.class.inc');
	}else{
		include('Advertise.class.inc');
	}
}
?>
