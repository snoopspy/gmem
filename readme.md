G Memory Library
================

# Install
  * For Qt user
    * Include **gmem.pri** in your project file(*.pro).
  * For none Qt user
    * Add all files in src folder in your project.

# Use

  * Include **GMem**.
  * Call **gmem_start()** to start memory leak detection and call **gmem_stop()** to stop memory leak detection.

```cpp
[main.cpp]

#include <GMem>

int main()
{
  gmem_start();
  ...
  gmem_stop();
}
```

  * Include **Gem** before malloc, freem calloc, realloc, new and delete are used.

```cpp
[test.cpp]

#include <GMem>

void foo()
{
  malloc(4);
  calloc(256, 4);
  ...
  new int;
  new int[256];
  ...
}
```

  * If compiler error occurs where other header file is included, include **GMemCancel** before the header file.

```cpp
[cancel.cpp]

#include <GMem>
...
... memory leak detection
...

#include <GMemCancel>
#include <list>
...
... no memory leak detection
...

#include <GMem>
...
... memory leak detection
...
```

# Example

  * Run the [source code](app/exam/cpp_leak_test/cpp_leak_test.cpp) and you will get the following result.

```
    # ./cpp_leak_test 
    [gmem] ***********************************************************************
    [gmem] memory leak 0xe7d070(4 bytes) cpp_leak_test.cpp:6
    [gmem] ***********************************************************************
    [gmem] ***********************************************************************
    [gmem] memory leak 0xe7d090(1024 bytes) cpp_leak_test.cpp:13
    [gmem] ***********************************************************************
    #
```

# Supported Platforms
  * Linux / g++ 4.8.2
  * Windows / mingw 4.9.1
