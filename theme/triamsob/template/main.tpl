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
			<div id="menu_container">
				<?=$menu?>
			</div>
			<div id="main">
				<div id="body">
					<?php if(MODULE=='forum'):?>
						<!-- Forum Content -->
						<div id="forum_content">
							<?php foreach($block['forum_top'] as $key => $item):?>
								<?=$item?>
							<?php endforeach?>
							<?php if(strlen($path)):?>
								<?=triamsob_render_box($path, null, 'forum_box')?>
							<?php endif?>
							<?=$notify?>
							<?=$body?>
							<?php foreach($block['forum_bottom'] as $key => $item):?>
								<?=$item?>
							<?php endforeach?>
						</div>
					<?php else:?>
						<!-- Regular Content -->
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
						
						<!-- Middle Blocks -->
						<div id="block_middle">
							<div id="search_box"></div>
							<div class="facebook_box">
								<div class="facebook_box_head"></div>
								<div class="facebook_box_body">
									<div class="facebook_box_content">
										<iframe src="http://www.facebook.com/plugins/likebox.php?href=http%3A%2F%2Fwww.facebook.com%2Ftriamsob&amp%3Bwidth=250&amp%3Bcolorscheme=light&amp%3Bshow_faces=true&amp%3Bstream=true&amp%3Bheader=true&amp%3Bheight=427" scrolling="no" frameborder="0" style="border:none; overflow:hidden; width:250px; height:427px;" allowTransparency="true"></iframe>
									</div>
								</div>
								<div class="facebook_box_foot"></div>
							</div>
							<?php foreach($block['middle'] as $key => $item):?>
								<?=$item?>
							<?php endforeach?>
						</div>
						
						<!-- Right Blocks -->
						<div id="block_right">
							<?php foreach($block['right'] as $key => $item):?>
							<div class="right_box">
								<div class="right_box_head"></div>
								<div class="right_box_body">
									<div class="right_box_content">
										<?=$item?>
									</div>
								</div>
								<div class="right_box_foot"></div>
							</div>
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
		<div id="search_bar">
			<?=render_search_form()?>
		</div>
		<div id="operation_content">
			<?php if(authority_is_guest()):?>
				<a href="<?=SECTION_URI.Q?>registration"><?=tt('sign up')?></a>
				<a href="#" onclick="return showLogin()"><?=tt('login')?></a>
			<?php else:?>
				<a href="#" onclick="return showLogin()"><?=tt('control panel')?></a>
				<a href="#" onclick="return submitLogout()"><?=tt('logout')?></a>
				<form action="<?= SECTION_URI?>" method="post" id="logout_form">
					<input name="login_name" type="hidden" value=""/>
					<input name="redirect" value="" type="hidden" />
					<input name="login_password" type="hidden" />
					<input name="logout" type="hidden" value="logout"/>
					<input name="login_salt" type="hidden" value="nothing"/>
				</form>
			<?php endif?>
		</div>
	</div>
	<?php if(authority_is_guest()):?>
		<div id="login_popup" style="display:none;">
			<?=sysblock_login()?>
		</div>
	<?php else:?>
		<div id="login_popup" style="display:none;">
			<?=sysblock_panel()?>
		</div>
	<?php endif?>
	<script>
		function showLogin(){
			$('#login_popup').toggle('blind');
			return false;
		}
		
		function submitLogout(){
			$('#logout_form').submit();
		}
	</script>
	</body>
</html>
