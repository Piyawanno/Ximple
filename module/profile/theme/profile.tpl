<?php if(!defined('XIMPLE_CMS')) die();?>
<div class="profile">
	<h3 class="list_label"><?=sprintf(tt('Profile of %s'), $user['login_name'])?></h3>
	<p align="center"><img src="<?=ROOT_URI?><?=$user['avatar']?>" alt="userlogo"></img></p>
	<?php if($allow_email):?>
		<p><?=render_icon('profile_write_mail/'.$user['id'].'/send_to/'.$user['login_name'], 'files/icon/email.png', sprintf(tt('Send an email to %s'), $user['login_name']));?></p>
	<?php endif?>
	<?php if(!authority_is_guest()):?>
		<p><?=render_icon('message_write/send_to/'.$user['login_name'], 'files/icon/message.png', sprintf(tt('Send a message to %s'), $user['login_name']));?></p>
		<p><?=render_icon('tracker/'.$user['id'], 'files/icon/tracker.png', sprintf(tt('See tracker of  %s'), $user['login_name']));?></p>
	<?php endif?>
	<?=render_write_icon('profile_write', tt('Add new User-Profile'))?>
	<?php if($readable):?>
		<?php foreach($data as $key => $value):?>
			<h4><?=$key?></h4>
			<table width="100%"><tbody>
			<?php foreach($value as $index => $profile):?>
			<tr>
				<td><?=$profile?></td>
				<?php if($editable):?>
				<td width="10%">
					<a href="<?=SECTION_URI.Q?>profile_edit/<?=$uid?>" ><img alt="edit" src="<?=ROOT_URI?>files/icon/edit.png" border="0"/></a>
				</td>
				<td width="10%">
					<a href="<?=SECTION_URI.Q?>profile_drop/<?=$uid?>"><img alt="delete" src="<?=ROOT_URI?>files/icon/stop.png" border="0"/></a>
				</td>
				<?php endif?>
			</tr>
			<?php endforeach?>
			</tbody></table>
		<?php endforeach?>
	<?php endif?>
</div>
