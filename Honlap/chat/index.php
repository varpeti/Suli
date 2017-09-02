<?php

session_start();

//Ha megvannak az adatok előrébb lép.
if (isset($_SESSION['nev']))
{
	header("Location: szoba.php");
	exit("index");
}

if(isset($_POST["s_nev_sub"]))
{
	$_SESSION['nev']=$_POST["s_nev"];

	header("Location: szoba.php");
	exit();

}

require_once('nev_input.html');

?>