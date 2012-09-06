<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="list_label"><?=tt('My Message')?></h3>
<?=render_write_icon('message_write', ('Send a Message'))?>
<table class="message">
<?php foreach($data as $key => $value):?>
	<tr>
		<td class="sender" align="center" valign="top">
			<?=render_avatar($value['sender'])?>
		</td>
		<td class="space"></td>
		<td class="message_container" valign="top">
			<?php if($value['status'] == 'new'):?>
				<p>
					<img src="<?=ROOT_URI?>files/icon/star.png" style="margin-right:5px;"/>
					<strong style="color:#f70;">new message</strong>
				</p>
			<?php endif?>
			<div class="message_content">
				<?=$value['message']?>
			</div>
			<p class="operation_bar">
				<span><?=$value['write_time']?></span>
				<a href="<?=SECTION_URI.Q?>message_drop/<?=$value['id']?>"><?=tt('drop')?></a>
				<a href="<?=SECTION_URI.Q?>message_write/send_to/<?=$value['sender']['login_name']?>" ><?=tt('reply')?></a>
			</p>
		</td>
	</tr>
	<tr style="height:30px;"></tr>
<?php endforeach?>
</table>
<?=render_write_icon('message_write', ('Send a Message'))?>
