<?php if(!defined('XIMPLE_CMS')) die();?>
<?require_once(ROOT_PATH.'theme/triamsob/theme.tool.inc');?>
<?='<?xml version="1.0" encoding="UTF-8"?>'?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
	<head>
		<?=$head?>
		<script src="<?=ROOT_URI.'include/external/sha1.js'?>"></script>
	</head>
	<body>
	<a name="top"></a>
	<div id="second_background">
		<div id="main_container">
			<div id="head">
				<h1 style="display:none;"><?=$section_name?></h1></a>
				<h2 style="display:none;"><?=$section_slogan?></h2>
			</div>
			<div id="main">
				<div id="social_tab">
					<div id="social_box">
						<div class="social_head"></div>
						<div class="social_body">
						<div class="social_content">
							<a href="http://www.facebook.com/TriamSob"><img src="<?=ROOT_URI?>theme/triamsob/image/bottoncanfb.png" alt="facebook" border="0" /></a>
							<a href="http://twitter.com/triamsob"><img src="<?=ROOT_URI?>theme/triamsob/image/bottoncantwitter.png" alt="facebook" border="0" /></a>
							<a href="http://www.youtube.com/triamsob"><img src="<?=ROOT_URI?>theme/triamsob/image/bottoncanyoutube.png" alt="facebook" border="0" /></a>
						</div>	
						</div>
						<div class="social_foot"></div>
					</div>
				</div>
				<div id="body">
					<script>
						autoCompleteTop = -235;
						autoCompleteLeft = -166;
					</script>
					<?php if(MODULE=='forum'):?>
						<?php include('forumcontent.tpl')?>
					<?php else:?>
						<?php include('content.tpl')?>
					<?php endif?>
					<div style="clear:both;"></div>
				</div> <!--body-->
				<div style="clear:both;"></div>
			</div> <!--main-->
		</div> <!--main_container-->
	</div> <!--second_background-->
	<div id="menu_container">
		<?=$menu?>
	</div>
	<div id="foot">
		<div id="foot_body">
			<?php foreach($block['foot'] as $key => $item):?>
				<?=$item?>
			<?php endforeach?>
		<div>
		<div style="clear:both;"></div>
	</div>
	<?php include('operationbar.tpl')?>
	</body>
</html>
