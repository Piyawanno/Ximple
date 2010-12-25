<?php
class ForumConfigModel extends ContentConfigModel{
	function ForumConfigModel(){
		ContentConfigModel::ContentConfigModel('forum');
		
		$option = array(
			'avatar' => tt('show avatar'),
			'comment_avatar' => tt('show avatar for comments'),
		);
		$this->forum_appearance = $this->checkbox(tt('show in rendered forum'), $option);
	}
}
?>
