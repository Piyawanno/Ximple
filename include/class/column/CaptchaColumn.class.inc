<?php
class CaptchaColumn extends ModelColumn{
	function CaptchaColumn(){
		$this->setType('char');
		$this->isDB = false;
		$this->isNotNull = true;
		$this->label = tt('insert code from followed picture before submit');
	}
	
	public function renderForm($formID){
		$genTime = time();
		$this->prepareJS($genTime);
		return '
			<input name="captcha_gentime_'.$this->name.'" type="hidden" value="'.$genTime.'"/>
			<input name="captcha_code_'.$this->name.'" id="captcha_code_'.$this->name.'" type="hidden" value="" />
			<input name="'.$this->name.'" size="25" maxlength="6" onkeyup="checkCaptcha(\''.$this->name.'\')" id="captcha_input_'.$this->name.'"/>
			<font id="captcha_info_'.$this->name.'" style="font-weight:bold;"></font>
			<br /><br />
			<img src="'.SECTION_URI.Q.'captcha/gentime/'.$genTime.'" style="padding:0;" border="0" id="captcha_img_'.$this->name.'"/>
			<a href="javascript:changeCaptcha(\''.$this->name.'\', '.$genTime.')">
				<img src="'.ROOT_URI.'files/icon/refresh.png" style="padding:0;margin:auto auto 16px 16px;" border="0"/>
			</a>
		';
	}
	
	private function prepareJS($genTime){
		head_add_js('include/javascript/captchacolumn.js');
		head_add_js_var('generateTime', $genTime);
		head_add_js_var('captchaMessage', tt('Please insert code from image before submit.'));
		head_add_js_var('captchaCorrect', tt('Code from image is correct.'));
		head_add_js_var('captchaWrong', tt('Code from image is wrong.'));
		head_add_js_var('captchaLock', true);
	}
}
?>
