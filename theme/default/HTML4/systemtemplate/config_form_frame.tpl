<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 onclick="hideSub('sub_config_<?=$id?>')" class="config_head"><?=$title?></h3>
<?php if($show):?>
	<div class="subform" id="sub_config_<?=$id?>" rel="show">
<?else:?>
	<div class="subform" id="sub_config_<?=$id?>" rel="hide" style="display:none;">
<?endif?>
	<?=$rendered_form?>
</div>
