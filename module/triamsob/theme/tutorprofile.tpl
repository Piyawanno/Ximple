<?php if(!defined('XIMPLE_CMS')) die();?>
<div class="main_box">
	<div class="main_box_head"></div>
	<div class="main_box_body">
		<div class="main_box_content">
			<div class="tutor_visual">
				<img src="<?=ROOT_URI.$avatar?>" class="tutor_avatar"/>
				<img src="<?=ROOT_URI.'module/triamsob/theme/ribbonconfirm.png'?>" class="tutor_ribbon"/>
				<a href="<?=SECTION_URI.Q.'message_write/send_to/'.$login_name?>" class="tutor_button"><?=tt('send message')?></a>
				<a href="<?=SECTION_URI.Q.'profile_write_mail/send_to/'.$login_name?>" class="tutor_button"><?=tt('send email')?></a>
			</div>
			<div class="tutor_profile">
				<h3 class="title_label"><?=$login_name?></h3>
				<?php if(isset($profile[TRIAMSOB_FACEBOOK_TYPE])):?>
					<a href="<?=$profile[TRIAMSOB_FACEBOOK_TYPE]?>"><img src="<?=ROOT_URI?>theme/triamsob/image/bottoncanfb.png" align="right" border="0"></a>
				<?php endif?>
				<p>
					<label><?=tt('subject')?></label>
					<?php foreach($subject as $key => $sid):?>
						<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/'.$sid.'/'.$subject_list[$sid]?>" class="tutor_subject"><?=$subject_list[$sid]?></a>
					<?php endforeach?>
				</p>
				<?=triamsob_render_profile_item($profile, TRIAMSOB_PLACE_TYPE, tt('place'))?>
				<?=triamsob_render_profile_item($profile, TRIAMSOB_PHONE_TYPE, tt('phone'))?>
				<?=triamsob_render_profile_descriptive_item($profile, TRIAMSOB_DEGREE_TYPE, tt('degree'))?>
				<?=triamsob_render_profile_descriptive_item($profile, TRIAMSOB_EXPERIENCE_TYPE, tt('experience'))?>
				<?=triamsob_render_profile_descriptive_item($profile, TRIAMSOB_ETC_TYPE, tt('etc.'))?>
			</div>
			<div style="clear:both;"></div>
		</div>
	</div>
	<div class="main_box_foot"></div>
</div>
