<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="list_label"><?=sprintf(tt('Evaluation Result for %s'), $evaluatee['login_name'])?></h3>
<p><?=$model['description']?></p>
<?=render_avatar($evaluatee, true)?>
<?php $result_number = count($result)?>
<?php if($result_number):?>
	<h4><?=tt('Opinion of evaluator')?></h4>
	<ul>
		<?php foreach($data as $key => $value):?>
		<li>
			<?php if($profile_access):?>
				<a name="evaluator_<?=$value['evaluator']['id']?>" />
				<h4><?=render_profile_link($value['evaluator'])?></h4>
			<?php endif?>
			<p><?=$value['opinion']?></p>
		</li>
		<?php endforeach?>
	</ul>
<?php endif?>
<div class="list">
	<table width="100%"><tbody>
		<tr>
			<th rowspan="2"><?=tt('description')?></th>
			<th colspan="<?=$result_number+1?>"><?=tt('result')?></th>
		</tr>
		<tr>
			<?php $i=0;?>
			<?php foreach($data as $key => $value):?>
				<?php $i++;?>
				<td align="center"><a href="#evaluator_<?=$value['evaluator']['id']?>"><?=$i?></td>
			<?php endforeach?>
			<td  align="center"><?=tt('averaged')?></td>
		</tr>
		<?php $average_sum=0?>
		<?php foreach($model['model'] as $name => $sub_model):?>
			<tr>
				<td colspan="<?=$result_number+2?>"><h4><?=$name?></h4></td>
			</tr>
			<?php foreach($sub_model as $key => $value):?>
				<tr>
					<td>
						<?=$value['name']?> (<?=$value['max']?>)
						<p style="color:#666;font-size:11px;"><?=$value['description']?></p>
					</td>
					<?php $sum=0;?>
					<?php foreach($data as $data_key => $data_value):?>
						<?php $sum+=$result[$data_key][$key];?>
						<td align="center"><?=$result[$data_key][$key]?></td>
					<?php endforeach?>
					<?php if($result_number):?>
						<td align="center"><?=sprintf('%.2f', ($sum/$result_number))?></td>
					<?php else:?>
						<td align="center">0</td>
					<?php endif?>
					<?php if($result_number) $average_sum += $sum/$result_number;?>
				</tr>
			<?php endforeach?>
		<?php endforeach?>
		<tr>
			<td align="center" colspan="<?=$result_number+1?>"><h4><u><?=tt('sum')?></u></h4></td>
			<td align="center"><?=$average_sum?></td>
		</tr>
	</table>
</div>
		
