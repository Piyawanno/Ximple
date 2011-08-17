<?php if(!defined('XIMPLE_CMS')) die();?>
<?='<?xml version="1.0" encoding="UTF-8"?>'?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
	<head>
		<?=$head?>
	</head>	
	<body>
	<a name="top"></a>
	<div id="search">
		<?=render_search_form()?>
	</div>
	<div id="main_container">
		<div id="head">
			<div id="head_left">
				<a href="<?=SECTION_URI?>"><h1><?=$section_name?></h1></a>
			</div>
			<div id="head_right">
				<div id="head_widget">
					<?php foreach($widget['head'] as $key => $item):?>
						<?=$item?>
					<?php endforeach?>
				</div>
			</div>
		</div>
		<div style="clear:both;"></div>
		<div id="menu_container">
			<?=$menu?>
			<div style="clear:both;"></div>
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
			<div id="foot">
				<?php foreach($widget['foot'] as $key => $item):?>
					<?=$item?>
				<?php endforeach?>
			</div>
		</div>
	</div>
	<br />
	</body>
</html>
