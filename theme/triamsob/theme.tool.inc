<?php
if(!function_exists('triamsob_render_box')){
	function triamsob_render_box($body, $head=null, $class='main_box'){
		if($head!=null){
			$head = '<h3 class="title_label">'.$head.'</h3>';
		}
		return '
		<div class="'.$class.'">
			<div class="'.$class.'_head"></div>
			<div class="'.$class.'_body">
				<div class="'.$class.'_content">
					'.$head.'
					'.$body.'
				</div>
			</div>
			<div class="'.$class.'_foot"></div>
		</div>';
	}
}
?>
