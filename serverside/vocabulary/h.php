<?php

include 'l.php';

$u = $_GET['u'];
$t = $_GET['t'];

if (auth($u, $t) != 0)
{
	echo "Auth error";
	exit(1);
}

include 'u.php';

upload_file($u);

function upload_file($u){
	$d = get_user_dir($u);
	$fpath = "$d/$file";
	$uploadTo = "$d/";
	$allowFileType = array('jpg','png','jpeg','gif','pdf','doc','txt');
	$fileName = $_FILES['file']['name'];
	$tempPath=$_FILES["file"]["tmp_name"];
    echo "Temp path: $tempPath\n";
	$basename = basename($fileName);
	$originalPath = $uploadTo.$basename;
	$fileType = pathinfo($originalPath, PATHINFO_EXTENSION);
	if(!empty($fileName)){
	
	   if(in_array($fileType, $allowFileType)){
		 // Upload file to server
		 if(move_uploaded_file($tempPath,$originalPath)){
			echo $fileName." has been uploaded successfully";
		   // write here sql query to store image name in database
		  
		  }else{
			echo 'File Not uploaded ! try again';
		  }
	  }else{
		 echo $fileType." file type not allowed";
	  }
   }else{
	 echo "Please Select a file";
   }
}

?>
