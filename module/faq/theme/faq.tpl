<?php if(!defined('XIMPLE_CMS')) die();?>
<div class="faq">
	<div id="faq_category_select">
		<strong><?=tt('FAQ Category : ')?></strong>
		<select id="selected_faq_category" onchange="changeFAQCategory(this)">
			<option value="0"><?=tt('Please, select category')?></option>
			<option value="0"><?=tt('All categories')?></option>					
			<?php foreach($category as $key => $value) :?>
				<option value="<?=$key?>"><?=$value?></option>
			<?php endforeach?>
		</select>
	</div>
	<?=$write_icon?>
	<?php foreach($data as $cid => $questions) :?>
	<div class="faq_container" id="faq_<?=$cid?>">
		<h3 class="list_label"><?=$category[$cid]?></h3>
		<?php foreach($questions as $key => $value) :?>
			<h3 class="title_label"> Q : <?=$value['question']?> </h3>
			<p><?=$value['answer']?> </p>
			<p class="faq_foot">
			<?php if($value['editable']):?>
				<a href="<?=SECTION_URI.'faq_edit/'.$key?>"><?=tt('edit')?></a>
			<?php endif?>
			<?php if($value['dropable']):?>
				<a href="<?=SECTION_URI.'faq_drop/'.$key?>"><?=tt('drop')?></a>
			<?php endif?>
			</p>
		<?php endforeach?>
	</div>
	<?php endforeach?>
</div>

<script>
	function changeFAQCategory(category){
		var cid = $(category).val();
		if(cid == 0){
			$('.faq_container').show();
		}else{
			$('.faq_container').hide();
			$('#faq_'+cid).show();
		}
	}
</script>
