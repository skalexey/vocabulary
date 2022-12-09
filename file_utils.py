import re

def insert_before(fpath, where, what):
	replace(fpath, where, what + where, 1)

def replace(fpath, where, what, count = -1):
	with open(fpath, "r") as f:
		contents = f.read()
	pos = contents.find(where)
	if (pos < 0):
		print("-1")
		return 1
	
	contents = contents.replace(where, what, count)

	with open(fpath, "w") as f:
		f.write(contents)

	print(pos)

def search(fpath, what, count = 1):
	if (type(count) != int):
		count = 1
	with open(fpath, "r") as f:
		contents = f.read()
	res = re.findall(what, contents)
	for p in res:
		count = count - 1
		if (count <= 0):
			return p
	return -1