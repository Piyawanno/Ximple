<?php
function module_get_info_blog(){
	$describe = tt('Blogging system for Ximple (see <a href="http://en.wikipedia.org/wiki/Blog">Wikipedia</a> for more information about blog).');
	return array(
		'name' => tt('Blog'),
		'description' => $describe,
	);
}

function module_init_blog(){
	include_once('Blog.class.inc');
	include_once('BlogConfig.class.inc');
	include_once(ROOT_PATH.'include/tool/widget.tool.inc');
	include_once(ROOT_PATH.'module/flashwidget/flashwidget.module.inc');
	
	$blog = new Blog();
	$blog->initModule('Blog.class.inc');
	
	$blogConfig = new BlogConfig();
	$blogConfig->initModule('BlogConfig.class.inc');
	
	config_set('blog_entries_number', 5);
	
	$clause = 'WHERE (section='.SECTION.' AND publishing_status < 2) ORDER BY publish_time DESC';
	flashwidget_add('blog_last_post', 'blog', tt('Last posted Blogs'), 'blog', 'topic', $clause);
	
	$clause = 'WHERE (section='.SECTION.' AND publishing_status < 2 AND comment_time > 0) ORDER BY comment_time DESC';
	flashwidget_add('blog_last_commented', 'blog', tt('Last commented Blogs'), 'blog', 'topic', $clause);
	
	widget_add(tt('Promoted Blogs'), 'blog_promote_widget');
}

function module_drop_blog(){
	include_once('Blog.class.inc');
	include_once('BlogConfig.class.inc');
	include_once(ROOT_PATH.'include/tool/widget.tool.inc');
	include_once(ROOT_PATH.'module/flashwidget/flashwidget.module.inc');
	
	$blog = new Blog();
	$blog->dropModule();
	$blogConfig = new BlogConfig();
	$blogConfig->dropModule();
	
	notify_add_info(tt('Blog has been successfully deactivated'));
	config_drop('blog_entries_number');
	flashwidget_drop('blog_last_post');
	flashwidget_drop('blog_last_commented');
}
?>
