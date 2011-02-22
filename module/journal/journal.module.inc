<?php
blog_switch();

function blog_switch(){
	$splitted = split('_', MODE);
	if(count($splitted) > 1 and $splitted[1] == 'config'){
		include('JournalConfig.class.inc');
	}else{
		include('Journal.class.inc');
	}
}
?>
