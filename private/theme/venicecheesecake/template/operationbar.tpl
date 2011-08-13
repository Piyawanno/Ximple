<?php if(!defined('XIMPLE_CMS')) die();?>
<div id="operation_bar">
	<div id="search_bar">
		<?=render_search_form()?>
	</div>
	<div id="operation_content">
		<?php if(!authority_is_guest()):?>
			<div style="float:right;">
				<a href="#" onclick="return showLogin()"><?=tt('control panel')?></a>
				<a href="#" onclick="return submitLogout()"><?=tt('logout')?></a>
				<form action="<?= SECTION_URI?>" method="post" id="logout_form">
					<input name="login_name" type="hidden" value=""/>
					<input name="redirect" value="" type="hidden" />
					<input name="login_password" type="hidden" />
					<input name="logout" type="hidden" value="logout"/>
					<input name="login_salt" type="hidden" value="nothing"/>
				</form>
			</div>
		<?php endif?>
		<div id="facebook_share">
			<a name="fb_share" type="button" share_url="<?=SECTION_URI.Q.ORIG_REQUEST?>"></a> 
			<script src="http://static.ak.fbcdn.net/connect.php/js/FB.Share" type="text/javascript">
			</script>
		</div>
		<script src="http://connect.facebook.net/en_US/all.js#xfbml=1"></script>
		<fb:like href="<?=SECTION_URI.Q.ORIG_REQUEST?>" layout="button_count" show_faces="true" width="35" height="23">
		</fb:like>
	</div>
</div>
<?php if(authority_is_guest()):?>
	<div id="login_popup" style="display:none;">
		<?=syswidget_login()?>
		<a href="#" onclick="return showLogin()">[<?=tt('close')?>]</a>
	</div>
<?php else:?>
	<div id="login_popup" style="display:none;">
		<?=syswidget_panel()?>
		<a href="#" onclick="return showLogin()">[<?=tt('close')?>]</a>
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
