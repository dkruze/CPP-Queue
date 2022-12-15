This queue holds for integers and is packaged in a class so it can be reworked as a header file, if need be.
It works as expected except it can have trouble recognizing when its completely empty after the last member has been dequeued, so be wary of that.
This can be tested in any compatible environment, just remember the steps for compiling (to C++23 standards) via the command line:
  g++ queue.cpp
  ./a.exe (or ./a.out)
