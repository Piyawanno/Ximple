<?php
peopleinfo_switch();

function peopleinfo_switch(){
	$splitted = split('_', MODE);
	if(count($splitted) > 1){
		if($splitted[1] == 'config'){
			include('PeopleConfig.class.inc');
		}elseif($splitted[1] == 'event'){
			include('Event.class.inc');
		}elseif($splitted[1] == 'info'){
			include('Information.class.inc');
		}else{
			include('People.class.inc');
		}
	}else{
		include('People.class.inc');
	}
}
?>
