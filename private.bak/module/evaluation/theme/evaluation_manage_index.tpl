<?php if(!defined('XIMPLE_CMS')) die();?>
<p>
	<?=tt('You can manage the Evaluations using the followed links. ')?>
	<?=tt('There, you can group a Evaluatee to many Evaluators. ')?>
	<?=tt('Moreover, you can edit and delete existent grouping.')?>
</p>
<ul>
<?php foreach($data as $key => $value):?>
	<li><a href=<?=SECTION_URI.Q.'evaluation_manage/model/'.$key?>><?=$value['name']?></a></li>
<?php endforeach?>
</ul>
