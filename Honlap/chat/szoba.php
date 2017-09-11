<?php 

session_start();

//Adatok meglétének ellenörzése, vissza, előre navigálás
if (!isset($_SESSION['nev']))
{
	header("Location: index.php");
	exit;
}

if (isset($_SESSION['szoba']) and !empty($_SESSION['szoba']))
{
	header("Location: chat.php");
	exit("index");
}

//Vissza, kilépés bisztosítása
require_once("viki.php");
visszakilepes();

require_once("titkosit.php");

if(isset($_POST["s_szoba_sub"]) and !empty($_POST["s_szoba"]))
{

	$_SESSION['szoba']=otlenites(htmlspecialchars($_POST["s_szoba"], ENT_QUOTES, 'UTF-8')); // ne lehessen HTML vagy Javascript injection
	if (!empty($_POST["s_szoba_pw"]))
	{
		$_SESSION['szoba_pw']=otlenites($_POST["s_szoba_pw"]); //Nem túl szép így tárolni, de ez nem a felhasználó személyes jelszava.
	}
	else
	{
		unset($_SESSION['szoba_pw']);
	}

	header("Location: chat.php");
	exit;	
}
	
require_once('szoba_begin.html');

echo 'Udv ' . $_SESSION['nev'] . '!<br>Elerheto szobak: ';
foreach(glob('../../private_html/chat/szobak/*') as $file) {
	
	
	if (time()-filemtime($file)>60*60*24) // Egy nap után törlődik minden szoba
	{
		// törli a régi szobákat.
		unlink($file);
	}
	else
	{
		//kiírj az elérhető szobákat
		$file = substr($file, 31,-6);
		if ($file!="public") {echo $file . ", ";}
	}
}

if (!file_exists("../../private_html/chat/szobak/public.szoba")) //Public szoba készítés ha nincs.
{
	$db= fopen("../../private_html/chat/szobak/public.szoba", "w");
	fwrite($db,titkosit("PublicPublicPubl","PublicPublicPubl")."\n");
	fclose($db);
}
echo 'public';
echo '<br>Uj szoba letrehozasahoz, csak irj be egy uj szoba nevet. Ha nem adsz meg jelszot, general egyet.<br>24 oraig nem hasznalt szobak, es linkek torlodnek!';


require_once('szoba_input.html');
require_once('szoba_end.html');
			
?>