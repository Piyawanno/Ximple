<?php
class PollConfigModel extends Model{
	function PollConfigModel(){
		$this->poll_result_color = $this->color('result bar color');
		
		$this->poll_comment_write_label = $this->title(tt('comment label'));
		$this->poll_comment_write_label->defaultData = tt('Please, write your opinion.');
		$this->poll_comment_write_label->enableTranslate();
		
		$this->poll_comment_page_length = $this->spin(tt('comments number per page'), 5, 50);
		
		$option = array(
			'comment_avatar' => tt('avatar for comments'),
			'signature' => tt('user signature'),
		);
		$this->poll_appearance = $this->checkbox(tt('show in rendered page'), $option);
	}
}
?>
