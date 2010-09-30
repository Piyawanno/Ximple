<?php
video_switch();

function video_switch(){
	$splitted = split('_', MODE);
	if(count($splitted) > 1 and $splitted[1] == 'config'){
		include('VideoConfig.class.inc');
	}else{
		include('Video.class.inc');
	}
}
?>
