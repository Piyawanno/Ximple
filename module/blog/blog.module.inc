<?php
blog_switch();

function blog_switch(){
	$splitted = split('_', MODE);
	if(count($splitted) > 1 and $splitted[1] == 'config'){
		include('BlogConfig.class.inc');
	}else{
		include('Blog.class.inc');
	}
}
?>
