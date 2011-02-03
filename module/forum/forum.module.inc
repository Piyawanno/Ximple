<?php
forum_switch();

function forum_switch(){
	$splitted = split('_', MODE);
	if(count($splitted) > 1 and $splitted[1] == 'config'){
		include('ForumConfig.class.inc');
	}elseif(count($splitted) > 1 and $splitted[1] == 'entry'){
		include('ForumEntry.class.inc');
	}else{
		include('Forum.class.inc');
	}
}
?>
