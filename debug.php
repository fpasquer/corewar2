#!/usr/bin/php
<?php
$cycle = 0;
$breaks = 0;
if ($argv[2] == "-b")
{
	$breaks = 1;
}
if ($argv[2])
{
	if($breaks == 1)
		$i = 3;
	else
		$i = 2;
	$champ = '';
	while ($argv[$i])
	{
		$champ .= ' champ/'.$argv[$i].'.cor ';
		$i++;
	}
}
$var = "";
while($cycle <= $argv[1])
{
echo "===============   CYCLE ".$cycle."  ================\n";
$var = shell_exec('./corewar -d '.$cycle.$champ.' && ./corewar_zaz -d '.$cycle.$champ.' > mem.txt && diff mem.txt dump_memory.txt');
$var = preg_replace("/^(I{1})(.+)(\n(.+))+/", "", $var);
$var = preg_replace("/\t(.+)[ \t\n+]/", "", $var);
$var = trim($var);
$var = preg_replace("/^([*]{1})(.+)(\n(.+))+/", "", $var);
$var = preg_replace("/\t(.+)[ \t\n+]/", "", $var);
if ($var != "")
{
	echo $var;
	echo "\n===============   FIN CYCLE Num ".$cycle."   ===============\n";
	if ($breaks == 1)
		break;
}
$cycle++;
}
?>