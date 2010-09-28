<?php if(!defined('XIMPLE_CMS')) die();?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<title>{#advimage_dlg.dialog_title}</title>
	<script type="text/javascript" src="<?=ROOT_URI?>include/external/tinymce/tiny_mce_popup.js"></script>
	<script type="text/javascript" src="<?=ROOT_URI?>include/external/tinymce/utils/mctabs.js"></script>
	<script type="text/javascript" src="<?=ROOT_URI?>include/external/tinymce/utils/form_utils.js"></script>
	<script type="text/javascript" src="<?=ROOT_URI?>include/external/tinymce/utils/validate.js"></script>
	<script type="text/javascript" src="<?=ROOT_URI?>include/external/tinymce/utils/editable_selects.js"></script>
	<script type="text/javascript" src="<?=ROOT_URI?>include/external/tinymce/plugins/advimage/js/image.js"></script>
	<script type="text/javascript">
		function create_folder(link){
			var folder_name = document.getElementById("folder").value;
			if(folder_name.length){
				window.location.href = "<?=SECTION_URI?>?mode=imageloader_create_directory&dir=<?=$current_dir?>&dir_create="+folder_name;
			}
		}
		
		function select_img(img_src){
			document.getElementById("src").value = img_src;
			document.getElementById("alt").value = "Image";
			ImageDialog.showPreviewImage(img_src);
			mcTabs.displayTab('general_tab','general_panel');
		}
		
		function check_focus(){
			var isInit = window.location.href.indexOf('initial=');
			if(document.getElementById("src").value.length && isInit != -1){
				mcTabs.displayTab('general_tab','general_panel');
			}else{
				mcTabs.displayTab('upload_tab','upload_panel');
			}
		}
		
		function submit_form(mess){
			if(mess != 'upload'){
				ImageDialog.insert();
			}else{
				document.image_form.submit();
			}
		}
	</script>
	<style>
		#src_list, #over_list, #out_list {width:280px;}
		.mceActionPanel {margin-top:7px;}
		.alignPreview {border:1px solid #000; width:140px; height:140px; overflow:hidden; padding:5px;}
		.checkbox {border:0;}
		.panel_wrapper div.current {height:560px;}
		#prev {margin:0; border:1px solid #000; width:428px; height:450px; overflow:auto;}
		#align, #classlist {width:150px;}
		#width, #height {vertical-align:middle; width:50px; text-align:center;}
		#vspace, #hspace, #border {vertical-align:middle; width:30px; text-align:center;}
		#class_list {width:180px;}
		input {width: 280px;}
		#constrain, #onmousemovecheck {width:auto;}
		#id, #dir, #lang, #usemap, #longdesc {width:200px;}
		#dirlist{height:125px;overflow-y:scroll;overflow-x:hidden;margin:10px 0px 10px 0px;}
		#imglist{height:280px;overflow-y:scroll;overflow-x:hidden;margin:10px 0px 10px 0px;}
	</style>
	<base target="_self" />
</head>
<body id="advimage" style="display: none">
	<form action="<?=SECTION_URI.Q?>imageloader_upload" name="image_form" enctype="multipart/form-data" method="post" >
		<div class="tabs">
			<ul>
				<?php if(!$is_guest):?>
				<li id="upload_tab" class="current">
					<span><a href="javascript:mcTabs.displayTab('upload_tab','upload_panel');" onmousedown="return false;">
						Select &amp; Upload Image</a></span>
				</li>
				<li id="general_tab"><span><a href="javascript:mcTabs.displayTab('general_tab','general_panel');" onmousedown="return false;">{#advimage_dlg.tab_general}</a></span></li>
				<?php else:?>
				<li id="general_tab" class="current"><span><a href="javascript:mcTabs.displayTab('general_tab','general_panel');" onmousedown="return false;">{#advimage_dlg.tab_general}</a></span></li>
				<?php endif?>
				<li id="appearance_tab"><span><a href="javascript:mcTabs.displayTab('appearance_tab','appearance_panel');" onmousedown="return false;">{#advimage_dlg.tab_appearance}</a></span></li>
			</ul>
		</div>

		<div class="panel_wrapper">
			<?php if(!$is_guest):?>
			<div id="upload_panel" class="panel current">
				<fieldset>
						<legend>Images</legend>
						<div id="imglist">
							<table style="width:95%;margin-left:20px;">
							<?php foreach($image as $key => $value):?>
								<tr><td style="width:95%;padding-top:20px;">
									<p>
										<a href="javascript:select_img('<?=ROOT_URI.$value['src']?>')" style="text-decoration:none;">
											<img src="<?=ROOT_URI.$value['src']?>" border="0"  style="max-width:120px;margin-right:10px;" align="left"/>
											<strong>URL : </strong><?=ROOT_URI.$value['src']?>
										</a>
									</p>
									<p><strong>size : </strong><?=render_file_size($value['size']);?></p>
									<a href="<?=SECTION_URI.Q?>imageloader_drop/<?=$value['src']?>">[<?=tt('delete');?>]</a>
								</td></tr>
							<?php endforeach?>
							</table>
						</div>
						<input type="hidden" name="upload_dir" value="<?=$current_dir?>" />
						<input type="file" name="file_to_upload" size="30"/>
						<input value="uploade image" type="submit" style="width:120px;" >
				</fieldset>
				<fieldset>
						<legend>Folders</legend>
						<div id="dirlist">
							<table style="width:90%;margin-left:20px;">
							<?php $i=0;?>
							<?php foreach($directory as $key => $value):?>
								<?php if($i%3 == 0):?>
									<tr>
								<?php endif?>
								<td style="width:25%;">
									<a href="<?=SECTION_URI?>?mode=imageloader&dir=<?=$value['dir']?>" style="text-decoration:none;">
										<img src="<?=ROOT_URI?>files/icon/folder.png" border="0" /> <?=$value['label']?>
									</a>
								</td>
								<?php if($i%3 == 2):?>
									</tr>
								<?php endif?>
								<?php $i++;?>
							<?php endforeach?>
							</table>
						</div>
						<input name="folder" id="folder"/>
						<input value="create folder" type="button" style="width:120px;" onclick="javascript:create_folder(this)" >
				</fieldset>
				
			</div>
			<?php endif?>
			<div id="general_panel" class="panel">
				<fieldset>
						<legend>{#advimage_dlg.general}</legend>

						<table class="properties">
							<tr>
								<td class="column1"><label id="srclabel" for="src">{#advimage_dlg.src}</label></td>
								<td colspan="2"><table border="0" cellspacing="0" cellpadding="0">
									<tr> 
									  <td><input name="src" type="text" id="src" value="" class="mceFocus" onchange="ImageDialog.showPreviewImage(this.value);" /></td> 
									  <td id="srcbrowsercontainer">&nbsp;</td>
									</tr>
								  </table></td>
							</tr>
							<tr>
								<td><label for="src_list">{#advimage_dlg.image_list}</label></td>
								<td><select id="src_list" name="src_list" onchange="document.getElementById('src').value=this.options[this.selectedIndex].value;document.getElementById('alt').value=this.options[this.selectedIndex].text;document.getElementById('title').value=this.options[this.selectedIndex].text;ImageDialog.showPreviewImage(this.options[this.selectedIndex].value);"></select></td>
							</tr>
							<tr> 
								<td class="column1"><label id="altlabel" for="alt">{#advimage_dlg.alt}</label></td> 
								<td colspan="2"><input id="alt" name="alt" type="text" value="" /></td> 
							</tr> 
							<tr> 
								<td class="column1"><label id="titlelabel" for="title">{#advimage_dlg.title}</label></td> 
								<td colspan="2"><input id="title" name="title" type="text" value="" /></td> 
							</tr>
						</table>
				</fieldset>

				<fieldset>
					<legend>{#advimage_dlg.preview}</legend>
					<div id="prev"></div>
				</fieldset>
			</div>

			<div id="appearance_panel" class="panel">
				<fieldset>
					<legend>{#advimage_dlg.tab_appearance}</legend>

					<table border="0" cellpadding="4" cellspacing="0">
						<tr> 
							<td class="column1"><label id="alignlabel" for="align">{#advimage_dlg.align}</label></td> 
							<td><select id="align" name="align" onchange="ImageDialog.updateStyle('align');ImageDialog.changeAppearance();"> 
									<option value="">{#not_set}</option> 
									<option value="baseline">{#advimage_dlg.align_baseline}</option>
									<option value="top">{#advimage_dlg.align_top}</option>
									<option value="middle">{#advimage_dlg.align_middle}</option>
									<option value="bottom">{#advimage_dlg.align_bottom}</option>
									<option value="text-top">{#advimage_dlg.align_texttop}</option>
									<option value="text-bottom">{#advimage_dlg.align_textbottom}</option>
									<option value="left">{#advimage_dlg.align_left}</option>
									<option value="right">{#advimage_dlg.align_right}</option>
								</select> 
							</td>
							<td rowspan="6" valign="top">
								<div class="alignPreview">
									<img id="alignSampleImg" src="<?=ROOT_URI?>include/external/tinymce/plugins/advimage/img/sample.gif" alt="{#advimage_dlg.example_img}" />
									Lorem ipsum, Dolor sit amet, consectetuer adipiscing loreum ipsum edipiscing elit, sed diam
									nonummy nibh euismod tincidunt ut laoreet dolore magna aliquam erat volutpat.Loreum ipsum
									edipiscing elit, sed diam nonummy nibh euismod tincidunt ut laoreet dolore magna aliquam
									erat volutpat.
								</div>
							</td>
						</tr>

						<tr>
							<td class="column1"><label id="widthlabel" for="width">{#advimage_dlg.dimensions}</label></td>
							<td nowrap="nowrap">
								<input name="width" type="text" id="width" value="" size="5" maxlength="5" class="size" onchange="ImageDialog.changeHeight();" /> x 
								<input name="height" type="text" id="height" value="" size="5" maxlength="5" class="size" onchange="ImageDialog.changeWidth();" /> px
							</td>
						</tr>

						<tr>
							<td>&nbsp;</td>
							<td><table border="0" cellpadding="0" cellspacing="0">
									<tr>
										<td><input id="constrain" type="checkbox" name="constrain" class="checkbox" /></td>
										<td><label id="constrainlabel" for="constrain">{#advimage_dlg.constrain_proportions}</label></td>
									</tr>
								</table></td>
						</tr>

						<tr>
							<td class="column1"><label id="vspacelabel" for="vspace">{#advimage_dlg.vspace}</label></td> 
							<td><input name="vspace" type="text" id="vspace" value="" size="3" maxlength="3" class="number" onchange="ImageDialog.updateStyle('vspace');ImageDialog.changeAppearance();" onblur="ImageDialog.updateStyle('vspace');ImageDialog.changeAppearance();" />
							</td>
						</tr>

						<tr> 
							<td class="column1"><label id="hspacelabel" for="hspace">{#advimage_dlg.hspace}</label></td> 
							<td><input name="hspace" type="text" id="hspace" value="" size="3" maxlength="3" class="number" onchange="ImageDialog.updateStyle('hspace');ImageDialog.changeAppearance();" onblur="ImageDialog.updateStyle('hspace');ImageDialog.changeAppearance();" /></td> 
						</tr>

						<tr>
							<td class="column1"><label id="borderlabel" for="border">{#advimage_dlg.border}</label></td> 
							<td><input id="border" name="border" type="text" value="" size="3" maxlength="3" class="number" onchange="ImageDialog.updateStyle('border');ImageDialog.changeAppearance();" onblur="ImageDialog.updateStyle('border');ImageDialog.changeAppearance();" /></td> 
						</tr>

						<tr>
							<td><label for="class_list">{#class_name}</label></td>
							<td colspan="2"><select id="class_list" name="class_list" class="mceEditableSelect"></select></td>
						</tr>

						<tr>
							<td class="column1"><label id="stylelabel" for="style">{#advimage_dlg.style}</label></td> 
							<td colspan="2"><input id="style" name="style" type="text" value="" onchange="ImageDialog.changeAppearance();" /></td> 
						</tr>

						<!-- <tr>
							<td class="column1"><label id="classeslabel" for="classes">{#advimage_dlg.classes}</label></td> 
							<td colspan="2"><input id="classes" name="classes" type="text" value="" onchange="selectByValue(this.form,'classlist',this.value,true);" /></td> 
						</tr> -->
					</table>
				</fieldset>
				<fieldset>
					<legend>{#advimage_dlg.swap_image}</legend>

					<input type="checkbox" id="onmousemovecheck" name="onmousemovecheck" class="checkbox" onclick="ImageDialog.setSwapImage(this.checked);" />
					<label id="onmousemovechecklabel" for="onmousemovecheck">{#advimage_dlg.alt_image}</label>

					<table border="0" cellpadding="4" cellspacing="0" width="100%">
							<tr>
								<td class="column1"><label id="onmouseoversrclabel" for="onmouseoversrc">{#advimage_dlg.mouseover}</label></td> 
								<td><table border="0" cellspacing="0" cellpadding="0"> 
									<tr> 
									  <td><input id="onmouseoversrc" name="onmouseoversrc" type="text" value="" /></td> 
									  <td id="onmouseoversrccontainer">&nbsp;</td>
									</tr>
								  </table></td>
							</tr>
							<tr>
								<td><label for="over_list">{#advimage_dlg.image_list}</label></td>
								<td><select id="over_list" name="over_list" onchange="document.getElementById('onmouseoversrc').value=this.options[this.selectedIndex].value;"></select></td>
							</tr>
							<tr> 
								<td class="column1"><label id="onmouseoutsrclabel" for="onmouseoutsrc">{#advimage_dlg.mouseout}</label></td> 
								<td class="column2"><table border="0" cellspacing="0" cellpadding="0"> 
									<tr> 
									  <td><input id="onmouseoutsrc" name="onmouseoutsrc" type="text" value="" /></td> 
									  <td id="onmouseoutsrccontainer">&nbsp;</td>
									</tr> 
								  </table></td> 
							</tr>
							<tr>
								<td><label for="out_list">{#advimage_dlg.image_list}</label></td>
								<td><select id="out_list" name="out_list" onchange="document.getElementById('onmouseoutsrc').value=this.options[this.selectedIndex].value;"></select></td>
							</tr>
					</table>
				</fieldset>

				<fieldset>
					<legend>{#advimage_dlg.misc}</legend>

					<table border="0" cellpadding="4" cellspacing="0">
						<tr>
							<td class="column1"><label id="idlabel" for="id">{#advimage_dlg.id}</label></td> 
							<td><input id="id" name="id" type="text" value="" /></td> 
						</tr>

						<tr>
							<td class="column1"><label id="dirlabel" for="dir">{#advimage_dlg.langdir}</label></td> 
							<td>
								<select id="dir" name="dir" onchange="ImageDialog.changeAppearance();"> 
										<option value="">{#not_set}</option> 
										<option value="ltr">{#advimage_dlg.ltr}</option> 
										<option value="rtl">{#advimage_dlg.rtl}</option> 
								</select>
							</td> 
						</tr>

						<tr>
							<td class="column1"><label id="langlabel" for="lang">{#advimage_dlg.langcode}</label></td> 
							<td>
								<input id="lang" name="lang" type="text" value="" />
							</td> 
						</tr>

						<tr>
							<td class="column1"><label id="usemaplabel" for="usemap">{#advimage_dlg.map}</label></td> 
							<td>
								<input id="usemap" name="usemap" type="text" value="" />
							</td> 
						</tr>

						<tr>
							<td class="column1"><label id="longdesclabel" for="longdesc">{#advimage_dlg.long_desc}</label></td>
							<td><table border="0" cellspacing="0" cellpadding="0">
									<tr>
									  <td><input id="longdesc" name="longdesc" type="text" value="" /></td>
									  <td id="longdesccontainer">&nbsp;</td>
									</tr>
								</table></td> 
						</tr>
					</table>
				</fieldset>
			</div>
		</div>

		<div class="mceActionPanel">
			<div style="float: left">
				<input type="submit" id="insert" name="insert" value="{#insert}" onclick="submit_form('no upload')"/>
			</div>

			<div style="float: right">
				<input type="button" id="cancel" name="cancel" value="{#cancel}" onclick="tinyMCEPopup.close();" />
			</div>
		</div>
    </form>
</body> 
</html> 
