<?php

triamsob_switch();

function triamsob_switch(){
	include('triamsob.tool.inc');
	triamsob_define_constant();
	triamsob_add_execute();
	$subject_mode = array('triamsob_tutor_subject_edit', 'triamsob_tutor_subject_save');
	$config_mode  = array('triamsob_config', 'triamsob_config_save');
	if(in_array(MODE, $subject_mode)){
		include('TutorSubject.class.inc');
	}elseif(in_array(MODE, $config_mode)){
		include('TriamsobConfig.class.inc');
	}
}

function triamsob_tutor_article(){
	$clause = 'WHERE (publishing_status < 2 AND category='.TRIAMSOB_TUTOR_CATEGORY.') ';
	$clause.= 'ORDER BY publish_time DESC';
	return triamsob_list_block('journal', $clause);
}

function triamsob_student_article(){
	$clause = 'WHERE (publishing_status < 2 AND category='.TRIAMSOB_STUDENT_CATEGORY.') ';
	$clause.= 'ORDER BY publish_time DESC';
	return triamsob_list_block('journal', $clause);
}

function triamsob_list_block($table, $clause){
	$clause = $clause.' LIMIT 5';
	$item = db_select_single_column($table, 'topic', $clause);
	$render_array = array(
		'mode' => $table,
		'item' => $item,
	);
	return render($render_array, 'module/flashblock/theme/flashblock.tpl', 'flashblock');
}

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
?>
