<?php if(!defined('XIMPLE_CMS')) die();?>
<div class="form">
	<?php if($meta->isAjax):?>
		<form enctype="multipart/form-data" method="post" action="<?=SECTION_URI.Q.$meta->mode?>" name="ximpleform" onsubmit="return <?=$meta->ajaxFunction?>(this, notNull<?=$meta->id?>, label<?=$meta->id?>)" id="<?=$meta->id?>">
	<?php else:?>
		<form enctype="multipart/form-data" method="post" action="<?=SECTION_URI.Q.$meta->mode?>" name="ximpleform" onsubmit="return checkForm(notNull<?=$meta->id?>, label<?=$meta->id?>)" id="<?=$meta->id?>">
	<?php endif?>
	<?=$rendered_form?>
	<!--{additional_form}-->
	<?php if(count($not_null)):?>
		<p>
			<span style="color:red;font-weight:bold;">*</span>
			<?=tt('required fields')?>
		</p>
	<?php endif?>
	<input type="submit" value="<?=$meta->submitLabel?>" style="display:block;margin-top:15px;"/>
	</form>
</div>

<?php if(!$meta->isAjax):?>
	<select style="display:none;position:absolute;" id="complete_option" multiple="multiple" size="5">
	</select>
	<div id="cle_image_loader" style="display:none;"></div>
	<?php if(isset($is_translate) and is_array(cc('supported_language'))):?>
		<div id="translate_dialog" style="display:none;text-align:left;" class="form">
			<p><label><?=tt('Select language')?></label></p>
			<select onchange="selectTranslateLanguage(this)">
				<option><?=tt('Please, select language')?></option>
				<?php foreach(cc('supported_language') as $key => $value):?>
					<option value="<?=$key?>"><?=$value?></option>
				<?php endforeach?>
			</select>
		</div>
	<?php endif?>
<?php else:?>
	<?=head_define_js_var();?>
	<?=head_define_js_array();?>
	<script>
		$(document).trigger("ready");
	</script>
<?php endif?>
