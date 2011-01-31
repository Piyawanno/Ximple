<?php
include_once('ReviewRatingModel.class.inc'); //create 'review_rating' table.

function review_rating_create_table(){
	$modelFactory = new ModelFactory('review_rating', new ReviewRatingModel());
	$modelConnector = $modelFactory->bind();
	$tableCreator = new TableCreator($modelConnector, 'review_rating');
	$tableCreator->create();
}
?>
