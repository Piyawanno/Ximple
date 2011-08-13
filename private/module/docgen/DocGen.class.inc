<?php
execute_add_class('docgen', 'DocGen');
include('DocGenModel.class.inc');

class DocGen extends Control{
	function DocGen(){
		$this->tableName = 'docgen';
		$this->moduleName = 'docgen';
		$this->moduleTitle = tt('DocGen');
		$this->setAdmin('docgen_admin');
		$this->ownerColumn = 'contributor';
		$this->setAccess();
		$this->setAction();
		$this->init(new DocGenModel());
		document_set_path($this->moduleTitle, $this->moduleName);
	}
	
	public function index(){
		if(gg('id')) return $this->display();
		else return $this->contributorListPage();
	}
	
	public function generatePDF(){
		$this->id = gg('id');
		$fileName = FILES_PATH.'docgen/'.$this->id.'.pdf';
		$this->selectByID($this->column);
		if(!is_file($fileName)){
			$this->generateLatexFile();
			$this->executeXeLatex();
		}
		header('Content-type: ');
		header('Content-Disposition: attachment; filename="'.$this->id.'.pdf"');
		readfile($fileName);
		execute_set_file();
	}
	
	public function insert(){
		Control::insert();
		document_set_redirect('docgen/'.$this->id.'/open_pdf/true');
	}
	
	public function update(){
		Control::update();
		document_set_redirect('docgen/'.$this->id.'/open_pdf/true');
		$this->dropGeneratedFiles();
	}
	
	public function drop(){
		Control::drop();
		$this->dropGeneratedFiles();
	}
	
	public function contributorListPage(){
		$title = sprintf(tt('List of %s for Contributor'), $this->moduleTitle);
		document_set_path($title);
		$p = tt('In the following list, your %s are shown. You can use this page to access them.');
		$this->listMeta->description = sprintf($p, $this->moduleTitle);
		$this->listMeta->mode = 'docgen_contributor_list';
		return $this->renderListPage('WHERE (contributor='.USER_ID.')');
	}
	
	public function adminListPage(){
		$this->modelConnector->setAttribute('contributor', 'isList', true);
		$title = sprintf(tt('List of %s entries for Editor'), $this->moduleTitle);
		document_set_path($title);
		$p = tt('You as Admin can use this page to access %s in Section.');
		$this->listMeta->description = sprintf($p, $this->moduleTitle);
		$this->listMeta->mode = 'docgen_admin_list';
		return $this->renderListPage('WHERE (section='.SECTION.')');
	}
	
	protected function renderListPage($clause){
		$this->listMeta->title = sprintf(tt('List of %s'), $this->moduleTitle);
		$this->listMeta->defaultOrderDesc = 'id';
		$this->selectListPage(20, $clause);
		$this->renderWriter();
		$this->setListWriteIcon(tt('generate new document'));
		$this->setListEditIcon();
		$this->setListDropIcon();
		return Control::renderListPage();
	}
	
	private function display(){
		search_set_page();
		head_add_css('docgen.css');
		$this->id = gg('id');
		$this->selectByID($this->column);
		document_set_path($this->dataByID['topic']);
		$this->formatHTML();
		$this->dataByID['editable'] = $this->checkEditable();
		return render($this->dataByID, 'docgen.tpl', 'docgen');
	}
	
	private function checkEditable(){
		$editable = authority_group('docgen_admin');
		$editable = ($editable or authority_owner($this->dataByID['contributor'], 'docgen_contributor'));
		return $editable;
	}
	
	private function renderWriter(){
		foreach($this->data as $key => $value){
			if(isset($value['contributor'])){
				$this->data[$key]['contributor'] = render_profile_link($value['contributor']);
			}else{
				break;
			}
		}
	}
	
	private function setAccess(){
		$this->addAccessMethod('docgen_contributor', 'index');
		$this->addAccessMethod('docgen_contributor', 'generatePDF');
		$this->addAccessMethod('docgen_contributor', 'contributorListPage');
		$this->addAccessMethod('docgen_contributor', 'write');
		$this->addAccessMethod('docgen_contributor', 'insert');
		$this->addAccessMethod('docgen_contributor', 'edit');
		$this->addAccessMethod('docgen_contributor', 'update');
		$this->addAccessMethod('docgen_contributor', 'drop');
	}
	
	private function setAction(){
		$this->addAction('docgen_generate_pdf', 'generatePDF');
		$this->addAction('docgen_admin_list', 'adminListPage');
		$this->addAction('docgen_contributor_list', 'contributorListPage');
	}
	
	private function dropGeneratedFiles(){
		$fileName = FILES_PATH.'docgen/'.$this->id.'.tex';
		if(is_file($fileName)) io_drop_file($fileName);
		$fileName = FILES_PATH.'docgen/'.$this->id.'.pdf';
		if(is_file($fileName)) io_drop_file($fileName);
		$fileName = FILES_PATH.'docgen/'.$this->id.'.aux';
		if(is_file($fileName)) io_drop_file($fileName);
		$fileName = FILES_PATH.'docgen/'.$this->id.'.log';
		if(is_file($fileName)) io_drop_file($fileName);
	}
	
	private function generateLatexFile(){
		$this->formatLatex();
		$latexSource = render($this->dataByID, 'docgentex.tpl', 'docgentex');
		$fileName = FILES_PATH.'docgen/'.$this->id.'.tex';
		io_write_file($fileName, $latexSource);
	}
	
	private function executeXeLatex(){
		$command  = 'cd '.FILES_PATH.'docgen/ ;';
		$fileName = FILES_PATH.'docgen/'.$this->id.'.tex';
		$command .= 'xelatex '.$fileName;
		exec($command);
	}
	
	private function formatHTML(){
		$this->dataByID['write_date'] = translate_date_th($this->dataByID['write_date']);
		$content = $this->dataByID['content'];
		$content = str_replace(" ", '&#160;', $content);
		$content = str_replace("\n", '<br />', $content);
		$this->dataByID['content'] = $content;
	}
	
	private function formatLatex(){
		$this->dataByID['write_date'] = translate_date_th($this->dataByID['write_date']);
		$content = $this->dataByID['content'];
		$content = str_replace(" ", "\\ ", $content);
		$this->dataByID['content'] = $content;
	}
}
?>
