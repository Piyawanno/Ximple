<?php if(!defined('XIMPLE_CMS')) die();?>
<div class="main_box">
	<div class="main_box_head"></div>
	<div class="main_box_body">
		<div id="addmission_content">
			<h3 class="title_label" style="display:none;"><?=tt('Admission')?></h3>
			<?php foreach($admission as $key => $value):?>
			<?php if(strlen($value['icon'])):?>
				<img src="<?=ROOT_URI.$value['icon']?>" class="triamsob_icon" />
			<?php endif?>
			<div class="triamsob_item">
				<h4><a href="<?=render_uri('blog', $value)?>"><?=$value['topic']?></a></h4>
				<?=triamsob_wrap_paragraph($value['intro'])?></a>
			</div>
			<div style="clear:both;"></div>
			<?php endforeach?>
			</ul>
		</div>
		<div class="main_box_read_more">
			<?=triamsob_render_category_link($category[TRIAMSOB_ADMISSION_CATEGORY], TRIAMSOB_ADMISSION_CATEGORY,'blog')?>
		</div>
	</div>
	<div class="main_box_foot"></div>
</div>

<div class="main_box">
	<div class="main_box_head"></div>
	<div class="main_box_body">
		<div id="exercise_content">
			<h3 class="title_label" style="display:none;"><?=tt('Exercise')?></h3>
			<?php foreach($exercise as $key => $value):?>
			<?php if(strlen($value['icon'])):?>
				<img src="<?=ROOT_URI.$value['icon']?>" class="triamsob_icon" />
			<?php endif?>
			<div class="triamsob_item">
				<h4><a href="<?=SECTION_URI.Q.'download/'.$key?>"><?=$value['name']?></a></h4>
				<?=triamsob_wrap_paragraph($value['description'])?>
			</div>
			<div style="clear:both;"></div>
			<?php endforeach?>
		</div>
		<div class="main_box_read_more">
			<?=triamsob_render_category_link($category[TRIAMSOB_EXERCISE_CATEGORY], TRIAMSOB_EXERCISE_CATEGORY, 'download')?>
		</div>
	</div>
	<div class="main_box_foot"></div>
</div>

<div>
	<div class="main_box_head"></div>
	<div class="main_box_body">
		<div id="exam_content">
			<h3 class="title_label" style="display:none;"><?=tt('Old Exam')?></h3>
			<?php foreach($old_exam as $key => $value):?>
			<?php if(strlen($value['icon'])):?>
				<img src="<?=ROOT_URI.$value['icon']?>" class="triamsob_icon" />
			<?php endif?>
			<div class="triamsob_item">
				<h4><a href="<?=SECTION_URI.Q.'download/'.$key?>"><?=$value['name']?></a></h4>
				<?=triamsob_wrap_paragraph($value['description'])?>
			</div>
			<div style="clear:both;"></div>
			<?php endforeach?>
		</div>
		<div class="main_box_read_more">
			<?=triamsob_render_category_link($category[TRIAMSOB_EXAM_CATEGORY], TRIAMSOB_EXAM_CATEGORY, 'download')?>
		</div>
	</div>
	<div class="main_box_foot"></div>
</div>

<div>
	<div class="main_box_head"></div>
	<div class="main_box_body">
		<div id="scholar_content">
			<h3 class="title_label" style="display:none;"><?=tt('Scholar')?></h3>
			<?php foreach($scholar as $key => $value):?>
			<?php if(strlen($value['icon'])):?>
				<img src="<?=ROOT_URI.$value['icon']?>" class="triamsob_icon" />
			<?php endif?>
			<div class="triamsob_item">
				<h4><a href="<?=render_uri('blog', $value)?>"><?=$value['topic']?></a></h4>
				<?=triamsob_wrap_paragraph($value['intro'])?></a>
			</div>
			<div style="clear:both;"></div>
			<?php endforeach?>
		</div>
		<div class="main_box_read_more">
			<?=triamsob_render_category_link($category[TRIAMSOB_SCHOLAR_CATEGORY], TRIAMSOB_SCHOLAR_CATEGORY,'blog')?>
		</div>
	</div>
	<div class="main_box_foot"></div>
</div>

<div>
	<div class="main_box_head"></div>
	<div class="main_box_body">
		<div id="forum_content">
			<h3 class="title_label" style="display:none;"><?=tt('Last Forum')?></h3>
			<ul>
			<?php foreach($forum as $key => $value):?>
				<li><a href="<?=SECTION_URI.Q.'forum_entry/'.$key?>"><?=$value?></a></li>
			<?php endforeach?>
			</ul>
		</div>
		<div class="main_box_read_more">
			<a href="<?=SECTION_URI.Q.'forum'?>"><?=tt('read more')?></a>
		</div>
	</div>
	<div class="main_box_foot"></div>
</div>
