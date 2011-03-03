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
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/0/คณิต ประถม'?>" class="tutor_subject"><img alt="คณิต ประถม" src="<?=ROOT_URI.'theme/triamsob/image/canmat1.png'?>" border="0"/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/1/คณิต ม.ต้น'?>" class="tutor_subject"><img alt="คณิต ม.ต้น" src="<?=ROOT_URI.'theme/triamsob/image/canmat2.png'?>" border="0"/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/2/คณิต ม.ปลาย'?>" class="tutor_subject"><img alt="คณิต ม.ปลาย" src="<?=ROOT_URI.'theme/triamsob/image/canmat3.png'?>" border="0"/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/3/อังกฤษ ประถม'?>" class="tutor_subject"><img alt="อังกฤษ ประถม" src="<?=ROOT_URI.'theme/triamsob/image/caneng1.png'?>" border="0"/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/4/อังกฤษ ม.ต้น'?>" class="tutor_subject"><img alt="อังกฤษ ม.ต้น" src="<?=ROOT_URI.'theme/triamsob/image/caneng2.png'?>" border="0"/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/5/อังกฤษ ม.ปลาย'?>" class="tutor_subject"><img alt="อังกฤษ ม.ปลาย" src="<?=ROOT_URI.'theme/triamsob/image/caneng3.png'?>" border="0"/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/6/ฟิสิกส์'?>" class="tutor_subject"><img alt="ฟิสิกส์" src="<?=ROOT_URI.'theme/triamsob/image/canphy.png'?>" border="0"/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/7/เคมี'?>" class="tutor_subject"><img alt="เคมี" src="<?=ROOT_URI.'theme/triamsob/image/canchem.png'?>" border="0"/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/8/ชีวะ'?>" class="tutor_subject"><img alt="ชีวะ" src="<?=ROOT_URI.'theme/triamsob/image/canbio.png'?>" border="0"/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/9/วิทยาศาสตร์ ประถม'?>" class="tutor_subject"><img alt="วิทยาศาสตร์ ประถม" src="<?=ROOT_URI.'theme/triamsob/image/cansci1.png'?>" border="0"/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/10/วิทยาศาสตร์ ม.ต้น'?>" class="tutor_subject"><img alt="วิทยาศาสตร์ ม.ต้น" src="<?=ROOT_URI.'theme/triamsob/image/cansci2.png'?>" border="0"/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/11/วิทยาศาสตร์ ม.ปลาย'?>" class="tutor_subject"><img alt="วิทยาศาสตร์ ม.ปลาย" src="<?=ROOT_URI.'theme/triamsob/image/cansci3.png'?>" border="0"/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/12/ไทย'?>" class="tutor_subject"><img alt="ไทย" src="<?=ROOT_URI.'theme/triamsob/image/cantha.png'?>" border="0"/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/13/สังคม'?>" class="tutor_subject"><img alt="สังคม" src="<?=ROOT_URI.'theme/triamsob/image/canso.png'?>" border="0"/></a>
		<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/14/อื่นๆ'?>" class="tutor_subject"><img alt="อื่นๆ" src="<?=ROOT_URI.'theme/triamsob/image/canother.png'?>" border="0"/></a>
	</div>
</div>
<div class="facebook_box_foot"></div>
