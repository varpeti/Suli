<?php
session_start();

//Adatok meglétének ellenörzése
if (!isset($_SESSION['nev'])) 
{
	header("Location: index.php");
	exit;
}

if (!isset($_SESSION['szoba']))
{
	header("Location: szoba.php");
	exit;
}

//Vissza, kilépés bisztosítása
require_once("viki.php"); 
visszakilepes();

require_once("titkosit.php");
require_once("egyszerlink.php");

ujuzenet();

if (file_exists("../../private_html/chat/szobak/" . $_SESSION['szoba'] . ".szoba") and $db= fopen("../../private_html/chat/szobak/" . $_SESSION['szoba'] . ".szoba", "r")) 
{
	//Jelszó vizsgálata
	$sor = fgets($db);
	if (!isset($_SESSION['szoba_pw']) or $_SESSION['szoba_pw'] != dekodol($sor,$_SESSION['szoba_pw']))
	{
		if ($_SESSION['szoba']=='public')
		{
			$_SESSION['szoba_pw']="PublicPublicPubl";
		}
		else
		{
			unset($_SESSION['szoba']);
			unset($_SESSION['szoba_pw']);

			header("Location: szoba.php");
			exit;
		}
	}

	//Chat és az üzenetek megjelenítése
	require_once('chat_begin.html');

	echo "<div id='header'><h1 style='padding-bottom: 40px; text-align: center'>" . $_SESSION['szoba'] . "</h2></div>\n<div id='CONTENT'>\n\t<div id='TEXT'>";

	require_once('chat_input.html');

	//Üzenetek olvasása
	while ( ($l = fgets($db)) !== false)
	{ 
		$ki = strtok(dekodol($l,$_SESSION['szoba_pw']),"¶");
		$mikor = sec2time(strtok("¶"));
		$mit = strtok("¶");
		echo "\n\t\t<div>"; 
		echo "\n\t\t\t<p style='text-align: left'>" . $ki . ": " . $mit . "</p>";
		echo "\n\t\t\t<p style='text-align: right'>" . $mikor . "</p>";
		echo "\n\t\t</div>"; 
	}
	fclose($db);

} else { // Csak akkor ha az új szobára lett kattnintva.

	ujszoba();
	
}

require_once('chat_end.html');


//Függvények

function sec2time($seconds)
{
	$days = floor($seconds / (60 * 60 * 24));

	$divisor_for_hours = $seconds % (60 * 60 * 24);
	$hours = floor($divisor_for_hours / (60 * 60));

	$divisor_for_minutes = $divisor_for_hours % (60 * 60);
	$minutes = floor($divisor_for_minutes / (60));

	$divisor_for_seconds = $divisor_for_minutes % (60);
	$seconds = ceil($divisor_for_seconds);

	$ido = $hours . "." . $minutes . "." . $seconds;
	return $ido;
}

function ujuzenet()
{
	if(isset($_POST["s_kuld"]))
  	{ 
  		$nev = $_SESSION['nev']; 
		$uzenet = $_POST["s_szoveg"];  
		$sec = time();

		// ne lehessen HTML vagy Javascript injection
		$nev = htmlspecialchars($nev);
		$uzenet = htmlspecialchars($uzenet);
		
		if ($uzenet=="/help") {
			$uzenet="Parancsok:<br>/help - kiirja ezt.<br>/del - torli a szobat.<br>/link - ad egy linket a szobahoz.<br>/img pelda.jpg - megjeleniti a kepet.";
		}
		elseif ($uzenet=="/del") { // Törli a szobát

			unlink("../../private_html/chat/szobak/" . $_SESSION['szoba'] . ".szoba");

			unset($_SESSION['szoba']);
			unset($_SESSION['szoba_pw']);
			exit('<meta http-equiv="refresh" content="1">');
		}
		elseif ($uzenet=="/link") {
			$uzenet=ujlink($_SESSION['szoba'],$_SESSION['szoba_pw']); // Uj egyszer hasznalhato link
		}
		elseif ( strpos($uzenet,"/img ") !== false ) {
			$uzenet="<img src=".substr($uzenet,5).">";
		}
  
		$_POST["s_szoveg"]=""; 

		$uzenet = titkosit($nev . "¶" . $sec . "¶" . $uzenet,$_SESSION['szoba_pw'])."\n";

		//Berakja az üzenetet a file elejére, a header mögé.
		$file = file("../../private_html/chat/szobak/" . $_SESSION['szoba'] . ".szoba");
		$header = array_shift($file);  // kiszedi az első sort
		array_unshift($file, $uzenet); // berakja az üzenetet
		array_unshift($file, $header); // vissza a header

		$db = fopen("../../private_html/chat/szobak/" . $_SESSION['szoba'] . ".szoba", 'w'); // Visszaírj az egész fájlt.
		fwrite($db, implode("", $file));     
		fclose($db);
 	}
}

function ujszoba()
{
	//spacek kiszedése
	$_SESSION['szoba'] = str_replace(' ', '', $_SESSION['szoba']);

	//szoba létrehozása
	$db= fopen("../../private_html/chat/szobak/" . $_SESSION['szoba'] . ".szoba", "w");
	$megj = false;
	if(!isset($_SESSION['szoba_pw'])) 
	{
		$_SESSION['szoba_pw'] = substr(crypt(openssl_random_pseudo_bytes(16)), -16); // Megbízható 16 karakteres jelszó.
		$megj=true;
	} 

	fwrite($db,titkosit($_SESSION['szoba_pw'],$_SESSION['szoba_pw'])."\n");
	fclose($db);

	//Chat és az üzenetek megjelenítése
	require_once('chat_begin.html');

	print("<div id='header'><h1 style='padding-bottom: 40px; text-align: center'>" . $_SESSION['szoba'] . "</h2></div>\n<div id='CONTENT'>\n\t<div id='TEXT'>");
	if ($megj) { print("<br>A szoba [jelszo]: [".$_SESSION['szoba_pw']."]"); }
	print("<br>".ujlink($_SESSION['szoba'],$_SESSION['szoba_pw']));
	print("Elerheto parancsok: /help");
}

?>