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

?>
