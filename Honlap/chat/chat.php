<?php

function ujuzenet ($uzenet, $nev, $db)
{
	$db = new SQLite3('sqlitedb.db');
	$ido = date("h:i:s");

	$db->exec("INSERT INTO uzenetek (uzenet, nev, ido) VALUES ('$uzenet', '$nev', '$ido')" );
	$db->exec("DELETE FROM uzenetek WHERE ROWID IN (SELECT ROWID FROM uzenetek ORDER BY ROWID DESC LIMIT -1 OFFSET 20)");

}

function megjelenit($db)
{
	require_once('chat_begin.html');
			
	$result = $db->query('SELECT uzenet, nev, ido FROM uzenetek');
	while($sor = $result->fetchArray()){
		echo "<div data-role='header'>\n\t<div data-role='main'>";
		echo $sor[2];
		echo "	|	";
		echo $sor[1];
		echo ":	";
		echo $sor[0];
		echo "\n</div>\n";
	}
		
	require_once('chat_input.html');
	require_once('chat_end.html');
}
			
?>