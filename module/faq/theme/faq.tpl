<?php if(!defined('XIMPLE_CMS')) die();?>
<div class="faq">
	<strong><?=tt('FAQ Category : ')?></strong>
	<select id="selected_faq_category" onchange="changeFAQCategory(this)">
		<option value="0"><?=tt('Please, select category')?></option>
		<option value="0"><?=tt('All categories')?></option>					
		<?php foreach($category as $key => $value) :?>
			<option value="<?=$key?>"><?=$value['category']?></option>
		<?php endforeach?>
	</select>
	
	<?php foreach($data as $cid => $questions) :?>
	<div class="faq_container" id="faq_<?=$cid?>">
		<h3 class="list_label"><?=$category[$cid]['category']?></h3>
		<p>
			<?=$category[$cid]['description']?>
		</p>
		<?php foreach($questions as $key => $value) :?>
			<h3 class="title_label"> Q : <?=$value['question']?> </h3>
			<p><strong>Answer : </strong><?=$value['answer']?> </p>
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
