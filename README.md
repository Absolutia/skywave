# skywave
Chat program. Or its supposed to be. Doesn't really resemble one right now.
Currently for command line Linux/BSD only, but we have planned a DOS port as well as GUI versions for Windows & Android.
## Installation/compilation
### Requirements
<b>ncurses</b> and <b>pthread</b>, if for some reason your BSD or GNU/Linux distro doesn't come with them.<br>
As for hardware? If it can run the Linux or BSD kernels, it should be fine.
### Compiling
The build script is unmaintained so just run this:<br>
   ```gcc -Wall main.c -lncursesw -pthread -I (include directory here) -O3 -o skywave.bin```<br><br>
Remember: the "include directory here" bit is a placeholder-- you will want to replace that part with the path for the include directory.
