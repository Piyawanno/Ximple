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
		<div id="main">
          <div id="head_border">
			<div id="head_container">
				<div id="head">
					<div id="menu_container">
				<?=$menu?>
			        </div>
				</div>
			</div>
			</div>
			<div id="body_container">
				<div id="content">
                    <div id="body">
                        <p><?=$path?></p>
                        <?=$notify?>
                        <?=$body?>
				    </div>
				</div>
                <div id="widget_container">
					<div id="widget_right">
						<?php foreach($widget['right'] as $key => $item):?>
							<?=$item?>
						<?php endforeach?>
					</div>
					<div id="widget_bottom"></div>                    
                </div>
				<div style="clear:both;"></div>
			</div>
		</div>
	</div>
	<div id="foot">
		<span>Logo by OnePen Studio powered by</span>
		<a href="<?=SECTION_URI?>">
			<img src="<?=THEME_URI?>image/XimpleSoft.png" border="0" alt="XimpleSoft" align="middle">
		</a>
		<?php foreach($widget['foot'] as $key => $item):?>
			<?=$item?>
		<?php endforeach?>
	</div>
	<?php include('operationbar.tpl')?>
	</body>
</html>
