<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="list_label"><?=tt('Custom CSS')?></h3>
<p><?=tt('You can select and edit CSS file from the followed list to customize your theme.')?></p>
<?php if(count($HTML4)):?>
	<h4 class="title_label"><?=tt('HTML4')?></h4>
	<ul>
		<?php foreach($HTML4 as $value):?>
			<li style="line-height:35px;">
				<a href="<?=SECTION_URI.Q?>theme_edit_css/theme_mode/HTML4/file/<?=$value?>"><?=$value?></a>
			</li>
		<?php endforeach?>
	</ul>
<?php endif?>

<?php if(count($HTML5)):?>
	<h4 class="title_label"><?=tt('HTML5')?></h4>
	<ul>
		<?php foreach($HTML5 as $value):?>
			<li style="line-height:35px;">
				<a href="<?=SECTION_URI.Q?>theme_edit_css/file/<?=$value?>"><?=$value?></a>
			</li>
		<?php endforeach?>
	</ul>
<?php endif?>

<?php if(count($MOBILE)):?>
	<h4 class="title_label"><?=tt('Mobile')?></h4>
	<ul>
		<?php foreach($MOBILE as $value):?>
			<li style="line-height:35px;">
				<a href="<?=SECTION_URI.Q?>theme_edit_css/file/<?=$value?>"><?=$value?></a>
			</li>
		<?php endforeach?>
	</ul>
<?php endif?>
