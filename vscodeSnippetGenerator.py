import json,os

os.chdir(os.path.dirname(__file__))
snippets = {}

for file in os.listdir():
	if not file.endswith('.cpp'): continue

	name = file[:-len('.cpp')]

	with open(file) as f:
		content = f.read().replace('\\','\\\\').splitlines()
	
	snippets[name] = {
		'scope': 'cpp',
		'prefix': name,
		'body': content
	}


json_object = json.dumps(snippets, indent=4)

with open("../.vscode/CpSnippetsGenerated.code-snippets", "w") as outfile:
	outfile.write(json_object)