<?php if(!defined('XIMPLE_CMS')) die();?>
<?php $appearance = cc('socialnetwork_like_box_appearance')?>
<div id="fb-root"></div>
<script>(function(d, s, id) {
  var js, fjs = d.getElementsByTagName(s)[0];
  if (d.getElementById(id)) {return;}
  js = d.createElement(s); js.id = id;
  js.src = "//connect.facebook.net/en_US/all.js#xfbml=1&appId=226181197410086";
  fjs.parentNode.insertBefore(js, fjs);
}(document, 'script', 'facebook-jssdk'));
</script>
<script src="http://connect.facebook.net/en_US/all.js#xfbml=1"></script>
<fb:like-box href="http://www.facebook.com/platform"
	width="292" colorscheme="dark" show_faces="true" stream="true" header="true"></fb:like-box>
<fb:like-box
	href="<?=cc('socialnetwork_like_box_uri')?>"
	width="<?=cc('socialnetwork_like_box_width')?>"
	height="<?=cc('socialnetwork_like_box_height')?>"
	colorscheme="<?=cc('socialnetwork_like_box_color')?>"
	show_faces="<?=in_array('faces', $appearance) ?'true':'false'?>"
	stream="<?=in_array('stream', $appearance) ?'true':'false'?>"
	header="<?=in_array('header', $appearance) ?'true':'false'?>">
</fb:like-box>
