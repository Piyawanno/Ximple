<?php if(!defined('XIMPLE_CMS')) die();?>
<?php foreach($users as $uid => $user):?>
	<div class="main_box">
		<div class="main_box_head"></div>
		<div class="main_box_body">
			<div class="main_box_content">
				<div class="tutor_visual">
					<img src="<?=ROOT_URI.$user['avatar']?>" class="tutor_avatar"/>
					<img src="<?=ROOT_URI.'module/triamsob/theme/ribbonconfirm.png'?>" class="tutor_ribbon"/>
				</div>
				<div class="tutor_profile">
					<h3 class="title_label"><a href="<?=SECTION_URI.Q.'triamsob_tutor_profile/'.$uid.'/'.$user['login_name']?>"><?=$user['login_name']?></a></h3>
					<p>
						<label><?=tt('subject')?></label>
						<?php foreach($user['subject'] as $key => $sid):?>
							<a href="<?=SECTION_URI.Q.'triamsob_tutor_subject/'.$sid.'/'.$subject[$sid]?>" class="tutor_subject"><?=$subject[$sid]?></a>
						<?php endforeach?>
					</p>
					<?php if(isset($user['profile'])):?>
						<?=triamsob_render_profile_item($user['profile'], TRIAMSOB_PLACE_TYPE, tt('place'))?>
						<?=triamsob_render_profile_item($user['profile'], TRIAMSOB_PHONE_TYPE, tt('phone'))?>
					<?php endif?>
					<p align="right"><strong><a href="<?=SECTION_URI.Q.'triamsob_tutor_profile/'.$uid.'/'.$user['login_name']?>"><?=tt('see more')?></a></strong></p>
				</div>
				<div style="clear:both;"></div>
			</div>
		</div>
		<div class="main_box_foot"></div>
	</div>
<?php endforeach?>
