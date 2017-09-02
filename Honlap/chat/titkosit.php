<?php 

$hhhh="a==(sa6fr34=(H#A";

function titkosit($adat,$kulcs)
{
	return base64_encode(openssl_encrypt($adat,'AES-256-CBC',$kulcs,0,$GLOBALS['hhhh']));
}

function dekodol($adat,$kulcs)
{
	return openssl_decrypt(base64_decode($adat),'AES-256-CBC',$kulcs,0,$GLOBALS['hhhh']);
}

?>