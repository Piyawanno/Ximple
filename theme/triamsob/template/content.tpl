<?php if(!defined('XIMPLE_CMS')) die();?>
<div id="content">
	<?php foreach($block['top'] as $key => $item):?>
		<?=$item?>
	<?php endforeach?>
	<?php if(strlen($path)):?>
		<?=triamsob_render_box($path)?>
	<?php endif?>
	<?=$notify?>
	<?=$body?>
	<?php foreach($block['bottom'] as $key => $item):?>
		<?=$item?>
	<?php endforeach?>
</div>

<!-- Middle Blocks -->
<div id="block_middle">
	<?php include('tutorbox.tpl')?>
	<div class="facebook_box">
		<div class="facebook_box_head"></div>
		<div class="facebook_box_body">
			<div class="facebook_box_content">
				<!--<script src="http://connect.facebook.net/en_US/all.js#xfbml=1"></script><fb:like-box href="http://www.facebook.com/triamsob" width="255" show_faces="true" stream="true" header="false"></fb:like-box> -->
			</div>
		</div>
		<div class="facebook_box_foot"></div>
	</div>
	<?php foreach($block['middle'] as $key => $item):?>
		<?=$item?>
	<?php endforeach?>
	<div class="essay">
		<a href="<?=SECTION_URI.Q.'journal/tag/บทความนักเรียน/tag_label/บทความนักเรียน'?>">
			<div id="essay_student_head" border="0"></div>
		</a>
		<div class="essay_body">
		<div class="essay_content">
			<?=execute_string('triamsob_student_article')?>
			<p align="right">
				<a href="<?=SECTION_URI.Q.'journal/tag/บทความนักเรียน/tag_label/บทความนักเรียน'?>"><?=tt('read more')?></a>
			</p>
		</div>
		</div>
		<div class="essay_foot"></div>
	</div>
	<div class="essay">
		<a href="<?=SECTION_URI.Q.'journal/tag/บทความติวเตอร์/tag_label/บทความติวเตอร์'?>">
			<div id="essay_tutor_head" border="0"></div>
		</a>
		<div class="essay_body">
		<div class="essay_content">
			<?=execute_string('triamsob_tutor_article')?>
			<p align="right">
				<a href="<?=SECTION_URI.Q.'journal/tag/บทความติวเตอร์/tag_label/บทความติวเตอร์'?>"><?=tt('read more')?></a>
			</p>
		</div>
		</div>
		<div class="essay_foot"></div>
	</div>
</div>

<!-- Right Blocks -->
<div id="block_right">
	<?php foreach($block['right'] as $key => $item):?>
	<div class="right_box">
		<div class="right_box_head"></div>
		<div class="right_box_body">
			<div class="right_box_content">
				<?=$item?>
			</div>
		</div>
		<div class="right_box_foot"></div>
	</div>
	<?php endforeach?>
</div>
