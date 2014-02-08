<?php if(!defined('XIMPLE_CMS')) die();?>
<div class="list">
	<h3 class="list_label"><?=$meta->title?></h3>
	<?php if(!empty($meta->writeMode)) echo(render_write_icon($meta->writeMode, $meta->writeLabel));?>
	<p><?=$meta->description?></p>
	<?=$table?>
</div>
