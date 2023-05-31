# Threads

## Concurrency with Multiple Processes
The first way to make use of concurrency within an application is to divide the
application into multiple, separate, single-threaded processes that are run that the same
time. These separate processes can then pass messages to each other through all the normal
inter-process communication channels (signals, sockets, files, pipes, and so on). One
downside is that such communication between processes is either complicated to setup or
slow, or both, because operating systems typically provide a lot of protection between
processes to avoid one process accidentally modifying data belonging to another process.

The alternative approach to concurrency is to run multiple threads in a single process.
Threads are much like light-weight processes: each thread runs independently of others,
and each may run a different sequence of instructions. But all threads in a process share
the same address space, and most of the data can be accessed directly from all threads --
global variables remain global, and pointers or references to objects or data can be
passed around among threads.


## Launching A New Thread
The performance gain might not be as large as expected; There's an inherent overhead
associated with launching a thread, because the OS has to allocate the associated kernel
resources and stack space and then add new thread to the scheduler, all of which takes
time. If the task being run on the thread is completed quickly, the time taken by the task
may be dwarfed by the overhead of launching the thread, possibly making the overall
performance of the application worse than if the task had been executed directly by the
spawning thread.

Furthermore, threads are a limited resource. If you have too many threads running at once,
this consumes OS resources and may take the system as a whole run slower. Not only that,
but using too many threads can exhaust the available memory or address space for a
process, because each thread requires a separate stack space.

Finally, the more threads you have running, the more context switching the operating
system has to do. Each context switch takes time that could be spent doing useful work, so
at some point, adding an extra thread will reduce the overall application performance
rather than increase it.

## Destructing a Thread
You need to explicitly decide whether to wait for it to finish. If you don't decide before
the std::thread object is destroyed, then your program is terminated (the `std::thread`
destructor calls `std::terminate()`). It's therefore imperative that you ensure that the
thread is correctly joined or detached, even in the presence of exceptions.
```cpp
void do_something(int& i) { ++i; }

struct func {
  int& i;
  func(int& i_) : i(i_) {}
  void operator()() {
    for (unsigned j = 0; j < 1000000; ++j) {
      do_something(i);
    }
  }
};

void oops() {
  int some_local_state = 0;
  func my_func(some_local_state);

  std::thread my_thread(my_func);
  my_thread.detach();  // my_func is continuing to run and visit
                       // some_local_state even though oops is finished & exited
}
```

C++ Runtime Library ensures that the resources associated with a detached thread are
correctly reclaimed when the thread exits. But it can no longer be joined.
Using RAII:
```cpp
class thread_guard {
  std::thread& t;

 public:
  explicit thread_guard(std::thread& t_) : t(t_) {}
  ~thread_guard() {
    if (t.joinable()) {
      t.join();
    }
  }
  thread_guard(thread_guard const&) = delete;
  thread_guard& operator=(thread_guard const&) = delete;
};

struct func;
void do_something_in_current_thread() {}

void f() {
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread t(my_func);
  thread_guard g(t);
  do_something_in_current_thread();
}

```

## Passing arguments to threads
By default, the arguments are copied into internal storage, where they can be accessed by
the newly created thread of execution, and then passed to the callable object or function
as rvalues as if they were temporaries.
```cpp
void f(int i, const std::string& s) {
  char kk = s[i];
  printf("%c\n", kk);
}

void oops(int some_param) {
  char buffer[1024];
  sprintf(buffer, "%i", some_param);
  // std::string kk{"sldkfj"};
  std::thread t(f, 3, std::string(buffer));
  t.detach();
}
```
