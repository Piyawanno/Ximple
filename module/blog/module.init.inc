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
	include_once(INCLUDE_PATH.'tool/widget.tool.inc');
	include_once(MODULE_PATH.'flashwidget/FlashWidgetManager.class.inc');
	
	$blog = new Blog();
	$blog->initModule('Blog.class.inc');
	
	$blogConfig = new BlogConfig();
	$blogConfig->initModule('BlogConfig.class.inc');
	
	config_set('blog_entries_number', 5);
	
	$flash = new FlashWidgetManager('blog_last_post');
	$flash->setMode('blog');
	$flash->setName(tt('Last posted Blogs'));
	$flash->setTable('blog');
	$flash->setColumn('topic');
	$flash->setClause('WHERE (section='.SECTION.' AND publishing_status < 2) ORDER BY publish_time DESC');
	$flash->submit();
	
	$flash = new FlashWidgetManager('blog_last_commented');
	$flash->setMode('blog');
	$flash->setName(tt('Last commented Blogs'));
	$flash->setTable('blog');
	$flash->setColumn('topic');
	$flash->setClause('WHERE (section='.SECTION.' AND publishing_status < 2 AND comment_time > 0) ORDER BY comment_time DESC');
	$flash->submit();
	
	$widget = new WidgetManager(tt('Promoted Blogs'), 'blog_promote_widget');
	$widget->submit();
}

function module_drop_blog(){
	include_once('Blog.class.inc');
	include_once('BlogConfig.class.inc');
	include_once(INCLUDE_PATH.'tool/widget.tool.inc');
	include_once(MODULE_PATH.'flashwidget/FlashWidgetManager.class.inc');
	
	$blog = new Blog();
	$blog->dropModule();
	
	$blogConfig = new BlogConfig();
	$blogConfig->dropModule();
	
	$flash = new FlashWidgetManager('blog_last_post');
	$flash->drop();
	
	$flash = new FlashWidgetManager('blog_last_commented');
	$flash->drop();
	
	$widget = new WidgetManager(tt('Promoted Blogs'), 'blog_promote_widget');
	$widget->drop();
	
	notify_add_info(tt('Blog has been successfully deactivated'));
	config_drop('blog_entries_number');
}
?>
