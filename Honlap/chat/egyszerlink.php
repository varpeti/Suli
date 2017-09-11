<?php

session_start();

$token = $_GET['q']; // Url beolvasás

require_once("titkosit.php");

if( strlen($token)>=32 )
{
	$szoba = '';
	$kod = '';
	$ok = false;
	
	$file = "../../private_html/chat/linkek.lnk";
	
	$lines = file($file); // file beolvasás
	
	$f = fopen($file,"w");
	
	flock($f,LOCK_EX); //lock
	
	// Végigmegy az összes tokenen a fileba.
	for( $i = 0; $lines[$i]; $i++ )
	{		
		$dat = dekodol(strtok($lines[$i],"¶"),$token); // {token¶szoba¶pw}¶ido
		$ido = strtok("¶");
		$tok = strtok($dat,"¶");
		if (time()-$ido<60*60*24) // Ha nem járt le.
		{
			if( $tok === $token) // Ha megvan.
			{
				$szoba = strtok("¶"); 
				$kod= strtok("¶");
				if (strlen($szoba)>=1) {$ok = true; }
			}
			else // Visszaírjuk ami nem egyezik.
			{
				fwrite($f,$lines[$i]);
			}
		}

	}
	
	flock($f,LOCK_UN); //unlock
	
	fclose($f);
	
	if( $ok ) //ha van
	{
		$_SESSION['szoba']=trim($szoba);
		$_SESSION['szoba_pw']=trim($kod);
	
		header("Location: index.php");
		exit();
	}
	else // Ha nincs ilyen token.
	{
		$_SESSION['szoba']='';
		$_SESSION['szoba_pw']='';

		header("Location: index.php");
		exit();
	}
}



function ujlink($szoba, $kod)
{
	$token = md5(uniqid(rand(),1));

	$file = "../../private_html/chat/linkek.lnk";
	
	$f = fopen($file,"a");
	
	flock($f,LOCK_EX); //lock

	require_once("titkosit.php");
	fwrite($f,titkosit($token."¶".$szoba."¶".$kod,$token)."¶".time()."\n");

	flock($f,LOCK_UN); //unlock
	
	fclose($f);
	
	$cwd = substr($_SERVER['PHP_SELF'],0,strrpos($_SERVER['PHP_SELF'],"/"));
	
	
	return "Egyszer hasznalhato URL: <a href='http://".$_SERVER['HTTP_HOST']."$cwd/egyszerlink.php?q=$token'>http://".$_SERVER['HTTP_HOST']."$cwd/egyszerlink.php?q=$token</a>";

}

?>