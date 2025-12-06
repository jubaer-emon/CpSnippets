Snippets I use in compettive programming compettitions (Codeforces, ICPC Prelim).

Place this folder in the workspace which may contain the `.vscode` subfolder and run the python file to generate the snippets.

Generate notebook with [codes2pdf](https://github.com/Erfaniaa/codes2pdf) in Linux or WSL. `codes2pdf` doesn't work on windows without WSL.

## Useful shortcuts
- `Ctrl + Shift + L` to change all occurances / rename 

## Steps to setup PC if internet is available:
- Download this repo as zip
- Install [CPH-NG vscode extension](https://marketplace.visualstudio.com/items?itemName=langningchen.cph-ng)
- Run the genrator python file
- Set cph cpp compiler flags to 
```
-DLOCAL -Wall -Wextra -Wshadow -Wconversion -Wfloat-equal -Wduplicated-cond -Wlogical-op -Wfatal-errors -g -std=c++17 -D_GLIBCXX_DEBUG
```
- Set cph run tests shortcut to `Ctrl + Enter` and fold all regions to `Alt + F`

## Steps when internet is not available 
- Config VS code with `Ctrl + P > Edit Config (UI)`

## TODO
- [x] vscode snippets generator
- [x] fix: script fail when .vscode folder not present
- [x] pdf generator
- [ ] organize files into topics
- [ ] graph snippets
- [ ] Steps when internet is not available 