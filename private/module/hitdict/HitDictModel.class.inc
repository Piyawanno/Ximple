<?php
require_once('hitdict.tool.inc');
require_once('HeadwordColumn.class.inc');
require_once('HitDictPictureModel.class.inc');
require_once('HitDictTranslateModel.class.inc');
require_once('HitDictVariantModel.class.inc');


class HitDictModel extends Model{
	function HitDictModel(){
		$this->headword =  $this->title(tt('headword'));
		$this->language =  $this->select(tt('language'), hitdict_get_language_pair_option());
		$this->pronunciation_th  =  $this->char(tt('Thai pronunciation'));
		$this->pronunciation_pi  =  $this->char(tt('Pin-In pronunciation'));
		$this->pronunciation_ipa =  $this->char(tt('IPA pronunciation'));
		
		
		$this->variant = $this->grid(tt('variant form'));
		$this->variant->setModel(new HitDictVariantModel());
		
		$this->picture = $this->grid(tt('pictures'));
		$this->picture->setModel(new HitDictPictureModel());
		
		$this->translate = $this->overlayGrid(tt('translated meaning'), new HitDictTranslateModel());
		#$this->synonym = new HeadwordColumn(tt('synonym'));
		
		$this->last_update_time = $this->now();
		$this->last_update_time->isUpdateTime = true;
		$this->last_update_by = $this->hidden(USER_ID, 'int');
		
		$this->section = $this->section();
	}
}
?>
