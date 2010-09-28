
function checkNotify(){
	if(!isGuest){
		$.get(sectionURI+'notify_check', function(data){
			if(data.length){
				$('#notify_check').remove();
				$('#notify_container').remove();
				$('body').append(data);
				$('#notify_container').dialog({
					bgiframe: true,
					autoOpen: false,
					width:450,
					modal: true,
					title: 'Notification',
					close : function (event, ui){
						$('#notify_check').remove();
						$('#notify_container').remove();
						$.get(sectionURI+'notify_mark_as_read', function(data){});
					}
				});
			}
			setTimeout("checkNotify()", checkNotifyInterval);
		});
	}
}

checkNotify();

function showNotify(){
	$('#notify_container').dialog('open');
}

function randomString() {
	var chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXTZabcdefghiklmnopqrstuvwxyz";
	var string_length = 32;
	var randomstring = "";
	for (var i=0; i<string_length; i++) {
		var rnum = Math.floor(Math.random() * chars.length);
		randomstring += chars.substring(rnum,rnum+1);
	}
	return randomstring;
}

function crypt(){
	var sessionKey;
	var cookies;
	var paraname;
	sessionKey = randomString();
	pass = document.getElementsByName("login_prepassword")[0].value;
	crypted = hex_sha1(pass);
	crypted = hex_sha1(crypted+sessionKey);
	document.getElementsByName("login_password")[0].value=crypted;
	document.getElementsByName("login_salt")[0].value=sessionKey;
	document.getElementsByName("login_prepassword")[0].value="";
}

function hideSub(subConf){
	$('#'+subConf).toggle('blind');
}

function togglePanel(panelID){
	$('.panel_body:visible').hide('blind');
	$('#'+panelID+':hidden').show('blind');
}

function showPlainCode(codeId){
	$('#code_'+codeId).hide();
	$('#plaincode_'+codeId).show();
}

function hidePlainCode(codeId){
	$('#code_'+codeId).show();
	$('#plaincode_'+codeId).hide();
}

function ximplePrint(link){
	window.open(link.href, 'print','toolbar=no,scrollbars=yes,titlebar=no,menubar=no,resizable=yes,width=800,height=600');
}

/// Not verified ///
function hide_sub_plain(sub_conf){
	$('#'+sub_conf).toggle();
}

function submit_sort(colname){
	$("input[name='sort_col']").attr('value', colname);
	$("input[name='search']").attr('value', $("select[name='"+colname+"']").attr('value'));
	$(".select_sort").attr('name', '');
	$(".select_sort").attr('value', '');
	$('#search_form').submit();
}

function submit_page(){
	var colname = $("input[name='sort_col']").attr('value');
	$("input[name='search']").attr('value', $("select[name='"+colname+"']").attr('value'));
	$('#search_form').submit();
}


function clear_sort(){
	$("input[name='sort_col']").attr('value', '');
	$(".select_sort").attr('name', '');
	$(".select_sort").attr('value', '');
	$('#search_form').submit();
}
