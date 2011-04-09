<?php if(!defined('XIMPLE_CMS')) die();?>
<?php foreach($data as $key => $value):?>
	<a href="#" onclick="return changeShownBlog(<?=$key?>, this)" id="promoted_link_<?=$key?>"><?=($key + 1)?></a>
<?php endforeach?>
<?php foreach($data as $key => $value):?>
	<div id="promoted_blog_<?=$key?>" style="display:none;">
		<a href="<?=SECTION_URI.Q.'blog/'.$value['id']?>"><h3 class="title_label"><?=$value['topic']?></h3></a>
		<p>
			<?=$value['intro']?></h3>
		</p>
	</div>
<?php endforeach?>
<?php if(count($data)):?>
	<script>
		var shownBlog = 'promoted_blog_0';
		var activated = $('#promoted_link_0');
		var blogCount = <?=count($data)?>;
		var currentBlog = 0;
		
		$(document).ready(function (){
			$('#promoted_link_0').addClass('promoted_blog_activated');
			$('#'+shownBlog).show('slide');
			slidePromotedBlog();
		});
		
		function changeShownBlog(blogID, clickedLink){
			activated.removeClass('promoted_blog_activated');
			$(clickedLink).addClass('promoted_blog_activated');
			activated = $(clickedLink);
			$('#'+shownBlog).hide();
			shownBlog = 'promoted_blog_'+blogID;
			$('#'+shownBlog).show('slide');
			currentBlog = blogID;
			return false;
		}
		
		function slidePromotedBlog(){
			changeShownBlog(currentBlog, $('#promoted_link_'+currentBlog));
			currentBlog = currentBlog+1;
			if(currentBlog >= blogCount) currentBlog = 0;
			setTimeout("slidePromotedBlog()", 5000);
		}
		
	</script>
<?php endif?>
