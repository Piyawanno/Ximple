<?php if(!defined('XIMPLE_CMS')) die();?>
<div class="wrest">
	<h3 class="list_label"><?=$label?></h3>
	<?php foreach($data as $key => $value):?>
		<h4 class="small_label"><a href="<?=SECTION_URI.Q.$mode.'/'.$key?>" class="label_link"><?=$value['topic']?></a></h4>
		<?php if(strlen($value['icon'])):?>
			<img src="<?=ROOT_URI.$value['icon']?>" align="left" class="wrest_icon" alt="Icon" />
		<?php endif?>
		<p><?=$value['summary']?></p>
		<div style="clear:both;margin-bottom:20px;"></div>
	<?php endforeach?>
</div>
