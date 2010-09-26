<?php

function install_init_blog(){
	include_once(ROOT_PATH.'include/config.tools.inc');
	include_once(ROOT_PATH.'module/blog/blog.init.inc');
	include_once(ROOT_PATH.'module/guestbook/guestbook.init.inc');
	
	add_block(tt('Navigation'), '', array());
	add_moduleitem('Home', ROOT_URI);
	add_block_item('Home');
	
	activate_module(0, 'blog');
	activate_module(0, 'guestbook');
	
	append_config('feed_modes', '_blog_');
	append_config('feed_type', 'rss');
	append_config('feed_type', 'atom');
	set_config('feed_comment', '1');
	set_config('index_mode', '_blog_');
	
	save_config();
}

function install_init_personal(){
}

function install_init_community(){
}

function install_init_document(){
}

function install_init_sme(){
}

?>
