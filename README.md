### Design Patterns
#### Nov 16/23, 2017
#### Prof Y C Cheng
#### Dept of Computer Science and Information Engineering
#### Taipei Tech

### Introduction
We will build a unix-like hierarchical file system in this short course (_Pattern Hatching__). We will have plenty of opportunities to encounter **design problems**. After analyzing the design problems, we will make use of appropriate design patterns to solve them. The patterns include _Composite_, _Proxy_, _Observer_, _Visitor_, _Template Method_, and _Mediator_.

I will be using the following simple way to write C++ programs. My programs (and your programs will, too) come with a makefile that builds it by typing _make_ in bash. We will use the g++ stack, which should work on most poplular OS platforms (e.g., Ubuntu, MacOS, and bash on Ubuntu on Windows).

When coding in class, I will use the editor [Atom](https://atom.io), which comes with syntax highlighting, code completion to make coding easy. I will also use the plugin [PlatformIO IDE Terminal](https://atom.io/packages/platformio-ide-terminal) so that we can access a terminal to build programs without leaving Atom.

### Preliminaries
Some useful function regarding files and directories in unix:

- checking size with ifstream
```c++
_fs = new ifstream(_name, std::ios::binary | std::ios::ate);
if (!_fs->good())
  throw string("file not good");
return _fs->tellg();
```

or

```c++
#include <sys/stat.h>
struct stat _st;
if(stat(_name.c_str(), &_st) != 0)
   throw string("file not good");
return _st.st_size;
```
