# MASH
Mayur's Assembeled SHell.

Creating a shell has 3 parts:
1. Parser
2. Executer
3. Subsystems.

Initially I will be concentrating on the parser and executer. 

Subsystems would be a part of the imprvement for the shell.

What it does:
* Mini-shell to execute system commands.
* Invokes user-made commands with arguements from CWD.
* Redirection

Room for improvemnt:
* Piping
* Arrow and Tab keys (eg. up arrow key should bring the previous used commands, tab should complete the filenames from CWD)
* Handling more signals
* Implementing more user-made commands

User-Made Commands Implemeneted so far:
1. ls
2. cat
3. cp
4. mv
5. rm
6. touch
7. slink (to create soft links)
8. rdlink (to figure out the path trail to the origial file)
9. clear
