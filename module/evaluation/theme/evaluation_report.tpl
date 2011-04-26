<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="list_label"><?=tt('Evaluation Report')?></h3>
<ul>
<?php foreach($data as $key => $value):?>
	<li>
		<h4><a href=<?=SECTION_URI.Q.'evaluation/model/'.$key?>><?=$value['name']?></a></h4>
		<p>
			<?=$value['description']?>
		</p>
	</li>
<?php endforeach?>
</ul>
