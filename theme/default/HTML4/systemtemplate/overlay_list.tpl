<?php if(!defined('XIMPLE_CMS')) die();?>
<?php if(strlen($description)):?>
	<p class="form_help"><?=$description?></p>
<?php endif?>
<div class="list">
	<table width="100%"><tbody>
		<tr>
		<?php foreach($column as $key => $col):?>
			<th style="min-width:100px;">
				<?=$label[$col]?>
			</th>
		<?php endforeach?>
			<th colspan="2"><?=tt('operation')?></th>
		</tr>
		
		<?php foreach($data as $id => $value):?>
		<tr>
			<?php foreach($column as $key => $col):?>
				<?php if(substr($value[$col], 0, 4) == '<img'):?>
					<td align="center">
				<?php else:?>
					<td>
				<?php endif?>
				
				<?php if((isset($mode[$col]) or isset($ajax_mode[$col])) and !(isset($value['avoidLink']) and $value['avoidLink'])):?>
					<?php if(isset($value['list_uri'])):?>
						<a href="<?=SECTION_URI.Q.$value['list_uri']?>"><?=$value[$col]?></a></td>
					<?php elseif(isset($ajax_mode[$col])):?>
						<a href="#" onclick="return <?=$ajax_mode[$col]?>(<?=$value['id']?>)"><?=$value[$col]?></a></td>
					<?php else:?>
						<a href="<?=SECTION_URI.Q.$mode[$col].'/'.$value['id']?>"><?=$value[$col]?></a></td>
					<?php endif?>
				<?php else:?>
					<?=$value[$col]?></td>
				<?php endif?>
			<?php endforeach?>
			<td style="width:20px;" align="center">
				<a href="#" onclick="return <?="$edit_function('$form_id', '$module', $id)"?>">
					<img src="<?=ROOT_URI.'files/icon/edit.png'?>" border="0" >
				</a>
			</td>
			<td style="width:20px;" align="center">
				<a href="#" onclick="return <?="$drop_function('$form_id', '$module', $id)"?>">
					<img src="<?=ROOT_URI.'files/icon/drop.png'?>" border="0" >
				</a>
			</td>
		</tr>
		<?php endforeach?>
	</tbody></table>
</div>
