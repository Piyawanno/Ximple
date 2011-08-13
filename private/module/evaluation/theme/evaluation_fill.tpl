<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="list_label"><?=tt('Fill Evaluation-Form')?></h3>
<ul>
<?php foreach($data as $key => $value):?>
	<li>
		<h4><a href=<?=SECTION_URI.Q.'evaluation_fill/model/'.$key?>><?=$value['name']?></a></h4>
		<p>
			<?=$value['description']?>
		</p>
	</li>
<?php endforeach?>
</ul>
