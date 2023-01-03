<?php
	$file = $_GET['p'];

	include 'l.php';

	$u = $_GET['u'];
	$t = $_GET['t'];

	if (auth($u, $t) != 0)
	{
		echo "Auth error";
		exit(1);
	}

	include 'u.php';
	$d = get_user_dir($u);
	$fpath = "$d/$file";

	if (file_exists($fpath)) {
		header('Content-Description: File Transfer');
		header('Content-Type: application/octet-stream');
		header('Content-Disposition: attachment; filename='.basename($fpath));
		header('Content-Transfer-Encoding: binary');
		header('Expires: 0');
		header('Cache-Control: must-revalidate, post-check=0, pre-check=0');
		header('Pragma: public');
		header('Content-Length: '.filesize($fpath));
		header('Modification-Time: '.gmdate('D, d M Y H:i:s \G\M\T', filemtime($fpath)));
		ob_clean();
		flush();
		readfile($fpath);
		exit;
	}
?>
