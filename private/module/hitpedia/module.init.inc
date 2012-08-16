<?php
function module_get_info_hitpedia(){
	return array(
		'name' => tt('HitPedia'),
		'description' => tt('Let your visitors sign and write word on your website')
	);
}

function module_init_hitpedia(){
	require_once('HitPedia.class.inc');
	require_once('HitPediaPictureModel.class.inc');
	require_once('HitPediaVariantModel.class.inc');
	#require_once('HitDictTranslate.class.inc');
	#require_once(INCLUDE_PATH.'class/QuickTableCreator.class.inc');
	
	$hitpedia = new HitPedia();
	$hitpedia->initModule('HitPedia.class.inc');
	
	#$hitdictTranslate = new HitDictTranslate();
	#$hitdictTranslate->initModule('HitDictTranslate.class.inc');
	
	$pictureCreator = new QuickTableCreator(new HitPediaPictureModel()); 
	$pictureCreator->create();
	
	$variantCreator = new QuickTableCreator(new HitPediaVariantModel()); 
	$variantCreator->create();
	
	$admin = new RoleManager('hitpedia_admin');
	$admin->setName('HitPedia Administrator');
	$admin->setDescription('Who can edit and drop hitpedia.');
	$admin->submit();
	
	$editor = new RoleManager('hitpedia_editor');
	$editor->setName('HitPedia Editor');
	$editor->setDescription('Who can edit and drop hitpedia.');
	$editor->submit();
	
	$panel = new PanelManager('Hitpedia');
	$panel->appendControl($hitpedia);
	#$panel->appendControl($hitdictTranslate);
	$panel->append('hitpedia_write', 'add new headword');
	$panel->submit();
}

function module_drop_hitpedia(){
	require_once('HitPedia.class.inc');
	#require_once('HitPediaTranslate.class.inc');
	
	$hitpedia = new HitPedia();
	$hitpedia->dropModule();
	
	#$hitdictTranslate = new HitPediaTranslate();
	#$hitdictTranslate->dropModule();
	
	$admin = new RoleManager('hitpedia_admin');
	$admin->drop();
	
	$editor = new RoleManager('hitpedia_editor');
	$editor->drop();
	
	$panel = new PanelManager('HitPedia');
	$panel->drop();
}
?>
