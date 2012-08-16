<?php if(!defined('XIMPLE_CMS')) die();?>
<div class='hitpedia'>
	<?=$data['headword']?> <br />
	<?=$data['language']['label']?> <br />
	<?=$data['pronunciation_th']?> <br />
	<?=$data['pronunciation_pi']?> <br /> 
	<?=$data['pronunciation_ipa']?> <br /> 
	<?=$data['last_update_time']?> <br /> 
	<?php foreach ($data['variant'] as $id => $key): ?>
		<?=$key['variant']?> <br />
	<?php endforeach ?>
	<?php foreach ($data['picture'] as $id => $key): ?>
	    <?php if($key['picture']):?>
		<img src='<?=ROOT_URI.$key["picture"]?>'> <br/>
		<?php endif ?>
		<?=$key['description']?>
	<?php endforeach ?>
	
	
	
</div>
