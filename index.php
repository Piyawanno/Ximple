<?php
	define('BOOT_TIME', (float)microtime(true));
	define('SECTION', 1);
	define('SECTION_PATH', dirname(__FILE__).'/');
	require('include/tool/boot.tool.inc');
	boot();
?>
