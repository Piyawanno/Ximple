<?php
class ListPage{
	private $modelConnector;
	private $listMeta;
	private $data;
	private $column;
	private $label;
	
	function ListPage($modelConnector, $listMeta){
		$this->modelConnector = $modelConnector;
		$this->listMeta = $listMeta;
		$this->column = $modelConnector->getColumnName();
	}
	
	public function render($data){
		head_add_css('list.css');
		$this->prepareRender();
		$renderArray = array(
			'data' => $data,
			'meta' => $this->listMeta,
			'sort_mode' => $this->getSortMode(),
			'column' => $this->modelConnector->getColumnNameByBoolean('isList'), 
			'label' => $this->label,
			'is_sort' => $this->modelConnector->getColumnNameByBoolean('isOrderable'),
			'mode' => $this->modelConnector->getColumnAttribute('listMode'),
		);
		return render($renderArray, 'list.tpl', 'list');
	}
	
	public function getClause($where){
		$clause = '';
		list($col, $search) = $this->getSearchRequest();
		if(!empty($search)){
			if(!empty($where)){
				$clause = $where.' AND '.$col." LIKE '%".$search."%'";
			}else{
				$clause = 'WHERE '.$col." LIKE '%".$search."%'";
			}
		}
		if(empty($clause)) $clause = $where;
		$order = gg('order');
		$order_desc = gg('order_desc');
		if(!empty($order) and in_array($order, $this->column)){
			$clause .= ' ORDER BY '.$order;
		}elseif(!empty($order_desc) and in_array($order_desc, $this->column)){
			$clause .= ' ORDER BY '.$order_desc.' DESC';
		}elseif(!empty($this->listMeta->defaultOrder)){
			$clause .= ' ORDER BY '.$this->listMeta->defaultOrder;
		}elseif(!empty($this->listMeta->defaultOrderDesc)){
			$clause .= ' ORDER BY '.$this->listMeta->defaultOrderDesc.' DESC';
		}
		return $clause;
	}
	
	public function getPageMode(){
		$mode  = $this->listMeta->mode;
		$mode .= $this->getSearchMode();
		$mode .= $this->getOrderMode();
		return $mode;
	}
	
	public function renderSearchForm(){
		list($search_col, $search) = $this->getSearchRequest();
		$renderArray = array(
			'request' => gg(),
			'meta' => $this->listMeta,
			'col' => $this->modelConnector->getColumnNameByBoolean('isReachable'),
			'search_col' => $search_col,
			'search' => $search,
			'label' => $this->label,
		);
		
		return render($renderArray, 'listsearch.tpl', 'list_search');
	}
	
	private function prepareRender(){
		if(empty($this->label)){
			$this->label = $this->modelConnector->getColumnAttribute('label');
		}
	}
	
	private function getSortMode(){
		$mode  = $this->listMeta->mode;
		$mode .= $this->getSearchMode();
		$mode .= '/page/'.$this->listMeta->page;
		return $mode;
	}
	
	private function getSearchMode(){
		list($col, $search) = $this->getSearchRequest();
		if(!empty($search)){
			return '/col/'.$col.'/search/'.$search;
		}
	}
	
	private function getOrderMode(){
		$order = gg('order');
		$order_desc = gg('order_desc');
		if(!empty($order) and in_array($order, $this->column)){
			return '/order/'.$order;
		}elseif(!empty($order_desc) and in_array($order_desc, $this->column)){
			return'/order_desc/'.$order_desc;
		}
	}
	
	private function getSearchRequest(){
		$search = addslashes(str_replace(' ', '', trim((string)gg('search'))));
		$col = gg('col');
		if(!empty($search) and !empty($col) and in_array($col, $this->column)){
			return array($col, $search);
		}
		return array('', '');
	}
}
?>
