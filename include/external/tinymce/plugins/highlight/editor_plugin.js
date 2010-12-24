(function() {
	// Load plugin specific language pack
	tinymce.PluginManager.requireLangPack('highlight');

	tinymce.create('tinymce.plugins.highlightPlugin', {
		init : function(ed, url) {
			ed.addCommand('mcehighlight', function() {
				ed.windowManager.open({
					file : url + '/dialog.htm',
					width : 620 + ed.getLang('highlight.delta_width', 0),
					height : 300 + ed.getLang('highlight.delta_height', 0),
					inline : 1
				}, {
					plugin_url : url
				});
			});

			ed.addButton('highlight', {
				title : 'highlight.desc',
				cmd : 'mcehighlight',
				image : url + '/img/highlight.png'
			});

			ed.onNodeChange.add(function(ed, cm, n) {
				cm.setActive('highlight', n.nodeName == 'IMG');
			});
		},

		/**
		 * Creates control instances based in the incomming name. This method is normally not
		 * needed since the addButton method of the tinymce.Editor class is a more easy way of adding buttons
		 * but you sometimes need to create more complex controls like listboxes, split buttons etc then this
		 * method can be used to create those.
		 *
		 * @param {String} n Name of the control to create.
		 * @param {tinymce.ControlManager} cm Control manager to use inorder to create new control.
		 * @return {tinymce.ui.Control} New control instance or null if no control was created.
		 */
		createControl : function(n, cm) {
			return null;
		},

		getInfo : function() {
			return {
				longname : 'Code Syntax Highlighting plugin',
				author : 'K. Piyawanno',
				authorurl : 'http://www.biolawcom.de',
				infourl : 'http://www.biolawcom.de',
				version : "1.0"
			};
		}
	});

	// Register plugin
	tinymce.PluginManager.add('highlight', tinymce.plugins.highlightPlugin);
})();
