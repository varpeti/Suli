<?php

$db = new SQLite3('sqlitedb.db');

$db->exec('CREATE TABLE IF NOT EXISTS uzenetek (uzenet STRING, ido STRING)');

require_once('main.php');

?>