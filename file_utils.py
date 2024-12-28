import os
import pathlib
import re
import sys


class UniversalPath(type(pathlib.Path())):  # Dynamically inherit the correct Path class for the system
	def __new__(cls, path, *args, **kwargs):
		syspath = system_path(path)
		return super().__new__(cls, syspath, *args, **kwargs)


def is_wsl_path(path):
	return path.startswith("/mnt/")

def is_windows_path(path):
	return path[1] == ":" or "\\" in path

def is_unix_path(path):
	return "/" in path

# Is path like /c/Users/...
def is_cyg_path(path):
	return re.match(r'^/[a-zA-Z]/', path) != None  # if the first folder name is a sigle letter

def wslpath_to_windows(path):
	if path.startswith('/mnt/'):
		drive_letter = path[5].upper() + ':'
		windows_path = drive_letter + path[6:].replace('/', '\\')
		return windows_path
	else:
		return path.replace('/', '\\')

def windows_to_wslpath(path):
	if re.match(r'^[a-zA-Z]:\\', path):
		# Handle drive letter paths
		drive_letter = path[0].lower()
		path_replaced = path[2:].replace("\\", "/")
		wsl_path = f"/mnt/{drive_letter}{path_replaced}"
		return wsl_path
	else:
		return path.replace('\\', '/')

def cygpath_to_windows(path):
	if re.match(r'^/[a-zA-Z]/', path):  # Match /x/... where x is a single letter
		drive_letter = path[1].upper() + ':'  # Extract and capitalize the drive letter
		windows_path = drive_letter + path[2:].replace('/', '\\')  # Replace '/' with '\'
		return windows_path
	elif path.startswith('/cygdrive/'):
		# Handle legacy /cygdrive/cx/... paths
		drive_letter = path[10].upper() + ':'
		windows_path = drive_letter + path[11:].replace('/', '\\')
		return windows_path
	else:
		return path.replace('/', '\\')  # Assume it's a relative path

def windows_to_cygpath(path):
	if re.match(r'^[a-zA-Z]:\\', path):
		# Handle drive letter paths
		drive_letter = path[0].lower()
		path_replaced = path[2:].replace("\\", "/")
		# Return '/x/...' format (simpler)
		cygwin_path = f'/{drive_letter}{path_replaced}'
		return cygwin_path
	else:
		return path.replace('\\', '/')  # Assume it's a relative path

def is_absolute_path(path):
	return os.path.isabs(path)

def system_path(path):
	import platform

	# Convert to a Path object
	path_processed = os.path.expanduser(path)  # Expands '~' to the user's home directory
	# Handle Windows-specific logic
	if is_absolute_path(path):
		if platform.system() == "Windows":
			if is_wsl_path(str(path_processed)):
				return wslpath_to_windows(str(path_processed))
				# return subprocess.check_output(["wsl", "wslpath", "-w", path_processed]).decode().strip()
			elif is_cyg_path(str(path_processed)):
				# return subprocess.check_output(["cygpath", "-w", path_processed]).decode().strip()
				return cygpath_to_windows(str(path_processed))
			else:
				# If absolute path, resolve it
				return path_processed
	return str(pathlib.Path(path_processed))


def insert_before(fpath, where, what):
	return replace(fpath, where, what + where, 1)

def replace(fpath, where, what, count = -1):
	# syspath  = system_path(fpath)
	syspath = UniversalPath(fpath)
	with open(syspath, "r") as f:
		contents = f.read()
	pos = contents.find(where)
	if (pos < 0):
		print(-1)
		return -1
	
	contents = contents.replace(where, what, count)

	with open(syspath, "w") as f:
		f.write(contents)

	print(pos)
	return pos

def search(fpath, what, count = 1):
	if (type(count) != int):
		count = 1
	with open(system_path(fpath), "r") as f:
		contents = f.read()
	res = re.findall(what, contents)
	for p in res:
		count = count - 1
		if (count <= 0):
			return p
	return -1

if __name__ == "__main__":
	if len(sys.argv) > 2:  # TODO: check if __main__ works in place of this args check
		arr = []
		for i, a in enumerate(sys.argv):
			if (i > 1):
				arr.append(a)
		locals()[sys.argv[1]](*arr)
	elif len(sys.argv) == 2:
		locals()[sys.argv[1]]()
