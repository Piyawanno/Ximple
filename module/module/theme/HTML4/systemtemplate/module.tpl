<?php if(!defined('XIMPLE_CMS')) die();?>
<script>
function highlightLink(link){
	$('#module_sort_block a').css({
		'font-weight' : 'normal',
		'color' : '#666',
	});
	
	$(link).css({
		'font-weight' : 'bold',
		'color' : '#800',
	});
}

function showModuleAlphabet(link, alphabet){
	highlightLink(link);
	var checkAlphabet = function(){
		var mid = $(this).attr('id');
		if(mid.substring(0, 1) == alphabet) $(this).show();
		else $(this).hide();
	}
	$('.private_module').each(checkAlphabet);
	$('.public_module').each(checkAlphabet);
	return false;
}

function showAllModule(link){
	highlightLink(link);
	$('.private_module').each(function(){$(this).show()});
	$('.public_module').each(function(){$(this).show()});
	return false;
}

function showInstalled(link){
	highlightLink(link);
	var checkInstalled = function(){
		var rel = $(this).attr('rel');
		if(rel == 'installed') $(this).show();
		else $(this).hide();
	}
	$('.private_module').each(checkInstalled);
	$('.public_module').each(checkInstalled);
	return false;
}

function showNotInstalled(link){
	highlightLink(link);
	var checkNotInstalled = function(){
		var rel = $(this).attr('rel');
		if(rel == 'not_installed') $(this).show();
		else $(this).hide();
	}
	$('.private_module').each(checkNotInstalled);
	$('.public_module').each(checkNotInstalled);
	return false;
}

addReady(function(){
	for(var i=97; i<97+26;i++){
		var alphabet = String.fromCharCode(i);
		$('#module_sort_block').append('<a href="#" onclick="return showModuleAlphabet(this, \''+alphabet+'\')">'+alphabet+'</a> ');
	}
	showInstalled($('#module_installed_link'));
});
</script>
<div class="list">
<h3 class="list_label"><?=tt('Manage Module')?></h3>
<h4>legends</h4>
<ul>
	<li><b>enable</b> : <?=tt('Check this field and submit. Checked modules will be activated.')?></li>
	<li><img src="<?=ROOT_URI?>files/icon/stop.png" border="0" /> : <?=tt('deactivate module')?></li>
	<li><img src="<?=ROOT_URI?>files/icon/correct.png" border="0" /> : <?=tt('activate module')?></li>
	<li><img src="<?=ROOT_URI?>files/icon/refresh_16.png" border="0" /> : <?=tt('refresh module')?></li>
</ul>
<div id="module_sort_block">
	<a href="#" onclick="return showAllModule(this);"><?=tt('all')?></a>
	<a href="#" onclick="return showInstalled(this);" id="module_installed_link"><?=tt('installed')?></a>
	<a href="#" onclick="return showNotInstalled(this);"><?=tt('not installed')?></a>
</div>
<form action="<?=SECTION_URI.Q?>module_init" method="post">
<table width="100%"><tbody>
	<tr>
		<th width="20%"><?=tt('module name / description')?></th>
		<th width="10%"><?=tt('enable')?></th>
		<th width="10%"><?=tt('activate')?></th>
		<th width="10%"><?=tt('refresh')?></th>
	</tr>
	<?php if($has_private):?>
	<tr>
		<td colspan="4">
			<strong><?=tt('Private Module')?></strong>
			<p><?=tt('The followed modules can be used only in this Section.')?></p>
		</td>
	</tr>
	<?php endif?>
	<?php $previous=true?>
	<?php foreach($module as $name => $value):?>
	<?php if($value['is_private']):?>
		<tr class="private_module" id="<?=$name?>_module_row" rel="<?=$value['installed'] ? 'installed' : 'not_installed' ?>" >
	<?php elseif($previous and $has_private):?>
		<tr>
			<td colspan="4"><strong><?=tt('Public Module')?></strong></td>
		</tr>
		<tr class="public_module" id="<?=$name?>_module_row" rel="<?=$value['installed'] ? 'installed' : 'not_installed' ?>" >
		<?php $previous=false?>
	<?php else:?>
		<tr class="public_module" id="<?=$name?>_module_row" rel="<?=$value['installed'] ? 'installed' : 'not_installed' ?>" >
	<?php endif?>
		<td width="80%">
			<p><strong><?=$value['name']?></strong></p>
			<p><?=$value['description']?></p>
		</td>
		<td align="center">
			<?php if($value['installed']) : ?>
				<input type="checkbox" value="<?=$name?>" name="<?=$name?>" checked="checked" />
			<?php else:?>
				<input type="checkbox" value="<?=$name?>" name="<?=$name?>" />
			<?php endif?>
		</td>
		<td align="center">
		<?php if($value['installed']) : ?>
			<a href="<?=SECTION_URI.Q?>module_deactivate/module_name/<?=$name?>">
				<img src="<?=ROOT_URI?>files/icon/stop.png" border="0" />
			</a>
		<?php else:?>
			<a href="<?=SECTION_URI.Q?>module_activate/module_name/<?=$name?>">
				<img src="<?=ROOT_URI?>files/icon/correct.png" border="0" />
			</a>
		<?php endif?>
		</td>
		<td align="center">
			<a href="<?=SECTION_URI.Q?>module_refresh/module_name/<?=$name?>">
				<img src="<?=ROOT_URI?>files/icon/refresh_16.png" border="0" />
			</a>
		</td>
	</tr>
	<?php endforeach?>
</tbody></table>
<input type="submit" value="<?=tt('submit Module configuration')?>"/>
</form>
</div>
