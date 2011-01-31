<?php
include_once('review.tool.inc');
class ReviewRatingModel extends Model {
	function ReviewRatingModel(){
		$this->reviewId = $this->hidden('0', 'int');
		$this->scorer = $this->hidden('0', 'int');
		$this->point = $this->hidden('0', 'int');
	}
}
?>
