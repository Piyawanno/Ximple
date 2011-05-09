<script>
var isStop = new Array();
var pictures = new Array();
var current = new Array();
<?php foreach($data as $key => $value):?>
	pictures[<?=$key?>] = new Array();
	<?php $i=0;?>
	<?php foreach($value['picture'] as $pictureID => $pictureName):?>
		pictures[<?=$key?>][<?=$i?>] = "<?=ROOT_URI?>files/gallery/<?=$key?>/thumb_<?=$pictureName?>";
		<?php $i++;;?>
	<?php endforeach?>
	current[<?=$key?>] = 0;
	isStop[<?=$key?>] = false;
<?php endforeach?>

function changeThumb(gid){
	var img = document.getElementById("thumb_"+gid);
	img.src = pictures[gid][current[gid]];
	current[gid] ++;
	if(current[gid] >= pictures[gid].length){
		current[gid] = 0;
	}
	if(!isStop[gid]){
		setTimeout("changeThumb("+gid+")", 1000);
	}else{
		isStop[gid] = false;
	}
}

function setStop(gid){
	isStop[gid] = true;
	current[gid] = 0;
	var img = document.getElementById("thumb_"+gid);
	img.src = pictures[gid][0];
}
</script>
<div class="gallery_list" style="margin-top:50px;background:url(<?=ROOT_URI?>theme/afterhours/image/gallery-background.png);">
	<table width="100%">
	<?php $count=0;?>
	<?php foreach($data as $key => $value):?>
		<?php $pictureName = array_values($value['picture']);?>
		<?php $count++;?>
		<?php if($count%3 == 1):?>
		<tr>
		<?php endif?>
			<td class="tumbnail" valign="center" align="center" onmouseover="changeThumb(<?=$key?>)"" onmouseout="setStop(<?=$key?>)">
				<?php if(count($value['picture'])):?>
				<a href="<?=render_uri('gallery', $value)?>">
					<img src="<?=ROOT_URI?>files/gallery/<?=$key?>/thumb_<?=$pictureName[0]?>" border="0" id="thumb_<?=$key?>"/>
				</a>
				<?php endif?>
				<h4><a href="<?=render_uri('gallery', $value)?>"><?=$value['topic']?></a></h4>
			</td>
		<?php if($count%3 == 0 or $count == $pictureNumber):?>
		</tr>
		<?php endif?>
	<?php endforeach?>
	</table>
</div>
