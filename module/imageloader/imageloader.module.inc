<?php
execute_add_function('imageloader');
execute_add_function('imageloader_upload');
execute_add_function('imageloader_create_directory');
imageloader_avoid_up_dir(gg('file'));

function imageloader(){
	execute_set_file();
	header('Content-Type: text/html; charset=UTF-8');
	$render_array = array(
		'current_dir' => gg('dir'),
		'is_guest' => authority_is_guest(),
		'image' => imageloader_get_image(),
		'directory' => imageloader_get_directory(),
	);
	$render = render($render_array, 'imageloader.tpl', 'imageloader');
	echo($render);
}

function imageloader_upload(){
	execute_set_db();
	if(!authority_is_guest()){
		io_upload(ff('file_to_upload'), ROOT_PATH.'files/member/'.USER_ID.'/'.pp('upload_dir'));
	}
	document_set_redirect('?mode=imageloader&dir='.pp('upload_dir'));
}

function imageloader_create_directory(){
	execute_set_db();
	if(!authority_is_guest()){	
		$path = ROOT_PATH.'files/member/'.USER_ID.'/'.gg('dir').gg('dir_create');
		if(!is_dir($path)) mkdir($path);
	}
	document_set_redirect('?mode=imageloader&dir='.gg('dir'));
}

function imageloader_get_image(){
	$path = 'files/member/'.USER_ID.'/'.gg('dir');
	$accepted_ext = array('gif', 'png', 'jpg', 'jpeg', 'tiff');
	$success = true;
	@$d = dir(ROOT_PATH.$path) or $success=false;
	if($success and !authority_is_guest()){
		$image = array();
		while (false !== ($entry = $d->read())){
			if(is_file(ROOT_PATH.$path.$entry)){
				$ext = split('\.', $entry);
				$ext = $ext[count($ext)-1];
				if(in_array(strtolower($ext), $accepted_ext)){
					$size = filesize(ROOT_PATH.$path.$entry);
					$image[] = array('src' => $path.$entry, 'size' => $size);
				}
			}
		}
		return $image;
	}else{
		echo('Problem by opening image directory');
		return array();
	}
}

function imageloader_get_directory(){
	$success = true;
	$path = 'files/member/'.USER_ID.'/'.gg('dir');
	@$d = dir(ROOT_PATH.$path) or $success=false;
	if($success and !authority_is_guest()){
		$directory = array();
		if(strlen(gg('dir'))){
			$parent_dir = dirname(gg('dir'));
			if($parent_dir == '.') $parent_dir = '';
			$directory[] = array('dir' => $parent_dir, 'label' => '.. (go up)');
		}
		while (false !== ($entry = $d->read())){
			if($entry != '.' and $entry != '..' and is_dir(ROOT_PATH.$path.$entry)){
				$directory[] = array('dir' => gg('dir').$entry.'/', 'label' => $entry);
			}
		}
		return $directory;
	}else{
		echo('Problem by opening image directory');
		return array();
	}
}

function imageloader_avoid_up_dir($dir){
	if(count(split('\/\.\.', $dir)) >= 2) error_denied();
}
?>
