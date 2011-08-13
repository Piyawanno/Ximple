<?php if(!defined('XIMPLE_CMS')) die();?>
<?='<?xml version="1.0" encoding="UTF-8"?>'?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
	<head>
		<?=$head?>
		<script>
			function changeWidget(contentID){
				var leftWidget = $('#left_widget_content');
				leftWidget.hide();
				leftWidget.html($('#'+contentID).html());
				leftWidget.show('scale');
				return false;
			}
		</script>
	</head>	
	<body>
	<a name="top"></a>
	<?php if(MODE == 'about'):?>
		<div id="home_container">
	<?php else:?>
		<div id="main_container">
	<?php endif?>
		<div id="head">
			<a id="head_name" href="<?=SECTION_URI?>"><h1><?=$section_name?></h1></a>
			<h2 id="head_slogan"><?=$section_slogan?></h2>
			<div style="clear:both;"></div>
		</div>
		<div id="body">
			<?php if(MODE == 'page'):?>
				<table><tr>
					<td>
						<div id="left_widget">
							<div id="left_widget_content">
								<?php foreach($widget['left'] as $key => $item):?>
									<?=$item?>
								<?php endforeach?>
							</div>
						</div>
					</td>
					<td valign="bottom">
						<div id="content">
							<div class="content_top"></div>
							<div class="content_body">
								<?=$notify?>
								<?=$body?>
							</div>
							<div class="content_bottom"></div>
						</div>
					</td>
				</tr></table>
			<?php else:?>
				<div id="wide_content">
					<?=$notify?>
					<?=$body?>
				</div>
			<?php endif?>
			<div style="clear:both;"></div>
		</div>
		<div id="menu_line">
			<div id="menu_container">
				<?=$menu?>
			</div>
			<div id="facebook_link">
				<a href="https://www.facebook.com/pages/After-Hours-Silom-Soi6/150352825030230"><img src="<?=SECTION_URI?>private/theme/afterhours/image/facebook.png"></a>
			</div>
			<div style="clear:both;"></div>
		</div>
		<div style="clear:both;"></div>
		<div id="foot">
			<?php foreach($widget['foot'] as $key => $item):?>
				<?=$item?>
			<?php endforeach?>
		</div>
	</div>
	<?php include('operationbar.tpl')?>
	</body>
</html>
