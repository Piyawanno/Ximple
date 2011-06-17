<?php
if(SECTION != 1) error_denied();
execute_add_class('section', 'Section');
include('SectionModel.class.inc');

define('SECTION_SCRIPT',
"<?php
	define('BOOT_TIME', (float)microtime(true));
	define('SECTION', %s);
	require('../../include/tool/boot.tool.inc');
	boot();
?>");

class Section extends Control{
	function Section(){
		$this->tableName = 'section';
		$this->moduleName = 'section';
		$this->moduleTitle = 'Section';
		$this->addAction('section_redirect', 'redirect');
		$this->addAction('section_manage', 'index');
		$this->setAdmin('section_admin');
		$this->init(new SectionModel());
		document_set_path($this->moduleTitle, 'section_manage');
	}
	
	public function index(){
		$description  = tt('Section is an instance of Ximple. ');
		$description .= tt('You can install Ximple only one time on a server and create multiple Sections. ');
		$description .= tt('Every Section is a self-contained website and has the own configurations but joint user and database.');
		$description .= tt('This can dramatically reduce your work for maintenance of multiple websites.');
		$this->listMeta->title = sprintf(tt('List of %s'), $this->moduleTitle);
		$this->listMeta->defaultOrder = 'id';
		$this->listMeta->description = $description;
		$this->setListWriteIcon();
		$this->setListEditIcon();
		$this->selectListPage();
		return $this->renderListPage();
	}
	
	public function write(){
		$this->initJS();
		head_add_js_var('sectionInsert', true);
		return Control::write();
	}
	
	public function edit(){
		$this->initJS();
		head_add_js_var('sectionUpdateID', $this->id);
		head_add_js_var('sectionInsert', false);
		return Control::edit();
	}
	
	public function insert(){
		$this->initScript();
		$this->initConfig();
		$this->initAdminMap();
		document_set_redirect('section_manage');
	}
	
	public function update(){
		$success = true;
		if($this->id != 1) $this->renamePath();
		if($success){
			Control::update();
			$this->updateConfig();
		}
		document_set_redirect('section_manage');
	}
	
	public function drop(){
		notify_add_error(tt('Section is not allowed to be deleted.'));
	}
	
	public function redirect(){
		$this->id = (int)gg('id');
		$this->selectByID($this->column);
		header('Location: '.ROOT_URI.'section/'.$this->dataByID['path']);
		die();
	}
	
	private function initJS(){
		head_add_js('module/section/section.js');
		head_add_js_var('nameTooShort', tt('Section name is too short.'));
		head_add_js_var('pathTooShort', tt('Section path is too short.'));
		head_add_js_var('nameExists', tt('Section name exists.'));
		head_add_js_var('pathExists', tt('Section path exists.'));
		head_add_js_var('pathNotConformed', tt('Section path is not conformed.'));
	}
	
	private function renamePath(){
		$old_path =  ROOT_PATH.'section/'.$this->dataByID['path'];
		$new_path =  ROOT_PATH.'section/'.pp('path');
		if(is_dir($old_path)){
			@rename($old_path, $new_path) or $success = false;
		}else{
			@mkdir($old_path) or $success = false;
			io_write_file($old_path.'/index.php', sprintf(SECTION_SCRIPT, $this->id));
		}
	}
	
	private function updateConfig(){
		$path = FILES_PATH.'config/config'.$this->id;
		$config = io_unserialize($path);
		$config['section_name'] = pp('name');
		$config['section_path'] = pp('path');
		io_serialize($config, $path);
	}
	
	private function initScript(){
		$success = true;
		$path = ROOT_PATH.'section/'.pp('path').'/';
		if(!is_dir($path)) @mkdir($path) or $success = false;
		if($success) Control::insert();
		if($success and !empty($this->id)){
			io_write_file($path.'index.php', sprintf(SECTION_SCRIPT, $this->id));
		}else{
			$p = tt('Section can not be created. Please check permission of %s.');
			notify_add_error(sprintf($p, ROOT_PATH.'section'));
		}
	}
	
	private function initConfig(){
		$path = FILES_PATH.'config/config'.$this->id;
		$config = config_check_default(array());
		$config['section_name'] = pp('name');
		$config['section_path'] = pp('path');
		io_serialize($config, $path);
	}
	
	private function initAdminMap(){
		$data = array(
			'users' => USER_ID,
			'groups' => 1,
			'section' => $this->id,
		);
		db_insert('map', $data);
	}
}
?>
