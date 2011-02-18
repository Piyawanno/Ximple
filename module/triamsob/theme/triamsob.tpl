<?php if(!defined('XIMPLE_CMS')) die();?>
<div>
	<h3 class="title_label"><?=tt('Admission')?></h3>
	<ul>
	<?php foreach($admission as $key => $value):?>
		<li><a href="<?=render_uri('blog', $value)?>"><?=$value['topic']?></a></li>
	<?php endforeach?>
	</ul>
	<div class="triamsob_read_more">
		<?=triamsob_render_category_link($category[TRIAMSOB_ADMISSION_CATEGORY], TRIAMSOB_ADMISSION_CATEGORY,'blog')?>
	</div>
</div>

<div>
	<h3 class="title_label"><?=tt('Exercise')?></h3>
	<ul>
	<?php foreach($exercise as $key => $value):?>
		<li><a href="<?=SECTION_URI.Q.'download/'.$key?>"><?=$value?></a></li>
	<?php endforeach?>
	</ul>
	<div class="triamsob_read_more">
		<?=triamsob_render_category_link($category[TRIAMSOB_EXERCISE_CATEGORY], TRIAMSOB_EXERCISE_CATEGORY, 'download')?>
	</div>
</div>

<div>
	<h3 class="title_label"><?=tt('Old Exam')?></h3>
	<ul>
	<?php foreach($old_exam as $key => $value):?>
		<li><a href="<?=SECTION_URI.Q.'download/'.$key?>"><?=$value?></a></li>
	<?php endforeach?>
	</ul>
	<div class="triamsob_read_more">
		<?=triamsob_render_category_link($category[TRIAMSOB_EXAM_CATEGORY], TRIAMSOB_EXAM_CATEGORY, 'download')?>
	</div>
</div>

<div>
	<h3 class="title_label"><?=tt('Scholar')?></h3>
	<ul>
	<?php foreach($scholar as $key => $value):?>
		<li><a href="<?=render_uri('blog', $value)?>"><?=$value['topic']?></a></li>
	<?php endforeach?>
	</ul>
	<div class="triamsob_read_more">
		<?=triamsob_render_category_link($category[TRIAMSOB_SCHOLAR_CATEGORY], TRIAMSOB_SCHOLAR_CATEGORY,'blog')?>
	</div>
</div>

<div>
	<h3 class="title_label"><?=tt('Forum')?></h3>
	<ul>
	<?php foreach($forum as $key => $value):?>
		<li><a href="<?=SECTION_URI.Q.'forum_entry/'.$key?>"><?=$value?></a></li>
	<?php endforeach?>
	</ul>
	<div class="triamsob_read_more">
		<a href="<?=SECTION_URI.Q.'forum'?>"><?=tt('read more')?></a>
	</div>
</div>
