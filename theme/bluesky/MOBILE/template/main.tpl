<?php if(!defined('XIMPLE_CMS')) die();?>
<?='<?xml version="1.0" encoding="UTF-8"?>'?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
	<head>
		<meta name="viewport" content="width=device-width, initial-scale=1"> 
		<?=$head?>
	</head>	
	<body>
		<a name="top"></a>
		<div data-role="page"> 
			<div data-role="header">
				<h1><?=$title?></h1>
				<?=$path?>
			</div>
			<div data-role="content"><?=$body?></div>
			<?php if(strlen($mobile_footer)):?>
			<div data-role="footer">
				<?=$mobile_footer?>
			</div>
			<?php endif?>
		</div>
	</body>
</html>
