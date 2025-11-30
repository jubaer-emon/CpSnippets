import json,os,pathlib 

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

output_file = pathlib.Path.cwd().parent / ".vscode/CpSnippetsGenerated.code-snippets"
output_file.parent.mkdir(exist_ok=True, parents=True)

with output_file.open("w") as file:
	file.write(json_object)

print("Snippets Generated")