<?php
execute_add_function('imageloader_cle');
execute_add_function('imageloader_simple');
execute_add_function('imageloader_upload');
execute_add_function('imageloader_simple_upload');
execute_add_function('imageloader_create_directory');
imageloader_avoid_up_dir(gg('file'));

function imageloader_simple(){
	if(authority_is_guest()) error_denied();
	execute_set_ajax();
	$path = gg('dir');
	$render_array = array(
		'current_dir' => gg('dir'),
		'is_guest' => authority_is_guest(),
		'image' => imageloader_get_image($path),
		'loader_id' => gg('loader_id'),
	);
	return render($render_array, 'imageloader_simple.tpl', 'imageloader_simple');
}

function imageloader_cle(){
	if(authority_is_guest()) error_denied();
	execute_set_ajax();
	$path = imageloader_get_user_image_path();
	$render_array = array(
		'current_dir' => $path,
		'is_guest' => authority_is_guest(),
		'image' => imageloader_get_image($path),
	);
	return render($render_array, 'imageloader_cle.tpl', 'imageloader_cle');
}

function imageloader_upload(){
	execute_set_db();
	if(!authority_is_guest()){
		io_upload(ff('file_to_upload'), ROOT_PATH.'files/member/'.USER_ID.'/'.pp('upload_dir'));
	}
	document_set_redirect('?mode=imageloader&dir='.pp('upload_dir'));
}

function imageloader_simple_upload(){
	execute_set_db();
	if(!authority_is_guest()){
		io_upload(ff('file_to_upload'), pp('current_dir'));
	}
}

function imageloader_create_directory(){
	execute_set_db();
	if(!authority_is_guest()){	
		$path = ROOT_PATH.'files/member/'.USER_ID.'/'.gg('dir').gg('dir_create');
		if(!is_dir($path)) mkdir($path);
	}
	document_set_redirect('?mode=imageloader&dir='.gg('dir'));
}

function imageloader_get_image($path){
	$accepted_ext = array('gif', 'png', 'jpg', 'jpeg', 'tiff');
	$success = true;
	@$d = dir($path) or $success=false;
	if($success and !authority_is_guest()){
		$image = array();
		while (false !== ($entry = $d->read())){
			if(is_file($path.$entry)){
				$ext = split('\.', $entry);
				$ext = $ext[count($ext)-1];
				if(in_array(strtolower($ext), $accepted_ext)){
					$size = filesize($path.$entry);
					$image[] = array(
						'src' => $path.$entry,
						'size' => $size
					);
				}
			}
		}
		return $image;
	}else{
		notify_error('Problem by opening image directory');
		return array();
	}
}

function imageloader_get_user_image_path(){
	$path = ROOT_PATH.'files/member/';
	if(!is_dir($path)) mkdir($path);
	$path.= USER_ID.'/';
	if(!is_dir($path)) mkdir($path);
	$path.= 'image/';
	if(!is_dir($path)) mkdir($path);
	return $path;
}

function imageloader_get_directory(){
	$success = true;
	$path = 'files/member/'.USER_ID.'/'.gg('dir');
	@$d = dir($path) or $success=false;
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
