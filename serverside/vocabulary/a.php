<?php

	include 'l.php';
	switch (auth($_GET['u'], $_GET['t']))
	{
		case 0:
			echo 'Authenticated successfully';
			$_SESSION['u'] = $_GET['u'];
			break;
		case 1:
			echo "No user name provided<br>";
			break;
		case 2:
			echo "No token provided<br>";
			break;
		case 3:
			echo "Error while registering<br>";
			break;
		case 4:
			echo "Auth error<br>";
			break;
		case -1:
			echo "Error during DB initialization";
			break;
		default:
			echo "Unknown error<br>";
			break;
	}
?>
