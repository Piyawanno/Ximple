<?php
execute_add_function('blog_promote_block');

function blog_promote_block(){
	$column = array('id', 'topic', 'icon', 'intro', 'uri');
	$clause = 'WHERE section='.SECTION.' AND publishing_status=4';
	$data = db_select('blog', $column, $clause);
	$render_array = array('data' => array_values($data));
	head_add_css('blog.css');
	return render($render_array, 'promotedblogs.tpl', 'promotedblogs');
}
?>
