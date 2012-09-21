<?php
require_once(INCLUDE_PATH.'class/column/SelectColumn.class.inc');

class UserByRoleColumn extends SelectColumn{
	private $role;
	
	function UserByRoleColumn($label, $role, $help=null){
		SelectColumn::SelectColumn($label, array(), $help);
		$this->role = $role;
	}
	
	public function renderForm($formID){
		if(strlen($this->data)){
			$hidden = new HiddenColumn($this->data, 'int');
			$hidden->name = $this->name;
			if(authority_group('user_admin')){
				$help = tt('You can edit user information in <a href="%s">Edit User page</a>.');
				$this->help = sprintf($help, SECTION_URI.Q.'user_edit/'.$this->data.'/redirect/'.mm());
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
					window.location.href = "'.SECTION_URI.Q.'user_write/redirect/'.mm().'";
				</script>';
				die($redirect);
			}
		}
	}
	
	function getResidualTranslator(){
		if(is_array(cc($this->role)) and count(cc($this->role))){
			$clause = 'WHERE id NOT IN ( SELECT '.$this->name.' FROM '.$this->tableName.') AND ';
			$clause.= 'id IN (SELECT users FROM map WHERE groups IN('.join(', ', cc($this->role)).'))';
			return db_select_single_column('users', 'login_name', $clause);
		}
	}
}
?>
