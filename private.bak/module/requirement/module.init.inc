<?php
function module_get_info_requirement(){
	return array(
		'name' => tt('Requirement Sheet'),
		'description' => tt('Requirement Sheet for Customers of XimpleSoft'),
	);
}

function module_init_requirement(){
	require_once(INCLUDE_PATH.'class/QuickTableCreator.class.inc');
	require_once('Requirement.class.inc');
	require_once('RequirementFileModel.class.inc');
	require_once('RequirementLinkModel.class.inc');
	require_once('TabMenuModel.class.inc');
	
	$requirement = new Requirement();
	$requirement->initModule('Requirement.class.inc');
	
	$fileCreator = new QuickTableCreator(new RequirementFileModel());
	$fileCreator->create();
	
	$linkCreator = new QuickTableCreator(new RequirementLinkModel());
	$linkCreator->create();
	
	$tabCreator = new QuickTableCreator(new TabMenuModel());
	$tabCreator->create();
	
	$admin = new RoleManager('requirement_admin');
	$admin->setName('Requirement Administrator');
	$admin->setDescription('Who can view, edit and drop Requirement Sheet.');
	$admin->submit();
	
	$panel = new PanelManager('Requirement Sheet');
	$panel->setControl($requirement);
	$panel->append('requirement_list', 'list all requirement');
	$panel->append('requirement_write', 'write new requirement');
	$panel->appendRole($admin);
	$panel->submit();
	
	$directory = FILES_PATH.'requirement/';
	if(!is_dir($directory)) mkdir($directory);
	$directory .= SECTION.'/';
	if(!is_dir($directory)) mkdir($directory);
}

function module_drop_requirement(){
	require_once('Requirement.class.inc');
	
	$requirement = new Requirement();
	$requirement->dropModule();
	
	$admin = new RoleManager('requirement_admin');
	$admin->drop();
}
?>
