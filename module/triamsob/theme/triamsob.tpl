<?php if(!defined('XIMPLE_CMS')) die();?>
<?php foreach($journal as $reference => $data):?>
	<div class="main_box">
		<div class="main_box_head"></div>
		<div class="main_box_body">
			<div id="<?=$reference?>_content">
				<?=triamsob_render_category_link($category[$data['category']], $data['category'], 'journal', '<div class="traimsob_linkbox"></div>')?>
				<h3 class="title_label" style="display:none;"><?=$data['label']?></h3>
				<?php foreach($data['data'] as $key => $value):?>
				<?php if(strlen($value['icon'])):?>
					<img src="<?=ROOT_URI.$value['icon']?>" class="triamsob_icon" />
				<?php endif?>
				<div class="triamsob_item">
					<h4><a href="<?=render_uri('journal', $value)?>"><?=$value['topic']?></a></h4>
					<?=triamsob_wrap_paragraph($value['intro'])?></a>
				</div>
				<div style="clear:both;"></div>
				<?php endforeach?>
				</ul>
			</div>
			<div class="triamsob_read_more">
				<?=triamsob_render_category_link($category[$data['category']], $data['category'], 'journal', tt('read more'))?>
			</div>
		</div>
		<div class="main_box_foot"></div>
	</div>
<?php endforeach?>

<div>
	<div class="main_box_head"></div>
	<div class="main_box_body">
		<div id="forum_content">
			<a href="<?=SECTION_URI.Q.'forum'?>"><div class="traimsob_linkbox"></div></a>
			<h3><?=tt('Last commented Forum')?></h3>
			<ul>
			<?php foreach($last_posted_forum as $key => $value):?>
				<li><a href="<?=SECTION_URI.Q.'forum_entry/'.$key?>"><?=$value?></a></li>
			<?php endforeach?>
			</ul>
			
			<h3><?=tt('Last posted Forum')?></h3>
			<ul>
			<?php foreach($last_commented_forum as $key => $value):?>
				<li><a href="<?=SECTION_URI.Q.'forum_entry/'.$key?>"><?=$value?></a></li>
			<?php endforeach?>
			</ul>
		</div>
		<div class="triamsob_read_more">
			<a href="<?=SECTION_URI.Q.'forum'?>"><?=tt('read more')?></a>
		</div>
	</div>
	<div class="main_box_foot"></div>
</div>
