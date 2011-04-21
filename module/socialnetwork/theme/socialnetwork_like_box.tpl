<?php if(!defined('XIMPLE_CMS')) die();?>
<script src="http://connect.facebook.net/en_US/all.js#xfbml=1"></script>
<?php $appearance = cc('socialnetwork_like_box_appearance')?>
<fb:like-box
	href="<?=cc('socialnetwork_like_box_uri')?>"
	width="<?=cc('socialnetwork_like_box_width')?>"
	colorscheme="<?=cc('socialnetwork_like_box_color')?>"
	show_faces="<?=in_array('faces', $appearance) ?'true':'false'?>"
	stream="<?=in_array('stream', $appearance) ?'true':'false'?>"
	header="<?=in_array('header', $appearance) ?'true':'false'?>">
</fb:like-box>
