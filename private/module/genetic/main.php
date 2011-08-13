<?php
require_once('CompetitiveClass.class.inc');
require_once('Population.class.inc');

$competitive = new CompetitiveClass();
$population = new Population($competitive);
$result = $population->getPopulation();
?>
