<?php if(!defined('XIMPLE_CMS')) die();?>
<div class="hitdict">
	<h3 class='form_label'><?=$data['id']?></h3>
	<h3><?=$data['headword']?></h3>
	<h3><?=$data['language']['label']?></h3>
	<h3><?=$data['pronunciation_th']?></h3>
	<h3><?=$data['pronunciation_pi']?></h3>
	<h3><?=$data['pronunciation_ipa']?></h3>
	<h3><?=$data['synonym']?></h3>
	<h3><?=$data['last_update_time']?></h3>
	<h3><?=$data['last_update_by']?></h3>
	<h3><?=$data['section']?></h3>
	<h3><?=$data['id']?></h3>
	<?php foreach($data['picture'] as $id => $item):?>
	<?php if($itme['picture']):?>
		<div>
		</div>
	<?php else :?>
		<div style='width:80px;height:60px;border:1'>  
			no image
		</div>
	<?php endif?>
		<h3><?=$item['description']?></h3>
		<h3><?=$item['hid']?></h3>
	<?php endforeach?>
	<?=ROOT_PATH?>
	<?=ROOT_URI?>
	<?=SECTION_PATH?>
	<?=SECTION_URI?>
</div>
