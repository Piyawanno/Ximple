<?php
require_once('hitpedia.tool.inc');
require_once('HitPediaPictureModel.class.inc');
require_once('HitPediaVariantModel.class.inc');
class HitPediaModel extends Model{
	function HitPediaModel(){
		$this->headword = $this->title(tt('headword'));
		$this->headword->listMode = 'hitpedia';
		$this->language = $this->select(tt('language'), hitpedia_get_language_pair_option());
		$this->pronunciation_th = $this->char(tt('Thai pronunciation'));
		$this->pronunciation_pi = $this->char(tt('Pin-in Pronunciation'));
		$this->pronunciation_ipa = $this->char(tt('IPA Pronunciation'));
		
		$this->variant = $this->grid(tt('variant'));
		$this->variant->setModel(new HitPediaVariantModel());
		
		$this->picture = $this->grid(tt('pictures'));
		$this->picture->setModel(new HitPediaPictureModel());
		
		$this->last_update_time = $this->now();
		$this->last_update_time->isUpdateTime = true;
		$this->last_update_by = $this->hidden(USER_ID, 'int');
		$this->section = $this->section();
	}
}
?>
