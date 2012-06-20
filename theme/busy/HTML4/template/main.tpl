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
		<div id="section_head">
			<a href="<?=SECTION_URI?>"><h1><?=$section_name?></h1></a>
			<h2 id="slogan_head"><?=$section_slogan?></h2>
		</div>
		<div id="search_container">
			<?=render_search_form()?>
		</div>
		<div style="clear:both;"></div>
		<div id="head">
			<div id="menu_container">
				<?=$menu?>
			</div>
			<div id="widget_top_container">
				<div id="widget_top">
					<?php foreach($widget['top'] as $key => $item):?>
						<?=$item?>
					<?php endforeach?>
				</div>
			</div>
		</div>
		<div id="main">
			<div id="content">
				<p><?=$path?></p>
				<?=$notify?>
				<?=$body?>
			</div>
            <div id="widget_container">
				<div id="widget_left">
					<?php foreach($widget['left'] as $key => $item):?>
						<?=$item?>
					<?php endforeach?>
				</div>
            </div>
			<div style="clear:both;"></div>
		</div>
		<div id="foot">
			<span>powered by</span>
			<a href="http://www.ximplesoft.com" style="font-weight:bold;">XimpleSoft</a>
			<span>credit picture from</span>
			<a href="http://www.wallpapersgalaxy.com/business-people-around-the-world-wallpaper/" style="font-weight:bold;"	>Wallpapers Galaxy</a>
			<?php foreach($widget['foot'] as $key => $item):?>
				<?=$item?>
			<?php endforeach?>
		</div>
	</div>
	</body>
</html>
