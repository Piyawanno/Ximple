<?php if(!defined('XIMPLE_CMS')) die();?>
<div id="pager">
	<a href="<?=ROOT_URI.Q.$uri?>/page/0">&#171;</a>
	<?php for($i=$begin;$i < $end;$i++) :?>
		<?php if($current == $i) :?>
			<b><?=$i+1?></b>
		<?php else :?>
			<a href="<?=ROOT_URI.Q.$uri?>/page/<?=$i?>"><?=$i+1?></a>
		<?php endif?>
	<?php endfor?>
	
	<?php if($previous != -1):?>
		<a href="<?=ROOT_URI.Q.$uri?>/page/<?=$previous?>">&#8249;</a>
	<?php endif?>
	
	<?php if($next != -1):?>
		<a href="<?=ROOT_URI.Q.$uri?>/page/<?=$next?>">&#8250;</a>
	<?php endif?>
	
	<a href="<?=ROOT_URI.Q.$uri?>/page/<?=$last?>">&#187;</a>
</div>
