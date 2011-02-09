<?php if(!defined('XIMPLE_CMS')) die();?>
<?php $last_key = count($data)-1;?>
<?php $i = 0;?>
<?php foreach($data as $key=>$value):?>
<?php if($i == $last_key):?>
	<a name="last_comment"></a>
<?php endif?>
<?php $i++;?>
<a name="comment_<?=$value['id']?>">
<div class="comment">
	<h3 class="title_label">
		<?php if($value['writer_id']['id'] == -1):?>
			<a href="<?=$value['homepage']?>"><?=$value['writer']?></a>
		<?php else:?>
			<?=render_profile_linke($value['writer_id'])?>
		<?php endif?>
	</h3>
	<?php if($value['is_new']):?>
		<p>
			<img src="<?=ROOT_URI?>files/icon/new.png" border="0" style="margin-right:15px;" align="left"/>
			<span style="color:#f70;"><?=tt('new comment')?></span>
		</p>
	<?php endif?>
	<table width="100%">
		<tr>
			<td valign="top"><?=$value['comment']?></td>
			<?php if($is_avatar):?>
				<td align="center" width="10%"><?=render_avatar($value['writer_id'], false)?></td>
			<?php endif?>
		</tr>
	</table>
	<p class="comment_foot">
		<a><?=$value['write_time']?></a>
		<?php if($value['editable']):?>
			<a href="<?=SECTION_URI.Q?>comment_edit/<?=$value['id']?>/module/<?=$value['mode']?>/parent/<?=$value['parent']?>"><?=tt('edit')?></a>
			<a href="<?=SECTION_URI.Q?>comment_drop/<?=$value['id']?>/module/<?=$value['mode']?>/parent/<?=$value['parent']?>"><?=tt('drop')?></a>
		<?php endif?>
	</p>
</div>
<?php endforeach?>
