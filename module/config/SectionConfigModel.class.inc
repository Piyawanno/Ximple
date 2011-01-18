<?php
class SectionConfigModel extends Model{
	function SectionConfigModel(){
		$this->section_name = $this->title(tt('section name'));
		$this->section_slogan = $this->char(tt('section solgan'));
		$this->home_label = $this->title(tt('home lable'));
		$this->index_mode = $this->select('fronpage module', cc('module_name'));
		$this->icon = $this->image(tt('section icon (16x16)'), 'files/misc/');
		
		
		if(function_exists('apache_get_modules')) $module = apache_get_modules();
		else $module = null;
		if($module==null or in_array('mod_rewrite', $module)){
			$this->friendly_url_enable = $this->enable(tt('enable friendly URI'));
		}else{
			$this->friendly_url_enable = $this->hidden();
			$this->friendly_url_enable->type = 'int';
			$this->friendly_url_enable->defaultData = 0;
		}
		
		$option = array(
			'develop' => tt('development'),
			'product' => tt('production'),
			'maintain' => tt('maintenance'),
		);
		$this->state = $this->radio(tt('section state'), $option);
		
		$this->registable = $this->enable(('Enable registration for new users'));
		$this->forget_password = $this->enable(('Enable password recovery'));
		
		$help = tt('Add supported language for contents in Section.');
		$this->supported_language = $this->grid(tt('Supported language'), $help);
		$this->supported_language->append('language_abbreviation', Model::char(tt('abbreviation')));
		$this->supported_language->append('language_description', Model::char(tt('description')));
		
		$option = timezone_identifiers_list();
		$option = array_combine($option, $option);
		$this->time_zone = $this->select(tt('time zone'), $option);
		
		$formats = array('d F Y', 'd M Y', 'd F y', 'd M y');
		$option = array();
		foreach($formats as $format){
			$option[$format] = date($format);
		}
		$this->time_format = $this->select(tt('time format'), $option);
		
		$timeInterval = array(5, 10, 30, 60, 300, 600, 1800);
		$this->notify_interval = $this->timeInterval(tt('notification refresh interval'), $timeInterval);
		
		$cacheOptions = array(
			3 => tt('agressive process cache (side-effects)'),
			2 => tt('page cache (recommended)'),
			1 => tt('partly process cache'),
			0 => tt('database cache only'),
		);
		$this->cache_mode = $this->radio(tt('cache mode'), $cacheOptions);
		$timeInterval = array(30, 60, 300, 600, 1800, 3600, 6*3600, 12*3600, 24*3600, 48*3600);
		$this->cache_time = $this->timeInterval(tt('cache time'), $timeInterval);
		
		$this->section_description = $this->plain(tt('description'));
		$this->section_keywords = $this->plain(tt('keywords'));
		
		$this->meta_data = $this->plain(tt('HTML header meta-data'));
		$this->allowed_tags = $this->plain(tt('allowed HTML-TAG'));
		
		$availableFeed = cc('feed_available_mode');
		if(!is_array($availableFeed)) $availableFeed = array();
		$this->feed_mode = $this->checkbox(tt('modules enabled feed'), $availableFeed);
		$this->feed_type = $this->checkbox(tt('feed type'), array('atom' => 'Atom', 'rss' => 'RSS'));
		$this->feed_number = $this->select(tt('number of feed entries'), array(5=>5, 10=>10, 15=>15, 20=>20));
		$this->feed_comment = $this->enable(tt('enable comment feed'));
		$this->feed_comment_explicit = $this->enable(tt('explicit comment feed'));
		
		$this->antispam_salt = $this->title(tt('antispam salt'));
		$timeInterval = array(3600, 2*3600, 6*3600, 12*3600);
		$this->antispam_time = $this->timeInterval(tt('antispam time'), $timeInterval);
		
		$this->syslog_enable = $this->enable(tt('system logging enable'));
		$timeInterval = array(3*24*3600, 5*24*3600, 7*24*3600, 15*24*3600, 30*24*3600, 90*24*3600, 120*24*3600, 180*24*3600);
		$this->syslog_time = $this->timeInterval(tt('system logging expiration'), $timeInterval);
		$this->tracker_enable = $this->enable(tt('user tracker enable'));
		$this->tracker_time = $this->timeInterval(tt('user tracker expiration'), $timeInterval);
	}
}

?>
