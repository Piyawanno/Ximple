<?php
require_once('../setup.php');
require_once('../tool/authority.tool.inc');
require_once('../tool/globalvar.tool.inc');
require_once(DB_TYPE.'_new.inc');

if(authority(array(), array(1))) die('Authorization failed!');
else echo('Authorization ok.');

function dump_db(){
	db_init();
	$tables = db_get_tables();
	
	$dir = ROOT_PATH.'files/sqlbackup/';
	if(!is_dir($dir)) mkdir($dir);
	
	$filename = $dir.'sqlbackup_'.time().'.sql';
	$file = fopen($filename, 'a');
	foreach($tables as $table){
		if($table != 'search' and $table != 'search_source'){
			$sqldatas = db_query("SELECT * FROM $table");
			$query = '';
		
			while ($sqldata = mysql_fetch_assoc($sqldatas)) {
				$keys = "";
				$values = "";
				$query = "";
				foreach($sqldata as $key=>$data){
					$keys .= $key.',';
					$data = str_replace("\\","\\\\",$data);
					$data = str_replace("'","\\'",$data);
					$values .= "'$data',";
				}
				$keys = substr($keys,0,-1);
				$values = substr($values,0,-1);
				$query  = "INSERT INTO $table($keys) VALUES($values);\n\n";
				fwrite($file, $query);
			}
		}
	}
	fclose($file);
	@ chmod($filename,0777);
}

dump_db();
?>
