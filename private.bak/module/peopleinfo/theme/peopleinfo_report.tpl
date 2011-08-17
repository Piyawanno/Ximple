<?php if(!defined('XIMPLE_CMS')) die();?>
<h3 class="list_label"><?=tt('Report Result')?></h3>
<div class="list">
<p><b><?=tt('QUERY')?> : </b><?=$label?></p>
<table width="100%">
	<tr>
		<th><?=tt('name')?></th>
		<?php foreach($data_type as $key =>$value):?>
			<th><?=$value?></th>
		<?php endforeach?>
	</tr>
	<?php foreach($data as $id => $item):?>
		<tr>
		<td><?=render_operation_link('peopleinfo', $id, $item['name'])?></td>
		<?php foreach($data_type as $key =>$value):?>
			<?php if(isset($item['data'][$key])):?>
				<td><?=$item['data'][$key]?></td>
			<?php else:?>
				<td></td>
			<?php endif?>
		<?php endforeach?>
		</tr>
	<?php endforeach?>
</table>
<p>
<a href="<?=SECTION_URI?>files/peopleinfo/csv/<?=$csv?>"><?=tt('Download CSV file')?></a>
</p>
</div>
