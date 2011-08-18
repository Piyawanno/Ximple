<?php
function module_get_info_develcard(){
	return array(
		'name' => tt('DevelCard'),
		'description' => tt('Development card for software improvments')
	);
}

function module_init_develcard(){
	include_once('DevelCard.class.inc');
	include_once('DevelCardConfig.class.inc');
	include_once('ResolverModel.class.inc');
	include_once(INCLUDE_PATH.'tool/widget.tool.inc');
	include_once(INCLUDE_PATH.'class/QuickTableCreator.class.inc');
	include_once(MODULE_PATH.'flashwidget/FlashWidgetManager.class.inc');
	
	$develcard = new DevelCard();
	$develcard->initModule('DevelCard.class.inc');
	
	$develcardConfig = new DevelCardConfig();
	$develcardConfig->initModule('DevelCardConfig.class.inc');
	
	$resolverCreator = new QuickTableCreator(new ResolverModel());
	$resolverCreator->create();
	
	$admin = new RoleManager('develcard_admin');
	$admin->setName('DevelCard Administrator');
	$admin->setDescription('Who can configure, edit and drop DevelCard.');
	$admin->submit();
	
	$moderator = new RoleManager('develcard_moderator');
	$moderator->setName('DevelCard Moderator');
	$moderator->setDescription('Who can edit and drop DevelCard.');
	$moderator->submit();
	
	$resolver = new RoleManager('develcard_resolver');
	$resolver->setName('DevelCard Resolver');
	$resolver->setDescription('Who must resolve problems mentioned in DevelCard.');
	$resolver->submit();
	
	$reporter = new RoleManager('develcard_reporter');
	$reporter->setName('DevelCard Reporter');
	$reporter->setDescription('Who can DevelCard Report.');
	$reporter->submit();
	
	$panel = new PanelManager('DevelCard');
	$panel->setControl($develcard);
	$panel->append('develcard_config', 'configure DevelCard');
	$panel->append('develcard_personal', 'my Develcard');
	$panel->append('develcard_personal_list', 'list of personals');
	$panel->append('develcard_write', 'submit new DevelCard');
	$panel->appendRole($admin);
	$panel->appendRole($moderator);
	$panel->appendRole($resolver);
	$panel->appendRole($reporter);
	$panel->submit();
	
	module_add('develcard', 'develcard.widget.module.inc', tt('DevelCard'), 'widget');
	
	$flash = new FlashWidgetManager('develcard_recent_progress');
	$flash->setMode('develcard');
	$flash->setName(tt('Recent DevelCard in progress'));
	$flash->setTable('develcard');
	$flash->setColumn('topic');
	$flash->setClause('WHERE (section='.SECTION.' AND status=1) ORDER BY comment_time DESC');
	$flash->submit();
	
	$widget = new WidgetManager(tt('My DevelCard in progress'), 'develcard_widget_resolver');
	$widget->setFormMode('develcard_widget_resolver_config');
	$widget->setSaveMode('develcard_widget_resolver_save');
	$widget->submit();
	
	$widget = new WidgetManager(tt('DevelCard of current User in progress'), 'develcard_widget_personal');
	$widget->setFormMode('develcard_widget_personal_config');
	$widget->setSaveMode('develcard_widget_personal_save');
	$widget->submit();
	
	notify_add_subscribe('develcard', tt('someone posts in DevelCard', true));
	notify_add_subscribe('develcard_comment', tt('someone comments on DevelCard', true));
	
	if(!is_array(cc('develcard_type'))){
		config_set('develcard_access', 2);
		config_set('develcard_pixel_per_point', 12);
		config_set('develcard_load_color', '#ffffff');
		config_set('develcard_load_bg_color', '#aa00aa');
		config_set('develcard_point_color', '#ffffff');
		config_set('develcard_point_bg_color', '#00aaaa');
	
		config_set('develcard_list_per_page', 20);
		config_set('develcard_hight_color', '#ff0000');
		config_set('develcard_medium_color', '#ffff00');
		config_set('develcard_low_color', '#00ff00');
		config_set('develcard_no_effect_color', '#0000ff');
		config_set('develcard_type', develcard_get_default_type_option());
		config_set('develcard_comment_write_label', tt('Please, write your opinion'));
		config_set('develcard_comment_page_length', 10);
	
		config_set('develcard_widget_resolver_number', 5);
		config_set('develcard_widget_personal_number', 5);
	}
}

function module_drop_develcard(){
	include_once('DevelCard.class.inc');
	include_once('DevelCardConfig.class.inc');
	include_once(INCLUDE_PATH.'tool/widget.tool.inc');
	
	$develcard = new DevelCard();
	$develcard->dropModule();
	
	$develcardConfig = new DevelCardConfig();
	$develcardConfig->dropModule();
	
	$admin = new RoleManager('develcard_admin');
	$admin->drop();
	
	$moderator = new RoleManager('develcard_moderator');
	$moderator->drop();
	
	$reporter = new RoleManager('develcard_reporter');
	$reporter->drop();
	
	$panel = new PanelManager('DevelCard');
	$panel->drop();
	
	notify_drop_subscribe('develcard');
	notify_drop_subscribe('develcard_comment');
}
?>
