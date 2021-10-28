<h1 align="center">emily</h1>

[![Discord](https://img.shields.io/discord/682240305235624014?color=blue&label=Discord&logo=discord)](https://discord.gg/naGkzRN)
[![Issues](https://img.shields.io/github/issues/loliconshik3/emily)](https://github.com/loliconshik3/emily/issues)
[![Start](https://img.shields.io/github/stars/loliconshik3/emily)](https://github.com/loliconshik3/emily/stargazers)
[![License](https://img.shields.io/github/license/loliconshik3/emily)](https://github.com/loliconshik3/emily/blob/main/LICENSE)
[![By](https://img.shields.io/badge/by-loliconshik3-informational)](https://github.com/loliconshik3)

**emily** - GNU/Linux applications and scripts launcher.

# For What?

Firstly emily has been maden as a replacement for i3-dmenu, because i don't like it. And offcourse i made it to upgrade my skills in c++.

Now i use emily by main apps launcher and i like it. 

# How work applications list

Well, it's simply to work. emily get all `.desktop` files in `/usr/share/applications` directory, read the files, get execute script from it and add app to list. 

* If you know other methods - write about it.

# Update scripts list

For update scripts list you need add script file (`.sh`) in `$HOME/emily` directory (emily will create dir itself). 
That's all. In next session emily update list and get all scripts from directory.