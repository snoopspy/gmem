G Memory Library
================

# Install
  * For Qt user
    * Include **gmem.pri** in your project file(*.pro).
  * For none Qt user
    * Add all files in src folder in your project.

# Use

  * Include **gmem.h**.
  * Call **gmem_start()** to start memory leak detection and call **gmem_stop()** to stop memory leak detection.

```cpp
[main.cpp]

#include "gmem.h"

int main()
{
  gmem_start();
  ...
  gmem_stop();
}
```

  * Include **gmem.h** before malloc, freem calloc, realloc, new and delete are used.

```cpp
[test.cpp]

#include "gmem.h"

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

  * If compiler error occurs where other header file is included, include **gmemcancel.h** before the header file.

```cpp
[cancel.cpp]

#include "gmem.h"
...
... memory leak detection
...

#include "gmemcancel.h"
#include <list>
...
... no memory leak detection
...

#include "gmem.h"
...
... memory leak detection
...
```

# Example

  * Run the [source code](app/exam/cpp-leak-test/cpp-leak-test.cpp) and you will get the following result.

```
# ./cpp-leak-test
[gmem] ***********************************************************************
[gmem] memory leak 0x5608e7b87eb0(4 bytes) cpp-leak-test.cpp:5
[gmem] ***********************************************************************
[gmem] ***********************************************************************
[gmem] memory leak 0x5608e7b87f70(1024 bytes) cpp-leak-test.cpp:11
[gmem] ***********************************************************************
#
```

# Supported Platforms
  * Linux / g++ 4.8.2 or higher
  * Windows / mingw 4.9.1 or higher
