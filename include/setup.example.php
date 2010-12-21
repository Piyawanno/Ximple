<?php
///	@file
/// This file save the access information of Ximple.


// Ximple 0.4 supports mysql, pgsql, sqlite.
define('DB_TYPE','sqlite');

// Database-Configurations (SQLite does not need these configurations)
define('DB_USER','login name for database');
define('DB_NAME','your database name');
define('DB_HOST','your database host example localhost');
define('DB_PASS','database password');

// Ximple 0.4 supports  en, th, de.
define(DEFAULT_LANGUAGE,'th');

// Please put slash ('/') at the end of this parameters.
// example: 'http://mydomain/' is a valid parameter but 'http://mydomain' is a invalid parameter
// example: '/my/root/path/' is a valid parameter but '/my/root/path' is a invalid parameter
define('ROOT_URI','http://mydomain/xblc/install/');
define('ROOT_PATH','/var/www//xblc/install/');

// User upload file size
define('MAX_UPLOADED_FILE_SIZE', 500e3);
define('MAX_USER_SPACE_SIZE', 100e6);

// Email configuration for sending mail.
define('SITE_MAIL', 'info@mydomain.net');
define('SMTP_SERVER', 'smtp.mydomain.net:25');
define('SMTP_LOGIN', 'Your login name for SMTP Server');
define('SMTP_PASSWD', 'SMTP password');
?>
