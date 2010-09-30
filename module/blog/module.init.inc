<?php
function module_get_info_blog(){
	$describe = tt('Let your visitors send email to the you with out knowing your email address. ');
	$describe.= tt('Moreover, you can show them your blog information on Blog-Page.');
	return array(
		'name' => tt('Blog'),
		'description' => $describe,
	);
}

function module_init_blog(){
	include_once('Blog.class.inc');
	include_once(ROOT_PATH.'include/tool/block.tool.inc');
	include_once(ROOT_PATH.'module/flashblock/flashblock.module.inc');
	$blog = new Blog();
	$blog->initModule('blog.module.inc');
	config_set('blog_entries_number', 5);
	
	$clause = 'WHERE (section='.SECTION.' AND publishing_status < 2) ORDER BY publish_time DESC';
	flashblock_add('blog_last_post', 'blog', tt('Last posted Blogs'), 'blog', 'topic', $clause);
	
	$clause = 'WHERE (section='.SECTION.' AND publishing_status < 2 AND comment_time > 0) ORDER BY comment_time DESC';
	flashblock_add('blog_last_commented', 'blog', tt('Last commented Blogs'), 'blog', 'topic', $clause);
}

function module_drop_blog(){
	include_once('Blog.class.inc');
	include_once(ROOT_PATH.'include/tool/block.tool.inc');
	include_once(ROOT_PATH.'module/flashblock/flashblock.module.inc');
	$blog = new Blog();
	$blog->dropModule();
	notify_add_info(tt('Blog has been successfully deactivated'));
	config_drop('blog_entries_number');
	flashblock_drop('blog_last_post');
	flashblock_drop('blog_last_commented');
}
?>
