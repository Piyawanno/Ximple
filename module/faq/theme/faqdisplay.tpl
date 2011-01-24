<?php if(!defined('XIMPLE_CMS')) die();?>
<div class="faq">
	<b><?=tt('FAQ Category : ')?></b>
	<select id="selected_faq_category" onchange="changeFAQCategory()">
		<?php if(empty($selected_category)) :?>
			<option><?=tt('Please, select category')?></option>
		<?php else :?>
			<option value="0"><?=tt('All categories')?></option>					
		<?php endif?>
		<?php foreach($category as $key => $value) :?>
			<?php if($key == $selected_category) :?>
				<option value="<?=$key?>" selected="selected"><?=$value?></option>
			<?php else :?>
				<option value="<?=$key?>"><?=$value?></option>
			<?php endif?>
		<?php endforeach?>
	</select>

	<?php foreach($faq_data as $key => $value) :?>
		<h3 class="title_label"> Q : <?=$value['question']?> </h3>
		<p> A : <?=$value['answer']?> </p>
	<?php endforeach?>
</div>

<script>
	function changeFAQCategory(){
		window.location.href = sectionURI+'faq/selected_category/'+$("#selected_faq_category").val();
	}
</script>
