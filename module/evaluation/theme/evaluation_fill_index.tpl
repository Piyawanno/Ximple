<?php if(!defined('XIMPLE_CMS')) die();?>
<p>
	<?=tt('You should evaluate the followed persons.')?>
</p>
<?php foreach($evaluation as $model_ref => $data):?>
	<ul>
		<li>
			<?=$model[$model_ref]?>
			<ul>
			<?php foreach($data as $key => $value):?>
				<li><a href="<?=SECTION_URI.Q.'evaluation_fill/'.$key?>"><?=$value['evaluatee']['label']?></a></li>
			<?php endforeach?>
			</ul>
		</li>
	<ul>
<?php endforeach?>
