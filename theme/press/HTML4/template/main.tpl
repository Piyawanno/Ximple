<?php if(!defined('XIMPLE_CMS')) die();?>
<?='<?xml version="1.0" encoding="UTF-8"?>'?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
	<head>
		<?=$head?>
		<script src="<?=ROOT_URI.'include/external/sha1.js'?>"></script>
	</head>	
	<body>
	<a name="top"></a>
	<div id="main_container">
		<div style="clear:both;"></div>
		<div id="main">
			<div id="content">
				<div id="menu_container">
					<?=$menu?>
				</div>
				<p><?=$path?></p>
				<?=$notify?>
				<?=$body?>
				<div id="foot">
					<span>powered by</span>
					<a href="http://www.ximplesoft.com" style="color:white;font-weight:bold;">XimpleSoft</a>
					<?php foreach($widget['foot'] as $key => $item):?>
						<?=$item?>
					<?php endforeach?>
				</div>
			</div>
            <div id="space_container"><div id="space_holder"></div></div>
            <div id="widget_container">
				<a id="section_head" href="<?=SECTION_URI?>"><h1><?=$section_name?></h1></a>
				<h2 id="slogan_head"><?=$section_slogan?></h2>
				<?=render_search_form()?>
				<div id="widget_right">
					<?php foreach($widget['right'] as $key => $item):?>
						<?=$item?>
					<?php endforeach?>
				</div>
            </div>
			<div style="clear:both;"></div>
		</div>
	</div>
	</body>
</html>
