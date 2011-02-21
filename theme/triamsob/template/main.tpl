<?php if(!defined('XIMPLE_CMS')) die();?>
<?require_once(ROOT_PATH.'theme/triamsob/theme.tool.inc');?>
<?='<?xml version="1.0" encoding="UTF-8"?>'?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
	<head>
		<?=$head?>
	</head>	
	<body>
	<a name="top"></a>
	<div id="second_background">
		<div id="main_container">
			<div id="head">
				<h1 style="display:none;"><?=$section_name?></h1></a>
				<h2 style="display:none;"><?=$section_slogan?></h2>
			</div>
			<div id="menu_container">
				<?=$menu?>
			</div>
			<div id="main">
				<div id="body">
					<?php if(MODULE=='forum'):?>
						<div id="forum_content">
							<?php foreach($block['forum_top'] as $key => $item):?>
								<?=$item?>
							<?php endforeach?>
							<?php if(strlen($path)):?>
								<?=triamsob_render_box($path)?>
							<?php endif?>
							<?=$notify?>
							<?=$body?>
							<?php foreach($block['forum_bottom'] as $key => $item):?>
								<?=$item?>
							<?php endforeach?>
						</div>
					<?php else:?>
						<div id="content">
							<?php foreach($block['top'] as $key => $item):?>
								<?=$item?>
							<?php endforeach?>
							<?php if(strlen($path)):?>
								<?=triamsob_render_box($path)?>
							<?php endif?>
							<?=$notify?>
							<?=$body?>
							<?php foreach($block['bottom'] as $key => $item):?>
								<?=$item?>
							<?php endforeach?>
						</div>
						<div id="block_middle">
							<div id="search_box">
							</div>
							<?php foreach($block['middle'] as $key => $item):?>
								<?=$item?>
							<?php endforeach?>
						</div>
						<div id="block_right_top">
							<?php foreach($block['right_top'] as $key => $item):?>
								<?=$item?>
							<?php endforeach?>
						</div>
						<div id="block_right_botoom">
							<?php foreach($block['right_bottom'] as $key => $item):?>
								<?=$item?>
							<?php endforeach?>
						</div>
					<?php endif?>
				</div>
				<div id="foot">
					<div id="foot_head"></div>
					<div id="foot_body">
						<?php foreach($block['foot'] as $key => $item):?>
							<?=$item?>
						<?php endforeach?>
					<div>
				</div>
			</div>
		</div>
	</div>
	<div id="operation_bar">
		
	</div>
	</body>
</html>
