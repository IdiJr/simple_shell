# 0x16. C - Simple Shell project (hsh)
**hsh** is a simple shell unix command interpreter that is part of the alx_low_level_programming and is intended to emulate the basics **sh** shell. All the information given in this README is based on the **hsh** and **bash** man (1) pages.

## Overview
**hsh** is a sh-compatible command language interpreter that executes commands read from the standard input or from a file.

### Invocation
Usage: **hsh** 
hsh is started with the standard input connected to the terminal. To start, compile all .c located in this repository by using this command:
```
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
./hsh
```
**hsh** is allowed to be invoked interactively and non-interactively. If **hsh** is invoked with standard input not connected to a terminal, it reads and executes received commands in order.

Example:
```
$ echo "echo 'Cisfun'" | ./hsh
'Cisfun'
$
```

When **hsh** is invoked with standard input connected to a terminal (determined by isatty(3), the interactive mode is opened. **hsh** Will be using the following prompt `$ `.

Example:
```
$./hsh
$ 
```

If a command line argument is invoked, **hsh** will take that first argument as a file from which to read commands.

Example:
```
$ cat trial
echo 'Cisfun'
$
```

### Environment
Upon invocation, **hsh** receives and copies the environment of the parent process in which it was executed. This environment is an array of *name-value* strings describing variables in the format *NAME=VALUE*. A few key environmental variables are:

#### HOME
The home directory of the current user and the default directory argument for the **cd** builtin command.

Example:
```
$ echo "echo $HOME" | ./hsh
/root 
```
NB: $HOME during the test was the root folder

#### PWD
The current working directory as set by the **cd** command.

Example:
```
$ echo "echo $PWD" | ./hsh
/root/simple_shell
```

#### OLDPWD
The previous working directory as set by the **cd** command.

Example:
```
$ echo "echo $OLDPWD" | ./hsh
/root
```

#### PATH
A colon-separated list of directories in which the shell looks for commands. A null directory name in the path (represented by any of two adjacent colons, an initial colon, or a trailing colon) indicates the current directory.

Example:
```
$ echo "echo $PATH" | ./hsh
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/mnt/c/Program Files/WindowsApps/CanonicalGroupLimited.Ubuntu20.04LTS_2004.5.11.0_x64__79rhkp1fndgsc:/mnt/c/Windows/system32:/mnt/c/Windows:/mnt/c/Windows/System32/Wbem:/mnt/c/Windows/System32/WindowsPowerShell/v1.0/:/mnt/c/Windows/System32/OpenSSH/:/mnt/c/MinGW/bin:/mnt/c/Users/idial/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/idial/AppData/Local/Programs/Microsoft VS Code/bin:/snap/bin
```

### Command Execution
When a command is inputed into **hsh**, it tokenizes it into words using `" "` as a delimiter. It then considers the first word as a command and subsequent words as arguments to that command. **hsh** then does the following:
1. If the first character of the command is neither a slash (`\`) nor dot (`.`), the shell searches for it in the list of shell builtins and invokes that builtin if it exists.
2. If the first character of the command is niether a slash (`\`), dot (`.`), nor builtin, **hsh** searches each element of the **PATH** environmental variable for a directory containing an executable file by that name.
3. If the first character of the command is a slash (`\`) or dot (`.`) or either of the above searches was successful, the shell executes the named program with any remaining given arguments in a separate execution environment.

### Exit Status 
**hsh** returns the exit status of the last command executed, with zero indicating success and non-zero indicating failure.
If a command is not found, the return status is 127; if a command is found but is not executable, the return status is 126.
All builtins return zero on success and one or two on incorrect usage (indicated by a corresponding error message).

### Signals
When the keyboard ctrl+c is input in the interactive mode, **hsh** is exited and also, End-Of-File ctrl+d will exit the program.

User hits ctrl+c in the second command and ctrl+d in the fourth command.
```
$ ~/simple_shell# ./hsh
$ ^C
$ ~/simple_shell# ./hsh
$ ~/simple_shell# 
```

### Variable Replacement
**hsh** interprets the `$` character for variable replacement.

#### $ENV_VARIABLE
`ENV_VARIABLE` is substituted with its value.

Example:
```
$ echo "echo $PWD" | ./hsh
/root/simple_shell
```

#### $?
`?` is substitued with the return value of the last program executed.

Example:
```
$ echo "echo $?" | ./hsh
0
```

#### $$
The second `$` is substitued with the current process ID.

Example:
```
$ echo "echo $$" | ./hsh
9
```

### Comments
**hsh** ignores all words and characters that begins with `#` character on a line.

Example:
```
$ echo "echo 'Cisfun' #this will be ignored!" | ./hsh
'Cisfun'
```

### Operators
**hsh** specially interprets the following operator characters:

#### ; - Command separator
Commands separated by a `;` are executed sequentially.

Example:
```
$ echo "echo 'hello' ; echo 'world'" | ./hsh
'hello'
'world'
```

#### && - AND logical operator
`command1 && command2`: `command2` is executed if, and only if, `command1` returns an exit status of zero.

Example:
```
$ echo "error! && echo 'Cisfun'" | ./hsh
./shellby: 1: error!: not found
$ echo "echo 'Great Tower of' && echo 'Babel'" | ./hsh
'Great Tower of'
'Babel'
```

#### || - OR logical operator
`command1 || command2`: `command2` is executed if, and only if, `command1` returns a non-zero exit status.

Example:
```
$ echo "error! || echo 'Reverbs'" | ./hsh
./hsh: 1: error!: not found
'Reverbs'
```

The operators `&&` and `||` have equal precedence, followed by `;`.

### Builtin Commands

#### cd
  * Usage: `cd [DIRECTORY]`
  * Changes the current directory of the process to `DIRECTORY`.
  * If no argument is given, the command is interpreted as `cd $HOME`.
  * If the argument `-` is given, the command is interpreted as `cd $OLDPWD` and the pathname of the new working directory is printed to standad output.
  * If the argument, `--` is given, the command is interpreted as `cd $OLDPWD` but the pathname of the new working directory is not printed.
  * The environment variables `PWD` and `OLDPWD` are updated after a change of directory.

Example:
```
$ ./hsh
$ pwd
/root/simple_shell
$ cd ../
$ pwd
/root
$ cd -
$ pwd
/root/simple_shell
```

#### exit
  * Usage: `exit [STATUS]`
  * Exits the shell.
  * The `STATUS` argument is the integer used to exit the shell.
  * If no argument is given, the command is interpreted as `exit 0`.

Example:
```
$ ./hsh
$ exit
```
The shell closes after the exit command was executed.

#### env
  * Usage: `env`
  * Prints the current environment.

Example:
```
$ ./hsh
$ env
SHELL=/bin/bash
WSL_DISTRO_NAME=Ubuntu-20.04
NAME=JRs
PWD=/root/simple_shell
...
```

#### setenv
  * Usage: `setenv [VARIABLE] [VALUE]`
  * Initializes a new environment variable, or modifies an existing one.
  * Upon failure, prints a message to `stderr`.

Example:
```
$ ./hsh
$ setenv NAME Luropichka
$ echo $NAME
Luropichka
```

#### unsetenv
  * Usage: `unsetenv [VARIABLE]`
  * Removes an environmental variable.
  * Upon failure, prints a message to `stderr`.

Example:
```
$ ./hsh
$ setenv NAME Luropichka
$ unsetenv NAME
$ echo $NAME

$
```

## Authors & Copyrights

* [Ali Baba Idi](https://github.com/IdiJr)
* [Emmanuel Addo](https://github.com/emmanueladdo)
