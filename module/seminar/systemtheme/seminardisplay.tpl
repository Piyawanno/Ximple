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
			<td><?=tt('size');?></td>
			<td><?=$data['size']?></td>
		</tr>
		<tr>
			<td><?=tt('created');?></td>
			<td><?=$data['createdate']?></td>
		</tr>
		<tr>
			<td><?=tt('Date');?></td>
			<td><?=$data['classdate']?></td>
		</tr>
		<tr>
			<td><?=tt('Time');?></td>
			<td><?=$data['classtime']?></td>
		</tr>
		<tr>
			<td><?=tt('description');?></td>
			<td><?=$data['description']?></td>
		</tr>
	</table>
	<a href="<?=SECTION_URI.Q?>seminar_insert_map/<?=$data['id']?>"><?=tt('enroll')?><a/> |
	<a href="<?=SECTION_URI.Q?>seminar_attendantlist/<?=$data['id']?>"><?=tt('status')?><a/> |
	<a href="<?=SECTION_URI.Q?>seminar_write/<?=$data['id']?>"><?=tt('new')?><a/> |
	<a href="<?=SECTION_URI.Q?>seminar_edit/<?=$data['id']?>"><?=tt('edit')?><a/> | 
	<a href="<?=SECTION_URI.Q?>seminar_drop/<?=$data['id']?>"><?=tt('delete')?><a/>
</div>
