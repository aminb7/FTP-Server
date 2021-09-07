# FTP-Server

The File Transfer Protocol (FTP) is a standard communication protocol used for the transfer of computer files from a server to a client on a computer network. 
In this project, we implemented an FTP Server on a client–server model architecture using separate control and data connections between the client and the server. Implemented commands are as follows.

1. `USER [name]`, Its argument is used to specify the user's string. It is used for user authentication.
2. `PASS [password]`, Its argument is used to specify the user's password. It is used for user authentication.
3. `PWD`, It is used to print the name of the current working directory.
4. `MKD [path]`, Its argument is used to specify the directory's path. It is usede to create a new directory.\n"
5. `DELE [flag]` [path], Its argument is used to specify the file/directory's path. It flag is used to specify whether a file (-f) or a directory (-d) will be removed. It is usede to remove a file or directory.
6. `LS`. It is used to print the list of files/directories in the current working directory.
7. `CWD [path]`, Its argument is used to specify the directory's path. It is used to change the current working directory.
8. `RENAME [from] [to]`, Its arguments are used to specify the old and new file's name. It is used to change A file's name.
9. `RETR [name]`, Its argument is used to specify the file's name. It is used to download a file.
10. `HELP`, It is used to display information about builtin commands.
11. `QUIT`, It is used to sign out from the server.

## Developers

* [**Ghazal Kalhor**](https://github.com/kalhorghazal)
* [**Amin Baqershahi**](https://github.com/aminb7)
