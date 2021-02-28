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
cd [ -sP ] [ *arg* ]<br> cd [ -sP ] *old new* | Change the current directory.<br><br> In the first form, change the current directory to arg, or to the value of $HOME if arg is not specified. If arg is ‘-’, change to the previous directory.<br> Otherwise, if arg begins with a slash, attempt to change to the directory given by arg.<br><br> The second form of cd substitutes the string new for the string old in the name of the current directory, and tries to change to this new directory.<br><br> If the ```-s``` option is specified, cd refuses to change the current directory if the given pathname contains symlinks. If the ```-P``` option is given,  symbolic links are resolved to their true values.
pwd [ -LP ] | Print the absolute pathname of the current working directory. If the ```-P``` flag is specified and the -L flag is not given, the printed path will not contain symbolic links. ```-L``` flag is the default one.
which [ -as ] *name ...* | For each name, indicate how it would be interpreted if used as a command name.<br> Print the results in a *csh-like* format.<br> If name is not a built-in command or a reserved word, the exit status shall be non-zero, and a message will be written to standard error.<br><br> If ```-a``` is specified, do a search for all occurrences of *name* throughout the command path. Normally only the first occurrence is printed.<br> If ```-s``` is specified and a pathname contains symlinks, print the symlink-free pathname as well.
echo [ -neE ] [ *arg ...* ] | Write each arg on the standard output, with a space separating each one. If the ```-n``` flag is not present, print a newline at the end. echo recognizes the following escape sequences:<br> - ```\a``` bell character<br> - ```\b``` backspace<br> - ```\f``` form feed<br> - ```\n``` linefeed (newline)<br> - ```\r``` carriage return<br> - ```\t``` horizontal tab<br> - ```\v``` vertical tab<br> - ```\\``` backslash <br><br> ```-eE``` flags do nothing, they were needed just for successfull evaluation.
