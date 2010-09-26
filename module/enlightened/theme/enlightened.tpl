<?php if(!defined('XIMPLE_CMS')) die();?>
<div id="enlightened">
	<?php foreach($news as $key => $value):?>
		<div class="image_container">
			<img src="<?=ROOT_URI?>module/enlightened/theme/news.jpg"/>
		</div>
		<div class="content_container">
			<h3 class="title_label"><a href="<?=render_uri('blog', $value)?>"><?=$value['topic']?></a></h3>
			<p class="type_label">::: ประกาศนิติราษฏร์ :::</p>
			<?=input_strip_image($value['intro'])?>
		</div>
	<?endforeach?>
	
	<?php foreach($item['บทความ'] as $key => $value):?>
		<div class="image_container">
			<img src="<?=ROOT_URI.$value['icon']?>"/>
		</div>
		<div class="content_container">
			<h3 class="title_label"><a href="<?=render_uri('page', $value)?>"><?=$value['topic']?></a></h3>
			<p class="type_label">::: บทความ :::</p>
			<?=input_strip_image($value['introduction'])?>
		</div>
	<?endforeach?>
	
	<?php foreach($item['สัมมนา-บทสัมภาษณ์'] as $key => $value):?>
		<div class="image_container">
			<img src="<?=ROOT_URI.$value['icon']?>"/>
		</div>
		<div class="content_container">
			<h3 class="title_label"><a href="<?=render_uri('page', $value)?>"><?=$value['topic']?></a></h3>
			<p class="type_label">::: สัมมนา-บทสัมภาษณ์ :::</p>
			<?=input_strip_image($value['introduction'])?>
		</div>
	<?endforeach?>
	
	<?php foreach($item['ไฟล์เสียง-ภาพ'] as $key => $value):?>
		<div class="image_container">
			<img src="<?=ROOT_URI.$value['icon']?>"/>
		</div>
		<div class="content_container">
			<h3 class="title_label"><a href="<?=render_uri('page', $value)?>"><?=$value['topic']?></a></h3>
			<p class="type_label">::: ไฟล์เสียง/ภาพ :::</p>
			<?=input_strip_image($value['introduction'])?>
		</div>
	<?endforeach?>
	
	<?php/*
	<?php if(isset($download['name'])):?>
		<div class="image_container">
			<?php if(isset($download['avatar'])):?>
				<img src="<?=ROOT_URI.$download['avatar']?>"/>
			<?php endif?>
		</div>
		<div class="content_container">
			<h3 class="title_label"><a href="<?=SECTION_URI.Q?>directory/<?=(((int)$download['category'])+12)?>"><?=$download['name']?></a></h3>
			<p class="type_label">::: เอกสารประกอบการสอน :::</p>
			<?=input_strip_image($download['description'])?>
		</div>
	<?php endif?>
	*/?>
	
	<?php foreach($item['เอกสารประวัติศาสตร์'] as $key => $value):?>
		<div class="image_container">
			<img src="<?=ROOT_URI?>module/enlightened/theme/history.jpg"/>
		</div>
		<div class="content_container">
			<h3 class="title_label"><a href="<?=render_uri('page', $value)?>"><?=$value['topic']?></a></h3>
			<p class="type_label">::: เอกสารประวิติศาสตร์ :::</p>
			<?=input_strip_image($value['introduction'])?>
		</div>
	<?endforeach?>
	
	
	<?php foreach($item['บทความนักศึกษา'] as $key => $value):?>
		<div class="image_container">
			<img src="<?=ROOT_URI?>module/enlightened/theme/article.jpg"/>
		</div>
		<div class="content_container">
			<h3 class="title_label"><a href="<?=render_uri('page', $value)?>"><?=$value['topic']?></a></h3>
			<p class="type_label">::: บทความนักศึกษา :::</p>
			<?=input_strip_image($value['introduction'])?>
		</div>
	<?endforeach?>
	
	<?php foreach($item['บทความแนะนำ'] as $key => $value):?>
		<div class="image_container">
			<img src="<?=ROOT_URI?>module/enlightened/theme/recommended.jpg"/>
		</div>
		<div class="content_container">
			<h3 class="title_label"><a href="<?=render_uri('page', $value)?>"><?=$value['topic']?></a></h3>
			<p class="type_label">::: บทความแนะนำ :::</p>
			<?=input_strip_image($value['introduction'])?>
		</div>
	<?endforeach?>
	
	<?php foreach($item['แถลงการณ์'] as $key => $value):?>
		<div class="image_container">
			<img src="<?=ROOT_URI.$value['icon']?>"/>
		</div>
		<div class="content_container">
			<h3 class="title_label"><a href="<?=render_uri('page', $value)?>"><?=$value['topic']?></a></h3>
			<p class="type_label">::: แถลงการณ์ :::</p>
			<?=input_strip_image($value['introduction'])?>
		</div>
	<?endforeach?>
	
	<?php if(isset($blog['topic'])):?>
		<div class="image_container">
			<img src="<?=ROOT_URI?>module/enlightened/theme/blog.jpg"/>
		</div>
		<div class="content_container">
			<h3 class="title_label"><a href="<?=render_uri('blog', $blog)?>"><?=$blog['topic']?></a></h3>
			<p class="type_label">::: ปกิณกะ :::</p>
			<?=input_strip_image($blog['intro'])?>
		</div>
	<?php endif?>
</div>
