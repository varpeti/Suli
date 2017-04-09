<meta http-equiv="refresh" content="15">
<?php

$db = new SQLite3('sqlitedb.db');

if(isset($_POST["s_gomb"]))
{
	$uzenet = $_POST["s_szoveg"];
	$ido = date("Y.m.d h:i:s");
	$db->exec("INSERT INTO uzenetek (uzenet, ido) VALUES ('$uzenet', '$ido')" );
	$db->exec("DELETE FROM uzenetek WHERE ROWID IN (SELECT ROWID FROM uzenetek ORDER BY ROWID DESC LIMIT -1 OFFSET 20)");

}

require_once('chat_begin.html');

$result = $db->query('SELECT uzenet, ido FROM uzenetek');
while($sor = $result->fetchArray()){
	echo $sor[1];
	echo " ";
	echo $sor[0];
	echo "<br>";
}

require_once('chat_input.html');
require_once('chat_end.html');
?>