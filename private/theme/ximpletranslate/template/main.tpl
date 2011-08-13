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
		<div id="head">
			<div style="display:none;">
				<h1><?=$section_name?></h1></a>
				<h2><?=$section_slogan?></h2>
			</div>
		</div>
		<div id="head">
			<div id="menu_container">
				<?=$menu?>
			</div>
			<div id="logo_container">
				<a href="<?=SECTION_URI?>">
					<img src="<?=THEME_URI.'image/XimpleTranslate.png'?>" border="0" id="ximple_logo">
				</a>
			</div>
		</div>
		<div id="main">
			<div id="body">
				<div id="content">
					<p><?=$path?></p>
					<?=$notify?>
					<?=$body?>
				</div>
				<div id="widget_left">
					<?php foreach($widget['left'] as $key => $item):?>
						<?=$item?>
					<?php endforeach?>
				</div>
				<div style="clear:both;"></div>
			</div>
		</div>
		<div id="powered">
			powered by <a href="http://www.ximplesoft.com">
				<img src="<?=THEME_URI.'image/XimpleSoft.png'?>" border="0" align="middle" />
			</a>
		</div>
	</div>
	<?php include('operationbar.tpl')?>
	</body>
</html>
