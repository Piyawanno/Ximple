<?php if(!defined('XIMPLE_CMS')) die();?>
<?='<?xml version="1.0" encoding="UTF-8"?>'?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
	<head>
		<?=$head?>
	</head>	
	<body>
	<a name="top"></a>
	<div id="main_container">
		<div id="head">
			<a href="<?=SECTION_URI?>" id="header_link">
				<img src="<?=THEME_URI.'image/logo.png'?>" alt="<?=$section_name?>" border="0">
			</a>
			<h2><?=$section_slogan?></h2>
		</div>
		<div id="main">
			<?php if(MODE == 'about'):?>
				<div id="home_body">
			<?php else:?>
				<div id="body">
			<?php endif?>
				<?php if(MODE == 'page'):?>
					<div id="content">
						<?=$notify?>
						<?=$body?>
					</div>
					<div id="middle_widget">
						<?php foreach($widget['middle'] as $key => $item):?>
							<?=$item?>
						<?php endforeach?>
					</div>
				<?php else:?>
					<div id="wide_content">
						<?=$notify?>
						<?=$body?>
					</div>
				<?php endif?>
				<div id="left_widget">
					<div id="facebook_box">
						<script src="http://connect.facebook.net/en_US/all.js#xfbml=1"></script><fb:like-box href="https://www.facebook.com/pages/VeniceCheeseCake/174078049309070" width="180" height="330" colorscheme="dark" show_faces="true" stream="true" header="true"></fb:like-box>
					</div>
					<div id="flavor_box">
						<?php foreach($widget['flavor'] as $key => $item):?>
							<?=$item?>
						<?php endforeach?>
					</div>
				</div>
				<a href="http://www.ximplesoft.com/">
					<div id="ximple_link">
						<p style="display:none;">All rights reserved ©2011 XimpleSoft</p>
					</div>
				</a>
				<div style="clear:both;"></div>
			</div>
			<div id="menu_container">
				<?=$menu?>
			</div>
			<div style="clear:both;"></div>
			
			<div id="foot">
			</div>
		</div>
	</div>
	<?php include('operationbar.tpl')?>
	</body>
</html>
