<?php

	function test()
	{
		// Check connection
		if ($conn->connect_error) {
			die("Connection failed: " . $conn->connect_error);
		}
		echo "Connected successfully";
		mysqli_close($conn);
		$conn = mysqli_connect($hostname, 'j70492510_tv', '34.+[8-(Wn.M', 'j70492510_vc');
	}

	function connect_to_db()
	{
		// define(PRINT_QUERIES, 1);
		include '../include/db_mysql.php';
		
		$hostname = ini_get("mysqli.default_host");
		$username = ini_get("mysqli.default_user");
		$password = ini_get("mysqli.default_pw");
		$database = "";
		$port = ini_get("mysqli.default_port");
		$socket = ini_get("mysqli.default_socket");

		$db = new Db('j70492510_vc', $hostname, 'j70492510_tv', '34.+[8-(Wn.M', 'j70492510_vc');

		return $db;
	}

	function auth($u, $t)
	{
		$db = connect_to_db();

		$tbl_name = "users";
		if (!$db->table_exists($tbl_name))
		{
			echo "Table does not exist. Create<br>";
			$rq = $db->query("CREATE TABLE IF NOT EXISTS $tbl_name (
				id INT PRIMARY KEY NOT NULL AUTO_INCREMENT,
				name VARCHAR(255),
				token VARCHAR(255)
				)
			", true);
			if (!$rq)
				return -1;
		}

		if (!isset($u) || strlen( $u ) === 0)
			return 1;
		else if (!isset($t))
			return 2;
		else
		{
			$ud = $db->query_firstrow("SELECT * FROM $tbl_name WHERE name = '$u';");
			if (!$ud)
			{
				$mdt = md5($t);
				if (!$db->query_firstrow("INSERT INTO $tbl_name (name, token) VALUES ('$u', '$mdt')"))
					return 3;
			}
			else
			{
				if ($ud)
					if ($ud['token'] != md5($t))
						return 4;
			}
			return 0;
		}
	}
?>
