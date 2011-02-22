<?php
tutorialschool_switch();

function tutorialschool_switch(){
	$splitted = split('_', MODE);
	if(count($splitted) > 1 and $splitted[1] == 'config'){
		include('TutorialSchoolConfig.class.inc');
	}else{
		include('TutorialSchool.class.inc');
	}
}
?>
