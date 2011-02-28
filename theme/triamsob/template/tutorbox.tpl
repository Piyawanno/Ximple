<?php if(!defined('XIMPLE_CMS')) die();?>
<div id="tutor_box">
	<div id="tutor_box_content">
		<h3><?=tt('search tutor')?></h3>
		<form action="<?=SECTION_URI.Q?>triamsob_tutor_search_result" method="post" id="tutor_search">
			<div>
				<div class="tutor_box_label"><?=tt('subject')?></div>
				<?php include_once(ROOT_PATH.'module/triamsob/triamsob.tool.inc')?>
				<select name="subject">
				<?php foreach(triamsob_get_tutor_subjects() as $key => $value):?>
					<option value="<?=$key?>"><?=$value?></option>
				<?php endforeach?>
				</select>
			</div>
			<div>
				<div class="tutor_box_label"><?=tt('place')?></div>
				<input name="place" />
			</div>
			<div>
				<div class="tutor_box_label"><?=tt('etc.')?></div>
				<input name="etc" />
			</div>
		</form>
		<p class="tutor_box_button"><a href="#" onclick="return submitForm();"><?=tt('search')?></a></p>
		<p class="tutor_box_button"><a href="<?=SECTION_URI.Q?>triamsob_tutor_registration"><?=tt('registration')?></a></p>
	</div>
</div>

<script>
	function submitForm(){
		$('#tutor_search').submit();
		return false;
	}
</script>

<div class="facebook_box_head"></div>
<div class="facebook_box_body">
	<div class="facebook_box_content">
		<h3 class="title_label"><?=tt('Tutor in the Can')?></h3>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/0'?>" class="tutor_subject"><img src="<?=ROOT_URI.'theme/triamsob/image/canmat1.png'?>" border="" alt=""/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/1'?>" class="tutor_subject"><img src="<?=ROOT_URI.'theme/triamsob/image/canmat2.png'?>" border="" alt=""/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/2'?>" class="tutor_subject"><img src="<?=ROOT_URI.'theme/triamsob/image/canmat3.png'?>" border="" alt=""/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/3'?>" class="tutor_subject"><img src="<?=ROOT_URI.'theme/triamsob/image/caneng1.png'?>" border="" alt=""/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/4'?>" class="tutor_subject"><img src="<?=ROOT_URI.'theme/triamsob/image/caneng2.png'?>" border="" alt=""/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/5'?>" class="tutor_subject"><img src="<?=ROOT_URI.'theme/triamsob/image/caneng3.png'?>" border="" alt=""/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/6'?>" class="tutor_subject"><img src="<?=ROOT_URI.'theme/triamsob/image/canphy.png'?>" border="" alt=""/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/7'?>" class="tutor_subject"><img src="<?=ROOT_URI.'theme/triamsob/image/canchem.png'?>" border="" alt=""/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/8'?>" class="tutor_subject"><img src="<?=ROOT_URI.'theme/triamsob/image/canbio.png'?>" border="" alt=""/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/9'?>" class="tutor_subject"><img src="<?=ROOT_URI.'theme/triamsob/image/cansci1.png'?>" border="" alt=""/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/10'?>" class="tutor_subject"><img src="<?=ROOT_URI.'theme/triamsob/image/cansci2.png'?>" border="" alt=""/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/11'?>" class="tutor_subject"><img src="<?=ROOT_URI.'theme/triamsob/image/cansci3.png'?>" border="" alt=""/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/12'?>" class="tutor_subject"><img src="<?=ROOT_URI.'theme/triamsob/image/cantha.png'?>" border="" alt=""/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/13'?>" class="tutor_subject"><img src="<?=ROOT_URI.'theme/triamsob/image/canso.png'?>" border="" alt=""/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/14'?>" class="tutor_subject"><img src="<?=ROOT_URI.'theme/triamsob/image/canother.png'?>" border="" alt=""/></a>
	</div>
</div>
<div class="facebook_box_foot"></div>
