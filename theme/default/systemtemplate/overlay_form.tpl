<?php if(!defined('XIMPLE_CMS')) die();?>
<div id="overlay_<?=$form_id.'_'.$module_name?>_dialog" style="display:none;">
	<div style="text-align:center;padding:50px;">
		<img src="<?=ROOT_URI?>files/icon/loader.gif"/>
	</div>
</div>
<p><label style="font-weight:bold;"><?=$label?></label></p>
<p class="form_help"><?=$help?></p>
<div id="overlay_<?=$form_id.'_'.$module_name?>_table"></div>
<p>
	<a href="#" onclick="">
		<img src="<?=ROOT_URI?>files/icon/add.png"/><?=tt('add new row')?>
	</a>
</p>
<script>
	overlayRefresh('<?=$form_id?>', '<?=$module_name?>');
</script>
