<?php
function module_get_info_gallery(){
	$describe = tt('Gallery allows you to manage your fotos like another content type (tags, category, work-flow & co.). ');
	$describe.= tt('Thumnails of your fotos will be automatically generated.');
	return array(
		'name' => tt('Gallery'),
		'description' => $describe,
	);
}

function module_init_gallery(){
	include_once('Gallery.class.inc');
	include_once('GalleryPicture.class.inc');
	include_once('GalleryConfig.class.inc');
	include_once(ROOT_PATH.'include/tool/widget.tool.inc');
	include_once(ROOT_PATH.'module/flashwidget/flashwidget.module.inc');
	
	$gallery = new Gallery();
	$gallery->initModule('Gallery.class.inc');
	$galleryPicture = new GalleryPicture();
	$galleryPicture->initModule('GalleryPicture.class.inc');
	$galleryConfig = new GalleryConfig();
	$galleryConfig->initModule('GalleryConfig.class.inc');
	
	config_set('gallery_entries_number', 5);
	
	$clause = 'WHERE (section='.SECTION.' AND publishing_status < 2) ORDER BY publish_time DESC';
	flashwidget_add('gallery_last_post', 'gallery', tt('Last posted Galleries'), 'gallery', 'topic', $clause);
	
	$clause = 'WHERE (section='.SECTION.' AND publishing_status < 2 AND comment_time > 0) ORDER BY comment_time DESC';
	flashwidget_add('gallery_last_commented', 'gallery', tt('Last commented Galleries'), 'gallery', 'topic', $clause);
}

function module_drop_gallery(){
	include_once('Gallery.class.inc');
	include_once('GalleryPicture.class.inc');
	include_once('GalleryConfig.class.inc');
	include_once(ROOT_PATH.'include/tool/widget.tool.inc');
	include_once(ROOT_PATH.'module/flashwidget/flashwidget.module.inc');
	
	$gallery = new Gallery();
	$gallery->dropModule();
	$galleryPicture = new GalleryPicture();
	$galleryPicture->dropModule();
	$galleryConfig = new GalleryConfig();
	$galleryConfig->dropModule();
	
	notify_add_info(tt('Gallery has been successfully deactivated'));
	config_drop('gallery_entries_number');
	flashwidget_drop('gallery_last_post');
	flashwidget_drop('gallery_last_commented');
}
?>
