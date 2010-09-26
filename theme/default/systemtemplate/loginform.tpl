<?php if(!defined('XIMPLE_CMS')) die();?>
<div id="login_form">
	<form action="<?=SECTION_URI?>" method="post" onsubmit="crypt()">
		<?=tt('name')?>
		<input name="login_name" size="12" style="display:block;margin:5px;" class="logininput"/>
		<input name="redirect" value="<?=ORIG_REQUEST?>" type="hidden" />
		<?=tt('password')?>
		<input name="login_prepassword" type="password" size="12" style="display:block;margin:5px;" class="logininput" />
		<input name="login_password" type="hidden" />
		<input name="login_salt" type="hidden" />
		<input name="login" type="hidden" value="login"/>
		<input type="submit" id="loginsubmit" value="login" style="display:block;margin:5px;"/>
	</form>
	<br />
	<?php if($allow_forget):?>
	<a style="padding:0;margin:0;background:none;" href="<?= SECTION_URI.Q?>forgot_password"><?=tt('forgot password')?></a>
	<?php endif?>
</div>
