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
	include_once(ROOT_PATH.'include/tool/block.tool.inc');
	include_once(ROOT_PATH.'module/flashblock/flashblock.module.inc');
	$gallery = new Gallery();
	$gallery->initModule('gallery.module.inc');
	config_set('gallery_entries_number', 5);
	
	$clause = 'WHERE (section='.SECTION.' AND publishing_status < 2) ORDER BY publish_time DESC';
	flashblock_add('gallery_last_post', 'gallery', tt('Last posted Gallerys'), 'gallery', 'topic', $clause);
	
	$clause = 'WHERE (section='.SECTION.' AND publishing_status < 2 AND comment_time > 0) ORDER BY comment_time DESC';
	flashblock_add('gallery_last_commented', 'gallery', tt('Last commented Gallerys'), 'gallery', 'topic', $clause);
	
	$galleryPicture = new GalleryPicture();
	$galleryPicture->initModule('GalleryPicture.class.inc');
}

function module_drop_gallery(){
	include_once('Gallery.class.inc');
	include_once(ROOT_PATH.'include/tool/block.tool.inc');
	include_once(ROOT_PATH.'module/flashblock/flashblock.module.inc');
	$gallery = new Gallery();
	$gallery->dropModule();
	notify_add_info(tt('Gallery has been successfully deactivated'));
	config_drop('gallery_entries_number');
	flashblock_drop('gallery_last_post');
	flashblock_drop('gallery_last_commented');
}
?>
