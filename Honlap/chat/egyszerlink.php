<?php

session_start();

$token = $_GET['q']; // Url beolvasás

if( strlen($token)>=32 )
{
	$szoba = '';
	$kod = '';
	
	$file = "../../private_html/chat/linkek.lnk";
	
	$lines = file($file); // file beolvasás
	
	$f = fopen($file,"w");
	
	flock($f,LOCK_EX); //lock
	
	// Végigmegy az összes tokenen a fileba.
	for( $i = 0; $lines[$i]; $i++ )
	{		
		
		if( ($tk = strtok($lines[$i],"¶")) == $token )
		{
			$szoba = strtok("¶"); 
			$kod= strtok("¶"); 
		}
		else // Visszaírjuk ami nem egyezik.
		{
			fwrite($f,$lines[$i]);
		}
	}
	
	flock($f,LOCK_UN); //unlock
	
	fclose($f);
	
	if( $szoba!='' ) //ha van
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



function uj($szoba, $kod)
{
	$token = md5(uniqid(rand(),1));

	$file = "../../private_html/chat/linkek.lnk";
	
	$f = fopen($file,"a");
	
	flock($f,LOCK_EX); //lock
	fwrite($f,$token."¶".$szoba."¶".$kod."\n");
	flock($f,LOCK_UN); //unlock
	
	fclose($f);
	
	$cwd = substr($_SERVER['PHP_SELF'],0,strrpos($_SERVER['PHP_SELF'],"/"));
	
	
	return "Egyszer hasznalhato URL: <a href='http://".$_SERVER['HTTP_HOST']."$cwd/egyszerlink.php?q=$token'>http://".$_SERVER['HTTP_HOST']."$cwd/egyszerlink.php?q=$token</a>";

}

?>