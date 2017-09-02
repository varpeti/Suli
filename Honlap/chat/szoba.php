<?php 

session_start();

//Adatok meglétének ellenörzése, vissza, előre navigálás
if (!isset($_SESSION['nev']))
{
	header("Location: index.php");
	exit;
}

if (isset($_SESSION['szoba']))
{
	header("Location: chat.php");
	exit("index");
}

//Vissza, kilépés bisztosítása
require_once("viki.php");
visszakilepes();

require_once("titkosit.php");

if(isset($_POST["s_szoba_sub"]) and !empty($_POST["s_szoba"]) and !empty($_POST["s_szoba_pw"]))
{

	$_SESSION['szoba']=($_POST["s_szoba"]);
	$_SESSION['szoba_pw']=$_POST["s_szoba_pw"]; //Nem túl szép így tárolni, de ez nem a felhasználó személyes jelszava.

	header("Location: chat.php");
	exit;	
}

if(isset($_POST["s_szoba_uj"]) and !empty($_POST["s_szoba"]))
{

	$_SESSION['szoba']=($_POST["s_szoba"]);
	unset($_SESSION['szoba_pw']); // Nem rögzít jelszót így, ha nem létezik ilyen szoba, újat csinál.

	header("Location: chat.php");
	exit;	
}
	
require_once('szoba_begin.html');

echo 'Udv ' . $_SESSION['nev'] . '! Elerheto szobak: ';
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


require_once('szoba_input.html');
require_once('szoba_end.html');
			
?>