import json,os

os.chdir(os.path.dirname(__file__))
snippets = {}

for root, _, files in os.walk('.'):
	for filename in files:		
		if not filename.endswith('.cpp'): continue

		name = filename[:-len('.cpp')]

		with open(os.path.join(root, filename)) as f:
			content = f.read().replace('\\','\\\\').splitlines()
		
		snippets[name] = {
			'scope': 'cpp',
			'prefix': name,
			'description': root,
			'body': content
		}

json_object = json.dumps(snippets, indent=4)

with open("../.vscode/CpSnippetsGenerated.code-snippets", "w") as outfile:
	outfile.write(json_object)

print("Snippets Generated")