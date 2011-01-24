<?php if(!defined('XIMPLE_CMS')) die();?>
<div class="translate_block">
	<?php foreach($language as $key => $value):?>
		<a href="<?=SECTION_URI.Q.'translate_set_language/language/'.$key?>"><?=$value?></a>
	<?php endforeach?>
</div>
