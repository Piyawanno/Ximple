<?php if(!defined('XIMPLE_CMS')) die();?>
<div class="list">
	<h3 class="title_label"><?=$data['topic']?></h3>
	<table width="100%">
		<tr>
			<th><?=tt('Attribute');?></th>
			<th><?=tt('Description');?></th>
		</tr>
		<tr>
			<td><?=tt('owner');?></td>
			<td><?=render_profile_link($data['owner'])?></td>
		</tr>
		<tr>
			<td><?=tt('priority');?></td>
			<td><?=$data['priority']?></td>
		</tr>
		<tr>
			<td><?=tt('created');?></td>
			<td><?=$data['createdate']?></td>
		</tr>
		<tr>
			<td><?=tt('deadline');?></td>
			<td><?=$data['deadline']?></td>
		</tr>
		<tr>
			<td><?=tt('description');?></td>
			<td><?=$data['description']?></td>
		</tr>
	</table>
	<a href="<?=SECTION_URI.Q?>develcard_edit/<?=$data['id']?>"><?=tt('edit')?><a/> | 
	<a href="<?=SECTION_URI.Q?>develcard_drop/<?=$data['id']?>"><?=tt('delete')?><a/>
</div>
