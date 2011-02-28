<?php if(!defined('XIMPLE_CMS')) die();?>
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
		<a href="#" onclick="return showLogin()">[<?=tt('close')?>]</a>
	</div>
<?php else:?>
	<div id="login_popup" style="display:none;">
		<?=sysblock_panel()?>
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
