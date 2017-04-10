<?php

$cnev = 'nev';

if (isset($_COOKIE[$cnev]))
{ // Chat rész

	$db = new SQLite3('sqlitedb.db');
	$db->exec('CREATE TABLE IF NOT EXISTS uzenetek (uzenet STRING, nev STRING, ido STRING)');
	require_once('chat.php');

	if(isset($_POST["s_gomb"]))
	{
		$uzenet = $_POST["s_szoveg"]; 
		$nev = $_COOKIE[$cnev];
		ujuzenet($uzenet,$nev,$db);

		$_POST["s_szoveg"]="";
	}

	megjelenit($db);

} else
{ // Login rész
	if(isset($_POST["s_gnev"]))
	{
		$nev = $_POST["s_nev"];
		setcookie('nev', $nev, time() + 24*60*60*300, '/');
		header("Location: index.php");
		exit;

	}
	require_once('nev_input.html');
}

?>