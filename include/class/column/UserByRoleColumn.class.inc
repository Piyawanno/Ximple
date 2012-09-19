<?php
require_once('SelectColumn.class.inc`');

class UserByRoleColumn extends SelectColumn{
	private $role;
	
	function UserByRoleColumn($label, $help=null){
		SelectColumn::SelectColumn($label, array(), $help);
	}
	
	public function setRole($role){
		$this->role = $role;
	}
	
	public function renderForm($formID){
		if(strlen($this->data)){
			$hidden = new HiddenColumn($this->data, 'int');
			$hidden->name = $this->name;
			if(authority_group('user_admin')){
				$help = tt('You can edit user information in <a href="%s">Edit User page</a>.');
				$this->help = sprintf($help, SECTION_URI.Q.'user_edit/'.$this->data.'/redirect/mrplere_translator');
			}
			return $hidden->renderForm($formID);
		}else{
			$this->option = $this->getResidualTranslator();
			if(count($this->option)){
				$help = tt('You can add new user in <a href="%s">Add User page</a>.');
				$this->help = sprintf($help, SECTION_URI.Q.'user_write');
				return SelectColumn::renderForm($formID);
			}else{
				$message = tt('No user has permission to be a Translator. ');
				$message.= tt('Please create a user with Translator Permission before adding a new translator.');
				$redirect = '
				<script>
					alert("'.$message.'");
					window.location.href = "'.SECTION_URI.Q.'user_write/redirect/mrplere_translator_write";
				</script>';
				die($redirect);
			}
		}
	}
	
	function getResidualTranslator(){
		$uid = userinfo_get_uid_by_role('mrplere_translator');
		$clause = 'WHERE section='.SECTION;
		$translatorUID = db_select_single_column('mrplere_translator', 'uid', $clause);
		$residualUID = array_diff($uid, $translatorUID);
		if(count($residualUID)){
			$clause = 'WHERE id='.join(' OR id=', $residualUID);
			return db_select_single_column('users', 'login_name', $clause);
		}else{
			return array();
		}
	}
}
?>
