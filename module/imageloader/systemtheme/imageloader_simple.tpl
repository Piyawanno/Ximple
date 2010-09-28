<?php if(!defined('XIMPLE_CMS')) die();?>
<style>
.image_container{
	text-align:center;
	margin:10px;
	width:120px;
	float:left;
}

.image_container img{
	max-width:120px;
}
</style>
<form enctype="multipart/form-data" method="post">
	<input type="file" name="file_to_upload" size="25"/>
	<input value="uploade image" type="submit" style="width:120px;" >
</form>
<p><strong><?=tt('click on image to select')?></strong></p>
<?php foreach($image as $key => $value):?>
	<div class="image_container">
		<a href="#" onclick="loaderChangeImage('<?=$loader_id?>', '<?=ROOT_URI.$value['src']?>', '<?=$value['src']?>');return false;">
			<img src="<?=ROOT_URI.$value['src']?>" border="0"/>
		</a>
		<br />
		<strong>size : </strong><?=render_file_size($value['size']);?>
	</div>
<?php endforeach?>
<p style="clear:both;"></p>
