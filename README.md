# <p align=center> UCODE-ush </p>

<h1 align=center> Installation </h1>

* Downdoal/clone the repo, move to the directory
* Type ```make``` to build the project, then ```./ush```
* Type ```make uninstall``` to delete project or ```make clean``` to delete unneccessary files
* Type ```make reinstall``` to rebuild the project

<h1 align=center> Implemented features </h1>

* Builtin commands without flags: ```export, unset, exit, fg```
* Builtin commands with flags:
  * ```env``` with ```-i, -P, -u```
  * ```cd``` with ```-s, -P``` and - argument
  * ```pwd``` with ```-L, -P```
  * ```which``` with ```-a, -s```
  * ```echo``` with ```-n, -e, -E``` 
* Managing signals CTRL+C and CTRL+Z
* Command separator ```;```
* The tilde expansion ```~``` with the following tilde-prefixes: ```~, ~/dir_name, ~username/dir_name, ~+/dir_name, ~-/dir_name```
* The basic form of parameter expansion ```${parameter}```
* The two-level-nested command substitution ```$(command)``` (without suport of command separator inside)

<h1 align=center> Commands manual </h1>

Command | Description
------- | -----------
unset *name* ... | Each named system variable is unset.
exit [*n*] | Exit the shell with the exit status specified by an arithmetic expression n; if none is specified, exit with *0* status.
export [*name[=value] ...*] | The specified names are set to the environment.
fg [*job ...*] | Bring each specified job in turn to the foreground.
env [-i] [-P *altpath*] [-u *name*] [*utility* [*argument* ...]] | Executes another utility after modifying the environment as specified on the command line. The options are as follows:<br> ```-i```      Execute the utility with no environment variables. <br>```-P altpath``` Search the set of directories as specified by altpath to locate the specified utility program, instead of using the value of the PATH environment variable.<br> ```-u name``` If the environment variable name is in the environment, then remove it before processing the remaining options. The value for name must not include the ```=``` character.
