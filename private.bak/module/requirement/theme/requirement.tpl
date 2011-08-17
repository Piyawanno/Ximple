<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="list_label"><?=$customer_name?></h3>
<p>
	<b><?=tt('customer email')?></b> : <?=$customer_email?>
</p>
<p>
	<b><?=tt('submit on')?></b> : <?=$get_date?>
</p>

<p><b><?=tt('company policy')?></b></p>
<p><?=$policy?></p>
<p><b><?=tt('concept purpose')?></b></p>
<p><?=$purpose?></p>

<?php if(count($tab_menu)):?>
	<p><b><?=tt('tab menu')?></b></p>
	<ul>
	<?php foreach($tab_menu as $key => $value):?>
		<?php if(strlen($value['menu_name']) and strlen($value['menu_description'])):?>
		<li>
			<u><?=$value['menu_name']?></u> : <?=$value['menu_description']?>
		</li>
		<?php endif?>
	<?php endforeach?>
	</ul>
<?php endif?>

<p><b><?=tt('representation')?></b></p>
<p><?=$representation?></p>

<?php if(count($expectation)):?>
	<p><b><?=tt('expected style')?></b></p>
	<ul>
	<?php foreach($expectation as $key => $value):?>
		<li><?=$expectation_option[$value]?></li>
	<?php endforeach?>
	</ul>
<?php endif?>

<?php if(count($file)):?>
	<p><b><?=tt('image files')?></b></p>
	<ul>
	<?php foreach($file as $key => $value):?>
		<?php if(is_file(ROOT_PATH.$value['file'])):?>
		<li>
			<p><?=$value['short_description']?></p>
			<a href="<?=ROOT_URI.$value['file']?>" target="_blank">
				<img src="<?=ROOT_URI.$value['file']?>" style="max-width:420px; display:block;"/>
			</a>
		</li>
		<?php endif?>
	<?php endforeach?>
	</ul>
<?php endif?>

<?php if(count($link)):?>
	<p><b><?=tt('example links')?></b></p>
	<ul>
	<?php foreach($link as $key => $value):?>
		<?php if(strlen($value['url']) and strlen($value['link_description'])):?>
		<li>
			<?=render_raw_link($value['url'])?> : <?=$value['link_description']?>
		</li>
		<?php endif?>
	<?php endforeach?>
	</ul>
<?php endif?>

<p class="operation_bar">
	<?=render_operation_link('requirement_edit', $id, tt('edit'))?>
	<?=render_operation_link('requirement_drop', $id, tt('drop'))?>
</p>
