<?php

function image_check_max_width($file, $path, $maxwidth){
	$image_src = image_get_src($file, $path);
	if($image_src){
		$src_w = imagesx($image_src);
		$src_h = imagesy($image_src);
		if($src_w >= $maxwidth){
			$dst_w = $maxwidth;
			$dst_h = ($src_h/$src_w)*$dst_w;
		
			$image_dst = imageCreateTrueColor($dst_w, $dst_h);
			imageCopyResized($image_dst, $image_src, 0, 0, 0, 0, $dst_w, $dst_h, $src_w, $src_h);
			imageJPEG($image_dst, $path, 85);
			imageFilter($image_dst, IMG_FILTER_SMOOTH, 12);
			notify_add_info(tt('Image has been automaticaaly resized.'));
		}
	}
}

function image_square_crop($file, $path, $size){
	$image_src = image_get_src($file, $path);
	if($image_src){
		$src_size = min(imagesx($image_src), imagesy($image_src));
		$image_dst = imageCreateTrueColor($size, $size);
		imageCopyResized($image_dst, $image_src, 0, 0, 0, 0, $size, $size, $src_size, $src_size);
		imageFilter($image_dst, IMG_FILTER_SMOOTH, 12);
		imageJPEG($image_dst, $path, 85);
	}
}

function image_generate_thumb($file, $path, $thumbpath){
	$image_src = image_get_src($file, $path);
	if($image_src){
		$src_w = imagesx($image_src);
		$src_h = imagesy($image_src);
		if($src_w >= $src_h){
			$dst_h = 100;
			$dst_w = ($src_w/$src_h)*100;
		}else{
			$dst_w = 100;
			$dst_h = ($src_h/$src_w)*100;
		}
		$image_dst = imageCreateTrueColor($dst_w, $dst_h);
		imageCopyResized($image_dst, $image_src, 0, 0, 0, 0, $dst_w, $dst_h, $src_w, $src_h);
		imageFilter($image_dst, IMG_FILTER_SMOOTH, 12);
		imageJPEG($image_dst, $thumbpath, 85);
	}
}

function image_get_src($file, $path){
	if(is_file($path)){
		if($file['type'] == "image/jpeg" or $file['type'] == "image/pjpeg"){
			return imageCreateFromJPEG($path);
		}
		elseif($file['type'] == "image/png" or $file['type'] == "image/x-png"){
			return  imageCreateFromPNG($path);
		}else{
			notify_add_error(tt('Only .png, .jpeg and .jpg are allowed to be uploaded.'));
			return null;
		}
	}
}

function image_generate_rounded_corner(){

}

/// Source http://www.bradshawenterprises.com/blog/2010/dynamically-drawing-gradients-with-php/
function image_generate_gradient($width, $height, $startColor, $endColor) {
	$final=imagecreatetruecolor($width,$height);
 
	$r=($startColor >> 16) & 0xFF;
	$g=($startColor >> 8) & 0xFF;
	$b=($startColor) & 0xFF;
 
	if ($height==0) {
		imagefill($final,0,0,imagecolorallocate($final,$r,$g,$b));
	} else {
 
		$endR=($endColor >> 16) & 0xFF;
		$endG=($endColor >> 8) & 0xFF;
		$endB=($endColor) & 0xFF;
 
		$incR=($endR-$r);
		$incG=($endG-$g);
		$incB=($endB-$b);
 
		$absDisR=abs($incR);
		$absDisG=abs($incG);
		$absDisB=abs($incB);
 
		if ($absDisR>$absDisG) {
			if ($absDisR>$absDisB) {
				$distance=$absDisR;
			} else {
				$distance=$absDisB;
			}
		} else if ($absDisG>$absDisB) {
			$distance=$absDisG;
		} else {
			$distance=$absDisB;
		}
 
		if ($distance==0) {
			imagefill($final,0,0,imagecolorallocate($final,$r,$g,$b));
		} else {
			if ($distance>$height) $distance=$height;
 
			$sliver=imagecreatetruecolor(1,$distance);
			$sliverMax=$distance-1;
 
			$incR/=$sliverMax;
			$incG/=$sliverMax;
			$incB/=$sliverMax;
 
			$style=array();
 
			for ($t=0; $t<$distance; $t++) {
				$style[$t]=imagecolorallocate($sliver,$r,$g,$b);
				$r+=$incR;
				$g+=$incG;
				$b+=$incB;
			}
 
			imagesetstyle($sliver,$style);
			imageline($sliver,0,0,0,$sliverMax,IMG_COLOR_STYLED);
			imagecopyresized(
				$final,$sliver,
				0,0,0,0,
				$width,$height,1,$distance
			);
			imagedestroy($sliver);
		}
	}
	return $final;
}

?>
