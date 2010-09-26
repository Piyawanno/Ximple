<?php
directory_switch();

function directory_switch(){
	$splitted = split('_', MODE);
	if(count($splitted) > 1 and $splitted[1] == 'config'){
		include('DirectoryConfig.class.inc');
	}else{
		include('PageDirectory.class.inc');
	}
}
?>
