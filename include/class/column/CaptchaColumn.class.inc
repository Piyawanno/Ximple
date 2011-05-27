<?php
class CaptchaColumn extends ModelColumn{
	function CaptchaColumn(){
		$this->setType('char');
		$this->isDB = false;
		$this->isNotNull = true;
		$this->label = tt('insert code from followed picture before submit');
	}
	
	public function renderForm($formID){
		$id = $formID.'_'.$this->name;
		$genTime = time();
		$this->prepareJS($genTime);
		
		$this->resetFormAttribute();
		$this->setFormAttribute('name', 'captcha_gentime_'.$this->name);
		$this->setFormAttribute('type', 'hidden');
		$this->setFormAttribute('value', $genTime);
		$render  = '<input '.$this->renderFormAttribute().'/>';
		
		$this->resetFormAttribute();
		$this->setFormAttribute('name', 'captcha_code_'.$this->name);
		$this->setFormAttribute('id', 'captcha_code_'.$this->name);
		$this->setFormAttribute('type', 'hidden');
		$render .= '<input '.$this->renderFormAttribute().'/>';
		
		$this->resetFormAttribute();
		$this->setFormAttribute('name', $this->name);
		$this->setFormAttribute('id', $id);
		$this->setFormAttribute('size', 25);
		$this->setFormAttribute('maxsize', 6);
		$this->setFormAttribute('onkeyup', 'checkCaptcha(\''.$this->name.'\', \''.$id.'\')');
		$render .= '<input '.$this->renderFormAttribute().'/>';
		$render .= '<font id="captcha_info_'.$this->name.'" style="font-weight:bold;"></font>';
		$render .= '<br /><br />';
		
		$this->resetFormAttribute();
		$this->setFormAttribute('src', SECTION_URI.Q.'captcha/gentime/'.$genTime);
		$this->setFormAttribute('style', 'padding:0;');
		$this->setFormAttribute('border', '0');
		$this->setFormAttribute('id', 'captcha_img_'.$this->name);
		$render .= '<img '.$this->renderFormAttribute().'/>';
		
		$this->resetFormAttribute();
		$this->setFormAttribute('src', ROOT_URI.'files/icon/refresh.png');
		$this->setFormAttribute('style', 'padding:0;margin:auto auto 16px 16px;');
		$this->setFormAttribute('border', '0');
		$render .= '<a href="javascript:changeCaptcha(\''.$this->name.'\', \''.$id.'\')">';
		$render .= '<img '.$this->renderFormAttribute().'/>';
		$render .= '</a>';
		return $render;
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
