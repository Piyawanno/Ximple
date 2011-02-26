<?php
advertise_switch();
execute_add_function('advertise_banner');

function advertise_switch(){
	$splitted = split('_', MODE);
	if(count($splitted) > 1 and $splitted[1] == 'config'){
		execute_add_class('advertise', 'AdvertiseConfig');
		include('AdvertiseConfig.class.inc');
	}else{
		execute_add_class('advertise', 'Advertise');
		include('Advertise.class.inc');
	}
}

function advertise_banner(){
	include_once('Advertise.class.inc');
	$advertise = new Advertise();
	return $advertise->renderBanner();
}
?>
