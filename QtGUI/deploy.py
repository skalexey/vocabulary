import os
import subprocess
import sys

args = ""
if (len(sys.argv) > 1):
    args = " " + sys.argv[1]

status = 0

if os.name == 'nt':
    status = os.system("powershell.exe deploy.ps1" + args)
else:
    status = os.system("./deploy.sh" + args)

sys.exit(status)

