<?php
execute_add_class('hitpedia', 'HitPedia');
include('HitPediaModel.class.inc');

class HitPedia extends Control{
	function HitPedia(){
		$this->moduleTitle = tt('HitPedia');
		$this->moduleName = 'hitpedia';
		$this->tableName = 'hitpedia';
		$this->writeLabel = tt('Add new Headword into HitPedia');
		$this->init(new HitPediaModel());
		
		document_set_path($this->moduleTitle, $this->fullModuleName);
		$this->setAccess();
		$this->setAction();
	}
	
	public function index(){
		$this->sortLanguangeLink();
		$this->id = (int) gg('id');
		if ($this->id) return $this->renderHeadword();
		else return $this->listPage();
	}
	
	private function sortLanguangeLink(){
		$message = tt('The followed list show all Headwords in all languages. ');
		$message .= tt('You can select Keywords sorted by followed language pair.<br>');
		$this->listMeta->title = 'Headword of HitPedia';
		$this->listMeta->description = $message;
		$pair = gg('pair');
		$sortlanguage = hitpedia_get_language_pair_option();
		
		if($pair != null){
			$sortLabel = tt('sort by').' : '.$sortlanguage[$pair];
			$this->listMeta->title .= '  ('.$sortLabel.')';
			document_set_path($sortLabel, $this->fullModuleName);
		}
		
		$item = '';
		foreach($sortlanguage as $key => $value){
			if($pair != $key){
				$item .= '<li>'.render_operation_link('hitpedia_sort_by_language', 'pair/'.$key, $value).'</li>';
			}
		}
		
		$this->listMeta->description.= '<ul>'.$item;
		$this->listMeta->description .= '<li>'.render_operation_link('hitpedia', null ,'show all').'</li>';
		$this->listMeta->description.= '</ul>';
	}
		
	public function write(){
		$this->setConfigForm();
		return Control::write();
	}
	
	public function edit(){
		$this->setConfigForm();
		return Control::edit();
	}
	
	private function setConfigForm(){
		$pronunciation = $this->getNewConfigForm(tt('pronunciation'));
		$pronunciation->append('pronunciation_th');
		$pronunciation->append('pronunciation_pi');
		$pronunciation->append('pronunciation_ipa');
		
		$variant = $this->getNewConfigForm(tt('variant form'));
		$variant->append('variant');
		
		$picture = $this->getNewConfigForm(tt('picture'));
		$picture->append('picture');
	}
	
	public function renderListPageSortByLanguage(){
	 	$this->sortLanguangeLink();
		$this->setListWriteIcon();
		$this->setListEditIcon();
		$this->setListDropIcon();
	
		$clause = 'WHERE language like"%' . gg('pair').'%"';
	    $this->selectListPage(20, $clause);
		return $this->renderListPage();
	}
	
	private function renderHeadword(){
		head_add_css('hitpedia.css');
		#head_add_js(SECTION_URI.'private/module/hitpedia/javascript/hitpedia.js');
		#head_add_js_var('headWordLabel', tt('Headword'));
		$this->selectByID($this->column);
		head_add_js_array('headwordData', $this->dataByID);
		$renderArray = array(
			'data' => $this->dataByID
		);	
		return render($renderArray, 'hitpedia_headword.tpl', 'hitpedia_headword');
	}
	
	private function setAccess(){
		$this->setAdmin('hitdict_admin');

		$this->addAccessMethod('guest','index');
		
		$this->addAccessMethod('hitdict_editor','write');
		$this->addAccessmethod('hitdict_editor','insert');
		$this->addAccessMethod('hitdict_editor', 'getHeadword');
	}
	
	private function setAction(){
		$this->addAction('hitpedia_sort_by_language', 'renderListPageSortByLanguage');
	}
}
?>
