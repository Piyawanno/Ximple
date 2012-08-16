<?php
 require_once('hitdict.tool.inc');
 class HitDictTranslateModel extends Model{
	function HitDictTranslateModel(){
		$this->headword = $this->select(tt('headword'), hitdict_get_headword_option());
		$this->type_of_word = $this->select(tt('part of speech'), hitdict_get_part_pair_option());
		
		$help = tt('Optional field, which can be used to map one word in headword language to one word in translated language.');
		$this->one_to_one_translation = $this->char(tt('one-to-obe translate'), $help);
		
		$this->extended_translation = $this->shortText(tt('extended transLation'));
		$this->example = $this->shortText(tt('example'));
	}
}
?>
