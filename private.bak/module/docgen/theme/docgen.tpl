<?php if(!defined('XIMPLE_CMS')) die();?>
<div class="docgen">
	<h3 class="title_label"><?=$topic?></h3>
	<p>
		<label><?=tt('place')?> : </label>
		<?=$place?>
	</p>
	<p>
		<label><?=tt('document ID')?> : </label>
		<?=$document_id?>
	</p>
	<p>
		<label><?=tt('write date')?> : </label>
		<?=$write_date?>
	</p>
	<p>
		<label><?=tt('topic')?> : </label>
		<?=$topic?>
	</p>
	<p>
		<label><?=$prefix?> : </label>
		<?=$receiver?>
	</p>
	<p>
		<?=$content?>
	</p>
	<p>
		<label><?=tt('signed by')?> : </label>
		<?=$writer_position?> (<?=$writer_rank?>)
	</p>
	<p class="docgen_info">
		<?=$write_date?>
		<?=tt('created by')?>
		<?=render_profile_link($contributor)?>
	</p>
	<p class="docgen_operation">
		<a href="<?=SECTION_URI.Q.'docgen_generate_pdf/'.$id?>"><?=tt('generate pdf')?></a>
		<?php if($editable):?>
			<a href="<?=SECTION_URI.Q.'docgen_edit/'.$id?>"><?=tt('edit')?></a>
			<a href="<?=SECTION_URI.Q.'docgen_drop/'.$id?>"><?=tt('drop')?></a>
		<?php endif?>
	</p>
	<?php if(strlen(gg('open_pdf'))):?>
		<script>
			window.open('<?=SECTION_URI.Q.'docgen_generate_pdf/'.$id?>', 'Generated Document', 'menubar=no,width=430,height=360,toolbar=no');
		</script>
	<?php endif?>
</div>
