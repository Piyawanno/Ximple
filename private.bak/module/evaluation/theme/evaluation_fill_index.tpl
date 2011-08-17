<?php if(!defined('XIMPLE_CMS')) die();?>
<p>
	<?=tt('Please, evaluate the followed persons.')?>
</p>
<?php foreach($evaluation as $model_ref => $data):?>
	<ul>
		<li><?=$model[$model_ref]?></li>
		<ul>
		<?php foreach($data as $key => $value):?>
			<li><a href="<?=SECTION_URI.Q.'evaluation_fill/'.$key.'/model/'.$model_ref?>"><?=$value['evaluatee']['label']?></a></li>
		<?php endforeach?>
		</ul>
	</ul>
<?php endforeach?>
