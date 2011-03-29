<?php
gallery_switch();

function gallery_switch(){
	$splitted = split('_', MODE);
	if(count($splitted) > 1 and $splitted[1] == 'config'){
		include('GalleryConfig.class.inc');
	}else{
		include('Gallery.class.inc');
	}
}
?>
