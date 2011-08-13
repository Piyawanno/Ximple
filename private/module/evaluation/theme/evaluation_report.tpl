<?php if(!defined('XIMPLE_CMS')) die();?>
<p>
	<?=tt('You can see report of the followed evaluations.')?>
</p>
<ul>
<?php foreach($data as $key => $value):?>
	<li>
		<a href=<?=SECTION_URI.Q.'evaluation/model/'.$key?>><?=$value['name']?></a>
	</li>
<?php endforeach?>
</ul>
