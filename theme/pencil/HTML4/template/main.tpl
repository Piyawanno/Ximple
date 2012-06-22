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
			<div id="head_wrapper">
				<a id="head_link" href="<?=SECTION_URI?>"><h1><?=$section_name?></h1></a>
				<h2 style="display:none;"><?=$section_slogan?></h2>
			</div>
			<div id="menu_container">
				<?=$menu?>
			</div>
		</div>
		<div id="color_plate">
			<div id="color_item_1" class="color_item"></div>
			<div id="color_item_2" class="color_item"></div>
			<div id="color_item_3" class="color_item"></div>
			<div id="color_item_4" class="color_item"></div>
			<div id="color_item_5" class="color_item"></div>
			<div id="color_item_6" class="color_item"></div>
			<div id="color_item_7" class="color_item"></div>
			<div id="color_item_8" class="color_item"></div>
			<div id="color_item_9" class="color_item"></div>
			<div id="color_item_10" class="color_item"></div>
			<div id="color_item_11" class="color_item"></div>
			<div id="color_item_12" class="color_item"></div>
		</div>
		<div style="clear:both;"></div>
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
	</div>
	<div id="foot">
		<span>powered by</span>
		<a href="http://www.ximplesoft.com" style="color:white;font-weight:bold;">XimpleSoft</a>
		<?php foreach($widget['foot'] as $key => $item):?>
			<?=$item?>
		<?php endforeach?>
	</div>
	<?php include('operationbar.tpl')?>
	</body>
</html>
