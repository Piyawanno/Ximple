<?php
function module_get_info_hitdict(){
	return array(
		'name' => tt('HitDict'),
		'description' => tt('Let your visitors sign and write word on your website')
	);
}

function module_init_hitdict(){
	require_once('HitDict.class.inc');
	require_once('HitDictPictureModel.class.inc');
	require_once('HitDictTranslate.class.inc');
	require_once('HitDictVariantModel.class.inc');
	require_once(INCLUDE_PATH.'class/QuickTableCreator.class.inc');
	
	$hitdict = new HitDict();
	$hitdict->initModule('HitDict.class.inc');
	
	$hitdictTranslate = new HitDictTranslate();
	$hitdictTranslate->initModule('HitDictTranslate.class.inc');
	
	$pictureCreator = new QuickTableCreator(new HitDictPictureModel()); //เป็นการสร้างตาราง _เพิ่มจากตารางหลัก
	$pictureCreator->create();
	
	$pictureCreator = new QuickTableCreator(new HitDictVariantModel()); 
	$pictureCreator->create();
	
	$admin = new RoleManager('hitdict_admin');
	$admin->setName('HitDict Administrator');
	$admin->setDescription('Who can edit and drop hitdict.');
	$admin->submit();
	
	$editor = new RoleManager('hitdict_editor');
	$editor->setName('HitDict Editor');
	$editor->setDescription('Who can edit and drop hitdict.');
	$editor->submit();
	
	$panel = new PanelManager('HitDict');
	$panel->appendControl($hitdict);
	$panel->appendControl($hitdictTranslate);
	$panel->append('hitdict_write', 'add new headword');
	$panel->submit();
}

function module_drop_hitdict(){
	require_once('HitDict.class.inc');
	require_once('HitDictTranslate.class.inc');
	
	$hitdict = new HitDict();
	$hitdict->dropModule();
	
	$hitdictTranslate = new HitDictTranslate();
	$hitdictTranslate->dropModule();
	
	$admin = new RoleManager('hitdict_admin');
	$admin->drop();
	
	$editor = new RoleManager('hitdict_editor');
	$editor->drop();
	
	$panel = new PanelManager('HitDIct');
	$panel->drop();
}
?>
