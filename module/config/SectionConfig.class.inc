<?php
execute_add_class('config', 'SectionConfig');
include_once(ROOT_PATH.'include/class/ConfigControl.class.inc');
include('SectionConfigModel.class.inc');

class SectionConfig extends ConfigControl{
	function SectionConfig(){
		$this->moduleName = 'config';
		$this->moduleTitle = tt('Section Configuration');
		$this->addAction('config_clear_db_cache', 'clearDBCache');
		$this->addAction('config_reset', 'reset');
		$this->setAdmin('config_admin');
		$this->init(new SectionConfigModel());
	}
	
	public function save(){
		$oldIcon = cc('icon');
		$this->setLanguage();
		ConfigControl::save();
		$this->uploadIcon($oldIcon);
		$this->setState();
		$this->modelConnector->triggerPostInsert();
	}
	
	public function index(){
		$this->formMeta->id = 'config';
		$this->formMeta->description = tt('You can use this form to configure important parameters of the Section. ');
		$p = tt('Or you can <a href="%s"><strong>reset configurations</strong></a> to the default values.');
		$this->formMeta->description.= sprintf($p, SECTION_URI.Q.'config_reset');
		$this->formMeta->mode = 'config_save';
		$this->formMeta->title = $this->moduleTitle;
		
		$general = $this->getNewConfigForm(tt('General Information'));
		$general->setShowByDefault(true);
		$general->append('section_name');
		$general->append('section_slogan');
		$general->append('index_mode');
		$general->append('home_label');
		$general->append('icon');
		$general->append('notify_interval');
		$general->append('friendly_url_enable');
		$general->append('state');
		
		$language = $this->getNewConfigForm(tt('Language'));
		$language->append('supported_language');
		
		$register = $this->getNewConfigForm(tt('Registration'));
		$register->append('registable');
		$register->append('forget_password');
		
		$time = $this->getNewConfigForm(tt('Time'));
		$time->append('time_zone');
		$time->append('time_format');
		
		$searchEngine = $this->getNewConfigForm(tt('Search Engine'));
		$searchEngine->append('section_description');
		$searchEngine->append('section_keywords');
		
		$html = $this->getNewConfigForm(tt('HTML'));
		$html->append('meta_data');
		$html->append('allowed_tags');
		
		$smiley = $this->getNewConfigForm(tt('Smiley'));
		$smiley->append('smiley');
		
		$cacheDescription  = tt('Database cache is a part of the system. It can not be disabled. ');
		$p = tt('You can, however, <a href="%s"><strong>clear database cache clicking here</strong></a>. ');
		$cacheDescription .= sprintf($p, SECTION_URI.Q.'config_clear_db_cache');
		$cacheDescription .= tt('This can take a long time. ');
		$cacheDescription .= tt('It should be noted that after submitting this configuration, ');
		$cacheDescription .= tt('all caches excepted database cache will be cleared.');
		$cache = $this->getNewConfigForm(tt('Cache'));
		$cache->setDescription($cacheDescription);
		$cache->append('cache_mode');
		$cache->append('cache_time');
		
		$feed = $this->getNewConfigForm(tt('Feed'));
		$feed->append('feed_mode');
		$feed->append('feed_type');
		$feed->append('feed_number');
		$feed->append('feed_comment');
		$feed->append('feed_comment_explicit');
		
		$spam = $this->getNewConfigForm(tt('Anti-Spamming'));
		$spam->append('antispam_salt');
		$spam->append('antispam_time');
		
		$syslog = $this->getNewConfigForm(tt('System Log'));
		$syslog->append('syslog_enable');
		$syslog->append('syslog_time');
		$syslog->append('tracker_enable');
		$syslog->append('tracker_time');
		return $this->render();
	}
	
	public function clearDBCache(){
		cache_clear_db();
		execute_set_db();
		document_set_redirect('config');
		notify_add_info(tt('Database cache has been cleared.'));
	}
	
	public function reset(){
		$configFile = ROOT_PATH.'files/config/config'.SECTION.'.php';
		if(is_file($configFile)) unlink($configFile);
		execute_set_db();
		document_set_redirect('config');
		notify_add_info(tt('Configuration have been successfully reset.'));
	}
	
	private function setLanguage(){
		$languageAbbreviation = pp('language_abbreviation');
		$languaDescription = pp('language_description');
		$language = array();
		foreach($languageAbbreviation as $key => $value){
			if(strlen($value) and strlen($languaDescription[$key])){
				$language[$value] = $languaDescription[$key];
			}
		}
		$this->setConfig('supported_language', $language);
	}
	
	private function uploadIcon($oldIcon){
		$dir = ROOT_PATH.'files/misc/';
		if(!is_dir($dir)) mkdir($dir);
		$icon = io_upload(ff('icon'), ROOT_PATH.'files/misc/');
		if(strlen($icon)){
			config_set('icon', $icon);
			if(is_file(ROOT_PATH.$oldIcon) and $oldIcon != 'files/misc/ximple.png'){
				unlink(ROOT_PATH.$oldIcon);
			}
		}else{
			config_set('icon', $oldIcon);
		}
		config_save();
	}
	
	private function setState(){
		$dir = ROOT_PATH.'files/state/';
		if(!is_dir($dir)) mkdir($dir);
		io_write_file($dir.'install', "");
		$dir.= SECTION.'/';
		io_clear_directory($dir);
		if(!is_dir($dir)) mkdir($dir);
		io_write_file($dir.pp('state'), "");
	}
}

?>
