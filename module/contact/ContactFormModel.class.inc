<?php
class ContactFormModel extends Model{
	function ContactFormModel($contactID){
		$this->email = $this->email(tt('your email address'));
		$this->subject = $this->title(tt('subject'));
		$this->message = $this->shortText(tt('message'));
		$this->message->isNotNull = true;
		$this->id = $this->hidden($contactID, 'int');
	}
}
?>
