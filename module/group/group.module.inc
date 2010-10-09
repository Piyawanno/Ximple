<?php
group_switch_load();

function group_switch_load(){
	$splitted = split('_', mm());
	if(count($splitted) > 1 and $splitted[1] == 'role'){
		include('role.module.inc');
	}else{
		include('Group.class.inc');
	}
}
?>
