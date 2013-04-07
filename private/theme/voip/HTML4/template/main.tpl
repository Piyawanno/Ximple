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
				<a id="head_link" href="<?=SECTION_URI?>">
				<h1 style="display:none;"><?=$section_name?></h1></a>
				<h2><?=$section_slogan?></h2>
			</div>
		</div>
		<div id="menu_container">
			<div id="menu_wrapper">
				<?=$menu?>
			</div>
			<div id="language_container">
				<?=syswidget_translate_flag();?>
			</div>
		</div>
		
		<?php if(MODE == cc('index_mode') && MODE_ID == 0):?>
			<div id="top">
				<?php if(strlen($path)):?><p><?=$path?></p><?php endif?>
				<?=$notify?>
				<?=$body?>
			</div>
		<?php else:?>
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
		<?php endif?>
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
