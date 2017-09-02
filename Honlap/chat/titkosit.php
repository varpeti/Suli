<?php 

$hhhh="Nagyon nagyon kell vigyazn a titkos jelszavakra, ezert ide irok egyet: a==(sa6fr34=(HIAg56hO<{NIA=9LKr)";



function titkosit($adat,$kulcs)
{
	return base64_encode(openssl_encrypt($adat,'AES-256-CBC',$GLOBALS['hhhh'],0,$kulcs));
}

function dekodol($adat,$kulcs)
{
	return openssl_decrypt(base64_decode($adat),'AES-256-CBC',$GLOBALS['hhhh'],0,$kulcs);
}


?>