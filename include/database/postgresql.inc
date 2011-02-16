<?php
/// @file
/// This file provides functions for database handling with PostgreSQL (support >= PostgreSQL-8.2).
/// The functions are extended with caching system and transaction.
/// However, developers are not free to send any query to database due to the security.
/// Queries are generated with query-templates and given array of data.
/// This method does not simplify the development in all cases but is more secure.

/// Internal global variables for postgresql-database-tool.
/// These variables should not be used outside this file.

global $db_connect, $db_transaction, $db_query_number;
global $db_query_all_number, $db_query_count;
global $db_query_all_count, $db_column;

$db_connect = null;
$db_transaction = false;
$db_query_number = array();
$db_query_all_number = 0;
$db_query_count = array();
$db_query_all_count = 0;
$db_column = array();

function db_init(){ //O.D. : DB_NAME is nowed used when connect
	global $db_connect;
	global $db_transaction;
//	@$db_connect = mysql_connect(DB_HOST,DB_USER,DB_PASS) or error_db_connect();
	$conn_string = 'host='.DB_HOST.' dbname='.DB_NAME.' user='.DB_USER.' password='.DB_PASS;
	@$db_connect = pg_connect($conn_string) or error_db_connect();
//	@mysql_db_query(DB_NAME, 'START TRANSACTION;', $db_connect) or error_db_log($query, mysql_error());
	@pg_query($db_connect, 'START TRANSACTION') or error_db_log($query, pg_last_error());
	$db_transaction = true;
}

function db_select_single_column($table, $column, $clause=null, $has_id=true, $cachable=true){
	if($column != 'id' and $has_id){
		$pre_data = db_select($table, array('id', $column), $clause, $cachable);
	}else{
		$pre_data = db_select($table, array($column), $clause, $cachable);
	}
	$data = array();
	$i = 0;
	foreach($pre_data as $key=>$value){
		if($has_id) $data[$key] = $value[$column];
		else $data[$i] = $value[$column];
		$i++;
	}
	return $data;
}

function db_select($table, $columns, $clause=null, $cachable=true){ //O.D. edited
	global $db_connect;
	$table = DB_TABLE_PREFIX.$table;
	$query = 'SELECT '.join(', ', $columns).' FROM '.$table.' '.$clause;
	if($cachable){
		$cache_file = cache_get_db_file($table, $query);
		if(cache_check_db($cache_file)){
			return cache_get_db_data($cache_file);
		}
	}
	@$state = pg_query($db_connect, $query) or error_db_log($query, pg_last_error());
	$data = array();
	while($row = pg_fetch_assoc($state)){
		if(count($columns) != count($row)){
			error_syslog('Error by fetching data from database. Column number mismatch.');
		}
		foreach($row as $key=>$value){
			if(is_string($value)) $row[$key] = stripslashes($value);
		}
		if(isset($row['id'])){
			$data[$row['id']] = $row;
		}
		else $data[] = $row;
	}
	if($cachable) cache_save_db($table, $query, $data);
	db_increase_query($table);
	return $data;
}

function db_get_rows_number($table, $clause=null){
	global $db_connect;
	$table = DB_TABLE_PREFIX.$table;
	$query = 'SELECT COUNT(id) as rows_number FROM '.$table.' '.$clause;
	$cache_file = cache_get_db_file($table, $query);
	if(cache_check_db($cache_file)){
		return cache_get_db_data($cache_file);
	}
	@$state = pg_query($db_connect, $query) or error_db_log($query, pg_last_error());
	$row = pg_fetch_assoc($state);
	cache_save_db($table, $query, $row['rows_number']);
	db_increase_query($table);
	return $row['rows_number'];
}

function db_count_group_by($table, $column, $where=null, $cachable=true){
	global $db_connect;
	$table = DB_TABLE_PREFIX.$table;
	if(strlen($where)) $where = 'WHERE '.$where;
	$query = "SELECT $column, COUNT($column) as number FROM $table $where GROUP BY $column";
	$cache_file = cache_get_db_file($table, $query);
	if($cachable){
		if(cache_check_db($cache_file)){
			return cache_get_db_data($cache_file);
		}
	}
	@$state = pg_query($db_connect, $query) or error_db_log($query, pg_last_error());
	$data = array();
	while($row = pg_fetch_assoc($state)){
		$row[$column] = stripslashes($row[$column]);
		$data[] = $row;
	}
	if($cachable) cache_save_db($table, $query, $data);
	db_increase_query($table);
	return $data;
}

function db_increase_query($table){
	global $db_query_number;
	global $db_query_all_number;
	$table = DB_TABLE_PREFIX.$table;
	if(isset($db_query_number[$table])) $db_query_number[$table]++;
	else $db_query_number[$table] = 0;
	$db_query_all_number ++;
}

function db_start_count($table=null){
	global $db_query_number;
	global $db_query_all_number;
	global $db_query_count;
	global $db_query_all_count;
	$table = DB_TABLE_PREFIX.$table;
	$concurency = false;
	if($table){
		if(isset($db_query_count[$table])) $concurency = true;
		if(isset($db_query_number[$table])) $db_query_count[$table] = $db_query_number[$table];
		else $db_query_count[$table] = 0;
	}else{
		if($db_query_all_count) $concurency = true;
		$db_query_all_count = $db_query_all_number;
	}
	
	if($concurency and is_develop()){
		notify_add_warning(tt('Concurrency problem for db_start_count : '.$table));
	}
}

function db_is_new_query($table=null){
	global $db_query_number;
	global $db_query_all_number;
	global $db_query_count;
	global $db_query_all_count;
	$table = DB_TABLE_PREFIX.$table;
	if($table){
		$is_new =  $db_query_count[$table] < $db_query_number[$table];
		unset($db_query_count[$table]);
	}else{
		$is_new = $db_query_all_count < $db_query_all_number;
		$db_query_all_count = 0;
	}
	return $is_new;
}

function db_get_query_number(){
	global $db_query_all_number;
	return $db_query_all_number;
}

function db_update($table, $data, $id){
	$id = (int) $id;
	if(empty($id)) error_syslog('Update database error.');
	db_update_many($table, $data, 'id='.$id);
}

/// Not secure, use with care.
function db_update_many($table, $data, $where){
	$table = DB_TABLE_PREFIX.$table;
	$value_set = '';
	foreach($data as $key => $value){
		if(is_string($value)  or $value==null) $value_set .= $key."='".addslashes($value)."', ";
		else $value_set .= $key.'='.$value.', ';
	}
	$value_set = substr($value_set,0, -2);
	$query = 'UPDATE '.$table.' SET '.$value_set.' WHERE '.$where;
	db_modify($table, $query);
}


function db_insert($table, $data){//Need new function Postgre has no insert_id
	$table = DB_TABLE_PREFIX.$table;
	$cols = join(',', array_keys($data));
	$value_set = '';
	foreach($data as $key => $value){
		if(is_string($value) or $value==null) $value_set .= "'".addslashes($value)."', ";
		else $value_set .= $value.', ';
	}
	$value_set = substr($value_set,0, -2);
	$query = 'INSERT INTO '.$table.'('.$cols.') VALUES('.$value_set.')';
	db_modify($table, $query);
	return mysql_insert_id();
}

function db_drop($table, $id){
	$table = DB_TABLE_PREFIX.$table;
	$id = (int) $id;
	if(empty($id)) error_syslog('Error by dropping data from database.');
	$query = 'DELETE FROM '.$table.' WHERE id='.$id;
	db_modify($table, $query);
}

/// Not secure, use with care.
function db_drop_many($table, $where){
	$table = DB_TABLE_PREFIX.$table;
	$query = 'DELETE FROM '.$table.' WHERE '.$where;
	db_modify($table, $query);
}

function db_exist_table($table){
	global $db_connect;
	$table = DB_TABLE_PREFIX.$table;
	$tables = pg_field_table(DB_NAME, $db_connect); //replace mysql_list_tables, alternative required
	while($row = pg_fetch_row($tables)){
		if($row[0] == $table) return true;;
	}
	return false;
}

function db_exist_column($table, $column){
	global $db_connect, $db_column;
	if(isset($db_column[$table])){
		$columns = $db_column[$table];
	}else{
		$columns = array();
		$table = DB_TABLE_PREFIX.$table;
		$state = mysql_list_fields(DB_NAME, $table, $db_connect);//required alternate replace
		$number = pg_num_fields($state);
		for($i = 0; $i < $number; $i++){
			$columns[] = pg_field_name($state, $i);
		}
		$db_column[$table] = $columns;
	}
	return in_array($column, $columns);
}

function db_create_table($table, $columns){
	$table = DB_TABLE_PREFIX.$table;
	$query = 'CREATE TABLE '.$table.'( ';
	$query.= 'id int unsigned  auto_increment, ';
	foreach($columns as $column){
		$query .= $column.', ';
	}
	$query.= 'PRIMARY KEY (id)) CHARACTER SET utf8;';
	db_modify($table, $query);
}

function db_get_tables(){
	global $db_connect;
	$state = mysql_list_tables(DB_NAME, $db_connect);//required alternate func.
	$tables = array();
	while($row = pg_fetch_row($state)){
		$tables[] = $row[0];
	}
	return $tables;
}

function db_modify($table, $query){
	global $db_connect;
	@$state = pg_query($db_connect, $query) or error_db_log($query, pg_last_error());
	cache_clear_db($table);
	db_increase_query($table);
}

function db_get_type($type){
	$typeMap = array(
		'int' => 'INT',
		'real' => 'DECIMAL',
		'char' => 'VARCHAR(250)',
		'shorttext' => 'TEXT',
		'text' => 'MEDIUMTEXT',
		'date' => 'DATE',
		'timestamp' => 'TIMESTAMP',
		'array' => 'TEXT',
	);
	return $typeMap[$type];
}

function db_close(){
	global $db_connect;
	global $db_transaction;
	if($db_connect and $db_transaction){
		pg_query($db_connect, 'COMMIT;');// semi collon?
	}
	if($db_connect){
		pg_close($db_connect);
	}
}

function db_rollback(){
	global $db_connect;
	global $db_transaction;
	if($db_transaction){
		pg_query($db_connect, 'ROLLBACK;'); // semi collon?
	}
	if($db_connect){
		pg_close($db_connect);
	}
}

?>