<?php

function input_is_email($email){
	return preg_match('/^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$/', $email);
}

function input_trim($input){
	$input = preg_replace('/\s+/', ' ', $input);
	return $input;
}

function input_split_comma($input){
	$input = split(',', str_replace(' ', '', addslashes(input_trim($input))));
	foreach($input as $key => $value){
		if(strlen($value) == 0) unset($input[$key]);
	}
	return $input;
}

function input_strip_image($input){
	return  preg_replace("/<img[^>]+\>/i", "", $input);
}

function input_reorder_multiple_files($name){
	$reordered = array();
	$received = ff($name);
	$n = count($received['name']);
	if(is_array($received['name'])){
		foreach($received['name'] as $i => $value){
			$reordered[$i]['name']     = $received['name'][$i];
			$reordered[$i]['tmp_name'] = $received['tmp_name'][$i];
			$reordered[$i]['type']     = $received['type'][$i];
			$reordered[$i]['size']     = $received['size'][$i];
			$reordered[$i]['error']    = $received['error'][$i];
		}
	}
	return $reordered;
}

function input_special_char($uri_get, $uri_server){
	foreach($uri_server as $key => $value){
		if(strpos($value, '%') !== false){
			$split1 = str_split($uri_get[$key]);
			$split2 = split('%', $value);
			$res = '';
			foreach($split1 as $ind => $chr){
				if($chr != '.' and $chr != ' ' and $chr != '_') $res .= $split1[$ind];
				elseif(isset($split2[$ind+1])) $res .= chr(hexdec($split2[$ind+1]));
			}
			$uri_server[$key] = $res;
		}
	}
	return $uri_server;
}


function input_strip_slash_array($array){
	foreach($array as $key => $value){
		if(is_array($value)) $array[$key] = translate_strip_slash_array($value);
		else $array[$key] = stripslashes($value);
	}
	return $array;
}

function input_strip_tags($data, $allowed_tag){
	$data = str_replace('<!--', '&lt;!--', $data);
	$data = str_replace('--!>', '--!&gt;', $data);
	$data = strip_tags($data, $allowed_tag);
	$data = str_replace('&lt;!--', '<!--', $data);
	$data = str_replace('--!&gt;', '--!>', $data);
	return $data;
}

?>
