<?php
while(true){
	ob_start();
	echo(exec('php cron.php'));
	ob_flush();
	flush();
	sleep(1);
}
?>
