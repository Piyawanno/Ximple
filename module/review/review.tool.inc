<?php
function review_rating_create_table(){
	include_once('ReviewRatingModel.class.inc');
	include_once(ROOT_PATH.'include/class/QuickTableCreator.class.inc');
	$model = new ReviewRatingModel();
	$tableCreator = new QuickTableCreator('review_rating', $model);
	$tableCreator->create();
}
?>
