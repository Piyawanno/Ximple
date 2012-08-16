<?php
execute_add_class('hitdict', 'Hitdict');
include('HitDictModel.class.inc');

class HitDict extends Control{
	function HitDict(){
		$this->moduleTitle = tt('HitDict');
		$this->moduleName = 'hitdict';
		$this->tableName = 'hitdict';
		$this->writeLabel = tt('Add new Keyword into HitDict');
		$this->init(new HitDictModel());
		$this->setAccess();
		$this->setAction();
		document_set_path($this->moduleTitle, $this->fullModuleName);
	}
	
	public function index(){
		$this->id = (int) gg('id');
		if($this->id) return $this->renderHeadword();
		else return $this->listPageWithLanguageSortLabel();
	}
	
	public function getHeadword(){
		execute_set_ajax();
		$clause = 'WHERE headword like"'.gg('wildcard').'%"';
		$option = db_select_single_column($this->tableName, 'headword', $clause);
		return render_autocomplete_option($option);
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
	
	public function write(){
		$this->setConfigForm();
		return Control::write();
	}
	
	public function edit(){
		$this->setConfigForm();
		return Control::edit();
	}
	
	private function sortLanguangeLink(){
		$message = tt('The followed list show all Headwords in all languages. ');
		$message .= tt('You can select Keywords sorted by followed language pair.<br>');
		$this->listMeta->title = 'Headword of HitDict';
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
				$item .= '<li>'.render_operation_link('hitdict_sort_by_language', 'pair/'.$key, $value).'</li>';
			}
		}
		
		$this->listMeta->description.= '<ul>'.$item;
		$this->listMeta->description .= '<li>'.render_operation_link('hitdict', null ,'show all').'</li>';
		$this->listMeta->description.= '</ul>';
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
	
	private function listPageWithLanguageSortLabel(){
		$this->sortLanguangeLink();
		
		return $this->listPage();
	}
	
	private function renderHeadword(){
		$this->selectByID($this->column);
		$renderArray = array(
			'data' => $this->dataByID
		);
		head_add_js_array('headwordData', $this->dataByID);
		return render($renderArray, 'hitdict_headword.tpl', 'hitdict_headword');
		
	
	}
	
	private function setAccess(){
		$this->setAdmin('hitdict_admin');

		$this->addAccessMethod('guest','index');
		
		$this->addAccessMethod('hitdict_editor','write');
		$this->addAccessmethod('hitdict_editor','insert');
		$this->addAccessMethod('hitdict_editor', 'getHeadword');
	}
	
	private function setAction(){
		$this->addAction('hitdict_get_headword', 'getHeadword');
		$this->addAction('hitdict_sort_by_language', 'renderListPageSortByLanguage');
	
	}
}
?>
