<?php
global $hightlight_geshi_included;
$hightlight_geshi_included = false;

function highlight($content){
	$code_array = highlight_getcode($content);
	highlight_clear_cache();
	foreach($code_array as $key => $value){
		$cache_file = highlight_get_cache_file($value['tag']);
		if(is_file($cache_file)){
			$hightlighted = io_read_file($cache_file);
		}else{
			$hightlighted = highlight_execute($value);
			io_write_file($cache_file, $hightlighted);
		}
		$content = str_replace($value['tag'], $hightlighted, $content);
	}
	return $content;
}

function highlight_getcode($content){
	preg_match_all("/<pre\s[^>]*>[^<]*<\/pre>/", $content, $preg_result);
	$code_array = array();
	foreach($preg_result[0] as $key => $value){
		preg_match('/lang="\w*"/', $value, $lang);
		$code = strip_tags($value);
		$code = str_replace("&lt;", "<", $code);
		$code = str_replace("&gt;", ">", $code);
		$code_array[] = array(
			'tag' => $value,
			'language' => substr($lang[0], 6, -1),
			'code' => $code,
		);
	}
	return $code_array;
}

function highlight_execute($code){
	global $hightlight_geshi_included;
	if(!$hightlight_geshi_included){
		include_once(ROOT_PATH.'include/external/geshi/geshi.php');
		$hightlight_geshi_included = true;
	}
	$geshi = new GeSHi($code['code'], $code['language']);
	$geshi->enable_line_numbers(GESHI_FANCY_LINE_NUMBERS);
	return '<div class="code">'.$geshi->parse_code().'</div>';
}

function highlight_get_cache_directory(){
	$directory = ROOT_PATH.'files/highlight/';
	if(!is_dir($directory)) mkdir($directory);
	return $directory;
}

function highlight_get_cache_file($code){
	$directory = highlight_get_cache_directory();
	return $directory.md5($code).'.php';
}

function highlight_clear_cache(){
	$directory = highlight_get_cache_directory();
	$date_file = $directory.'lastclear.txt';
	cache_clear_by_day($date_file, $directory, 30);
}
?>
