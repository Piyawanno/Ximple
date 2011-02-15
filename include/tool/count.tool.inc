<?php
function count_increase($mode, $id, $offset=0){
	$count_dir = ROOT_PATH.'files/count/';
	if(!is_dir($count_dir)) mkdir($count_dir);
	$count_dir.= SECTION.'/';
	if(!is_dir($count_dir)) mkdir($count_dir);
	$file_name = $count_dir.$mode.'.bin';
	$file = null;
	if(!is_array($id)) $file = count_increase_scalar($file_name, $file, $id, $offset);
	else $file = count_increase_array($file_name, $file, $id, $offset);
	if($file) fclose($file);
}

function count_set($mode, $id, $value){
	$count_dir = ROOT_PATH.'files/count/';
	if(!is_dir($count_dir)) mkdir($count_dir);
	$count_dir.= SECTION.'/';
	if(!is_dir($count_dir)) mkdir($count_dir);
	$file_name = $count_dir.$mode.'.bin';
	if(is_file($file_name)) $file = fopen($file_name, 'r+');
	else $file = fopen($file_name, 'x');
	$bin = pack('V', $value);
	fseek($file, $id*4);
	flock($file, LOCK_EX);
	fwrite($file, $bin);
	flock($file, LOCK_UN);
	if($file) fclose($file);
}


function count_increase_scalar($file_name, $file, $id, $offset){
	if(is_file($file_name)){
		$size = filesize($file_name);
		if($file == null) $file = fopen($file_name, 'r+');
		fseek($file, $id*4, SEEK_SET);
		if($size >= $id*4 + 4){
			$bin = fread($file, 4);
			if(strlen($bin)) $number = unpack('V', $bin);
			else $number = array(0,0);
			$bin = pack('V', $number[1]+1+$offset);
		}else{
			$bin = pack('V', 1+$offset);
		}
	}else{
		if($file == null) $file = fopen($file_name, 'x');
		$bin = pack('V', 1+$offset);
	}
	fseek($file, $id*4);
	flock($file, LOCK_EX);
	fwrite($file, $bin);
	flock($file, LOCK_UN);
	return $file;
}

function count_increase_array($file_name, $file, $id_array, $offset){
	foreach($id_array as $id){
		$file = count_increase_scalar($file_name, $file, $id, $offset);
	}
	return $file;
}

function count_get($mode, $id){
	$file_name = ROOT_PATH.'files/count/'.SECTION.'/'.$mode.'.bin';
	if(!is_file($file_name)) return 0;
	$size = filesize($file_name);
	if($size < $id*4 + 4) return 0;
	$file = fopen($file_name, 'r');
	fseek($file, $id*4);
	$count = unpack('V', fread($file, 4));
	return $count[1];
}

function count_get_array($mode, $id_array){
	$file_name = ROOT_PATH.'files/count/'.SECTION.'/'.$mode.'.bin';
	if(!is_file($file_name)){
		$count = array();
		foreach($id_array as $id){
			$count[$id] = 0;
		}
		return $count;
	}
	$size = filesize($file_name);
	$file = fopen($file_name, 'r');
	$count = array();
	foreach($id_array as $id){
		if($size < $id*4 + 4){
			$count[$id] = 0;
		}else{
			fseek($file, $id*4);
			$number = unpack('V', fread($file, 4));
			$count[$id] = $number[1];
		}
	}
	return $count;
}
?>
