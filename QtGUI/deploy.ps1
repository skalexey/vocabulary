# Check if the script is running with elevated privileges
function Test-Admin {
	$currentUser = New-Object Security.Principal.WindowsPrincipal $([Security.Principal.WindowsIdentity]::GetCurrent())
	$currentUser.IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
}

# Prompt for elevation if not already running as administrator
if (-not (Test-Admin)) {
	$scriptPath = $MyInvocation.MyCommand.Path
	Start-Process powershell.exe -Verb RunAs -ArgumentList "-File $scriptPath"
	Exit
}

$executable_name = "QtGUIApp"
$app_folder = "vocabulary\Qt"
$deploy_dir = $Env:PROGRAMFILES + "\" + $app_folder
# Check if the directory already exists
if ($args.Count -ge 1) {
	$build_type = $args[0].ToLower()
} else {
	$build_type = "release"
}

Write-Host "Build type to deploy: $build_type"

# Check if the directory already exists
if (-not (Test-Path -Path $deploy_dir -PathType Container)) {
    # If not, create the directory
    New-Item -ItemType Directory -Path $deploy_dir -Force
    Write-Host "Directory created: $deploy_dir"
} else {
    Write-Host "Deploy directory already exists: '$deploy_dir'"
}

# Specify the source directory based on the argument
$build_dir = Join-Path "Build-cmake" ($build_type.Substring(0, 1).ToUpper() + $build_type.Substring(1))

# Check if the source directory exists
if (Test-Path -Path $build_dir -PathType Container) {
	# Run windeployqt.exe to copy the required Qt DLLs
	$THIS_DIR = Split-Path -Parent $MyInvocation.MyCommand.Path
	windeployqt.exe Join-Path $build_dir "QtGUIApp.exe" --qmldir $THIS_DIR
	if ($?) {
		Write-Host "Qt DLLs copied from '$build_dir' to '$deploy_dir'"
	} else {
		Write-Host "Error: Copying Qt DLLs from '$build_dir' to '$deploy_dir' failed. See the log above ^^" -ForegroundColor Red
		exit 1
	}
	# Copy files from the source directory to the newly created directory
	Copy-Item -Path $build_dir\* -Destination $deploy_dir -Recurse -Force
	if ($?) {
		Write-Host "Files copied from '$build_dir' to '$deploy_dir'"
	} else {
		Write-Host "Error: Copying files from '$build_dir' to '$deploy_dir' failed. See the log above ^^" -ForegroundColor Red
		exit 2
	}
} else {
	Write-Host "Error: Build directory '$build_dir' does not exist. Please build the project first, or correct the path."
	exit 3
}

$shortcut_path = $Env:APPDATA + "\Microsoft\Windows\Start Menu\Programs\" + (Join-Path $app_folder $executable_name) + ".lnk"
$null = New-Item -ItemType Directory -Path ([System.IO.Path]::GetDirectoryName($shortcut_path)) -Force

# Create a shortcut in the start menu
$shell = New-Object -ComObject ("WScript.Shell")
$shortcut = $shell.CreateShortcut($shortcut_path)
$shortcut.TargetPath = Join-Path $deploy_dir ($executable_name + ".exe")
$shortcut.Save()
Write-Host "Shortcut created in the start menu: $shortcut.TargetPath"
