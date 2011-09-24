<?php if(!defined('XIMPLE_CMS')) die();?>
<?php foreach($data as $id => $item) :?>
<div class="faq">	
	<h3 class="title_label"><?=$item['question']?></h3>
	<p><?=$item['answer']?></p>
	<p><b><?=tt('category')?> : </b><?=$item['category']['category']?></p>
	<p><b><?=tt('by')?> : </b><?=$item['owner']['login_name']?></p>
</div>
<?php endforeach?>
