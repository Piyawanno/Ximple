<?php
include_once('SeminarMapModel.class.inc'); //create 'seminar_map' table.
function seminar_map_create_table(){
	$modelFactory = new ModelFactory('seminar_map', new SeminarMapModel());
	$modelConnector = $modelfactory->bind();
	$tableCreator = new TableCreator($modelconnector, 'seminar_map');
	$tableCreator->create();
}
?>
