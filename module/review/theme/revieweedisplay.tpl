<?php if(!defined('XIMPLE_CMS')) die();?>
<div class="review">
	<b><a href="review_write/<?=gg('id')?>">new review</a></b>
	<b><?=tt('Review for reviewee: ')?></b>
	<?php foreach($review_data as $key => $value) :?>
		<h3 class="title_label"> review by : <?=$value['reviewer']?> </h3>
		<h3 class="title_label"> star : <?=$value['star']?> </h3>
		<h3 class="title_label"> create date : <?=$value['createdate']?> </h3>
		<a href="review_rating/<?=$reviewee?>/reviewId/<?=$value['id']?>/scorer/<?=$reviewer?>/point/1">+1</a>
		<a href="review_rating/<?=$reviewee?>/reviewId/<?=$value['id']?>/scorer/<?=$reviewer?>/point/-1">-1</a>
		<p> <?=$value['description']?> </p>
		<b> ---------------------------- </b>
	<?php endforeach?>
</div>

