<?php
/// @file
/// This file provides functions for document attribute setting and getting.
///
/// @author bow_der_kleine <bow_der_kleine@yahoo.de>

/// Internal global variables for document-tool.
/// These variables should not be used outside this file.

global $document_title, $document_description;
global $document_keywords, $document_redirect;
global $document_is_back, $document_form, $document_path;
global $document_lock_set_path;

$document_lock_set_path = false;
$document_title = '';
$document_description = '';
$document_redirect = '';
$document_keywords = array();
$document_form = false;
$document_path = array();

function document_set_title($title){
	global $document_title;
	$document_title = $title;
}

function document_get_title(){
	global $document_title;
	return $document_title;
}

function document_set_description($description){
	global $document_description;
	$document_description = $description;
}

function document_get_description(){
	global $document_description;
	return $document_description;
}

function document_add_keyword($keyword){
	global $document_keywords;
	if(!in_array($keyword, $document_keywords)){
		$document_keywords[] = $keyword;
	}
}

function document_add_keywords($keywords){
	global $document_keywords;
	$document_keywords = array_merge($document_keywords, $keywords); 
}

function document_get_keywords(){
	global $document_keywords;
	$keywords = join(', ', $document_keywords);
	return empty($keywords) ? '': $keywords;
}

function document_set_redirect($redirect){
	global $document_redirect;
	$document_redirect = $redirect;
}

function document_get_redirect(){
	global $document_redirect;
	return $document_redirect;
}

function document_set_redirect_back(){
	global $document_is_back;
	$document_is_back = true;
}

function document_get_redirect_back(){
	global $document_is_back;
	return $document_is_back;
}

function document_init_form(){
	global $document_form;
	$document_form = true;
}

function document_has_form(){
	global $document_form;
	return $document_form;
}

function document_lock_set_path(){
	global $document_lock_set_path;
	$document_lock_set_path = true;
}

function document_release_set_path(){
	global $document_lock_set_path;
	$document_lock_set_path = false;
}

function document_set_path($name, $uri=''){
	global $document_path;
	global $document_lock_set_path;
	if(!$document_lock_set_path){
		$document_path[$name] = $uri;
	}
}

function document_render_path(){
	global $document_path, $document_title;
	if(IS_INDEX) return '';
	$i = 0;
	$render = '';
	$size = count($document_path);
	$p = '<a href="%s">%s</a>';
	foreach($document_path as $name => $uri){
		if($i == 0){
			$render .= sprintf($p, SECTION_URI, $name);
		}elseif($i != $size-1){
			$render .= sprintf($p, SECTION_URI.Q.$uri, $name);
		}else{
			$render .= $name;
			if(strlen($document_title) == 0){
				$document_title = $name;
			}
		}
		if($i != $size-1){
			$render .= '&#160;&#187;&#160;';
		}
		$i++;
	}
	return $render;
}

?>
