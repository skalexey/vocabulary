import os
import subprocess
import sys

args = ""
if (len(sys.argv) > 1):
	args = " " + sys.argv[1]

status = 0

if os.name == 'nt':
	p = subprocess.Popen(["powershell.exe", "deploy.ps1"], stdout=sys.stdout)
	status = p.communicate()
else:
	status = os.system("./deploy.sh" + args)

sys.exit(status)
