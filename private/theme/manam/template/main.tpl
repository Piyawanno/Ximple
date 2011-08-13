<?php if(!defined('XIMPLE_CMS')) die();?>
<?='<?xml version="1.0" encoding="UTF-8"?>'?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
	<head>
		<?=$head?>
	</head>
	<body>
	<div id="main_container">
		<div id="side_tab"></div>
		<div id="content_container">
			<div id="head">
				<div id="head_logo">
					<a href="<?=SECTION_URI?>"><img src="<?=THEME_URI.'image/seahorse.png'?>" border="0" alt="Manam Thai Food Logo"/></a>
				</div>
				<div style="display:none;">
					<h1><?=$section_name?></h1>
					<h2><?=$section_slogan?></h2>
				</div>
			</div>
			<div id="menu_container">
				<?=$menu?>
			</div>
			<div id="main">
				<div id="body">
					<div id="content">
						<p><?=$path?></p>
						<?=$notify?>
						<?=$body?>
					</div>
					<div id="widget_panel">
						<?php foreach($widget['panel'] as $key => $item):?>
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
		<div style="clear:both;"></div>
	</div>
	<?php if(strlen(ORIG_REQUEST)):?>
		<script>
			var picNumber = Math.round((Math.random()*100))%5;
			var style = "url("+rootURI+"private/theme/manam/image/herb";
			style += picNumber+".jpg) no-repeat right bottom";
			$('#body').css('background', style);
		</script>
	<?php else:?>
		<script>
			var picNumber = 0;
			var style = "url("+rootURI+"private/theme/manam/image/herb";
			style += picNumber+".jpg) no-repeat right bottom";
			$('#body').css('background', style);
		</script>
	<?php endif?>
	</body>
</html>
