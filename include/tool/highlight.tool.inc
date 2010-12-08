<?php

function highlight($content){
	$code_array = highlight_getcode($content);
	if(count($code_array)){
		include_once(ROOT_PATH.'include/external/geshi/geshi.php');
	}
	foreach($code_array as $key => $value){
		$hightlighted = highlight_execute($value);
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
	$geshi = new GeSHi($code['code'], $code['language']);
	$geshi->enable_line_numbers(GESHI_FANCY_LINE_NUMBERS);
	return '<blockquote>'.$geshi->parse_code().'</blockquote>';
}

?>
