---
title: Standard C++ Futures, Promises and Async
subtitle: An introduction to std::future, std::promise and std::async from the C++ standard library
slug: standard-cpp-futures
date: '2025-02-22'
tags:
- C++
---

The standard library of modern C++, most notably since C++ 11, features types for basic asynchronous programming in the header `<future>`. In this post, we will explore the most important pieces to quickly get started.

We will not get into every detail, though, since [cppreference.com/header/future](https://en.cppreference.com/w/cpp/header/future) already offers an excellent and comprehensive coverage.

## `std::future`

Any operation running asynchronously must offer a way for clients to retrieve its result, or at least to wait until it completes. The `std::future<T>` type implements a mechanism to offer just that through synchronization objects.

Let's take a look at the following example:

{{< code-file language="cpp" source="code/future_1.cpp" >}}

The functions `wait_for_async` and `print_timed` are provided in a separate file and provide necessary functionality to demonstrate the use of `std::future`. Their implementation is not relevant, but you can find them [here](./code/helpers.cpp).

The example demonstrates a common usage of a future: Start an asynchronous operation, immediately receive a waitable `std::future` object, and then at some point wait for the operation to complete using `.get()`.

But as the client, we gain the ability to decide for ourselves when to wait for the result to complete, and can thus also control if we want to start multiple operations simultaneously:

```cpp
print_timed("start");               // 0s

std::future<void> first_future = wait_for_async(std::chrono::seconds(2));
std::future<void> second_future = wait_for_async(std::chrono::seconds(2));
// second_future is running while we wait for first_future
first_future.get();
print_timed("first completed");    // 2s
second_future.get();
print_timed("second completed");   // 2s

std::future<void> third_future = wait_for_async(std::chrono::seconds(2));
third_future.get();
print_timed("third completed");    // 4s
```

It is even possible to receive result values from futures:

```cpp
auto add_async(int, int) -> std::future<int>;

int main ()
{
    std::cout << add_async(20, 22).get() << std::endl; // 42
}
```

As you can see, it is quite straightforward to work with returned future objects.

### Execution Guarantees

Even though the prior examples might suggest otherwise, it is critical to note that a future object _does not make any guarantees_ about the underlying execution. The fact that the futures in the examples started executing right away was only due to the specific implementations of the helper functions such as `wait_for_async`.

As we will see in the next sections, some operations will not start until someone waits on their returned future, or may not even start at all and instead wait until an external event sets the result.

All that a future object does is provide a way to __wait for a result__. You generally don't construct a future directly, but either use one of the accompanying classes covered in the next sections or receive one from an external library.

### Exceptions

A feature of `std::future` is that the producer can throw an exception at the client's site. Thus, you'll need to expect exceptions when calling `.get()`.

```cpp  
try
{
    future.get();
}
catch (const std::exception& e) { }
```

The `.wait()` function on the other hand, also available on all futures, does not throw exceptions and merely waits until the future completes. If you want to handle exceptions you'll have to call `.get()`, even if you're not interested in a return value.

A specialization of `std::future<void>` with a `void .get()` function is available for this purpose.

### Shared Futures

It is best to regard a `std::future` as a one-way-use object:

- It is not allowed to call `.get()` on a single future object more than once: Doing so will result in undefined behavior. \
  `.wait()` can be called multiple times without invalidating the future object, although the uses of this behavior are limited.
 
- Futures can be moved, but cannot be copied: The copy assignment operator and constructor are not available.

If you wish to share a future, you'll need to convert it to a `std::shared_future` using the constructor or `.share()` function:

```cpp
std::shared_future<void> shared_future{std::move(future)};
// or
std::shared_future<void> shared_future = future.share();
```

Shared futures _can_ be copied, and _can_ be used to retrieve the result multiple times.

The original future object will be invalidated during the conversion.

### Non-Blocking Waits & Continuations

Unfortunately, the standard library does not provide a way to specify a callback to a future, nor does it provide a way to chain futures. Fortunately, you can always chain futures manually through function composition, as we will explore in the `std::async` [coverage below](#stdasync).

There is, however, no way to wait for a future to complete using standard, non-blocking awaits without a callback mechanism or something similar. So beware of `.get()` and `.wait()` calls on threads that run event loops, such as UI threads, as they __are blocking__.

I recommend looking into C++ [coroutines](https://en.cppreference.com/w/cpp/language/coroutines) if this is your use case. At the time of writing, they are a relatively new feature of C++, meaning that their specification and implementations are not entirely completed yet, and are not covered in more detail here. They do look very promising, though.

## `std::promise`

We have learned that a future offers nothing more than a way to wait for a result. They can be obtained through several ways, but the most prominent one is through a `std::promise<T>` object. A promise offers a way to create a future, and to set its result at some later point in a possibly different thread.

Let's take a look at the following example:

{{< code-file language="cpp" source="code/promise_1.cpp" >}}

The most interesting bits are the creation of the promise object, obtaining its future through `.get_future()`, and setting its result through `.set_value()` in another thread.

As you can imagine, promises are a great way to offer futures to clients, which is why they are often used internally.

There is unfortunately no shared promise type available like there is for futures, so you're not allowed to call `.get_future()` more than once on a promise object.

### Exceptions

Futures might not only return a result, but also throw exceptions, as covered in the [future](#stdfuture) section. Promise objects offer to set exceptions in their futures through the `.set_exception()` method:

``` cpp
auto promise = std::promise<int>{};

auto concurrentThread = std::thread([&promise]
{
    try
    {
        throw std::logic_error{"an exception occurred"};
    }
    catch (...)
    {
        promise.set_exception(std::current_exception());
    }
});

try
{
    promise.get_future().get();
}
catch(...)
{
    std::cout << "exception caught";
}
```

There is no `.set_exception` overload that directly takes a simple exception reference. Instead, it expects an exception pointer of type `std::exception_ptr`, which you can obtain by:

- Calling `std::current_exception()` when you are in a `catch` block

```cpp
try { ... }
catch(...) { promise.set_exception(std::current_exception()); }
```

- Using `std::make_exception_ptr()` to create a pointer

```cpp
promise.set_exception(
    std::make_exception_ptr(std::logic_error {"an exception occurred"}));
```

## `std::packaged_task`

An arguably easier way to create futures than through a promise is through a `std::packaged_task<T>`. You can think of a packaged task as a wrapper around a function that provides a future object to retrieve the result, as shown in the following example:

{{< code-file language="cpp" source="code/packaged_task_1.cpp" >}}

Note that the created `std::packaged_task` object can be called like a function, and that the result of that function can be retrieved through the future.

You might ask yourself what happens if you don't call the `packaged_task` object before waiting for the future to complete, so something like this:

```cpp
auto task = std::packaged_task<int()>{[]
{
    return 42;
}};

auto future = task.get_future();
std::cout << future.get() << std::endl; // 42

task();
```

The answer is that the _future would never complete_, since the function does not start before being called explicitly. So a packaged task is no way to start an operation asynchronously, but rather a way to bundle (_package_) a task for execution in another place.

### Parameterization

One of the selling-points of `std::packaged_task`s is that they can be parameterized, meaning that you can pass arguments to the function at the time of invocation.

{{< code-file language="cpp" source="code/packaged_task_2.cpp" >}}

### Other Remarks

There are some noteworthy things to keep in mind when working with `std::packaged_task` objects:

- It is not possible to obtain more than one future object from a `std::packaged_task` through `.get_future()`.
- It is not allowed to invoke the function of a packaged task more than once. 
- The state of a `std::packaged_task` can be reset through the `.reset()` function, equivalent to creating a new `std::packaged_task` object using the same function.
- A `std::packaged_task` can only be moved, not copied.

## `std::async`

Until now, we've looked at futures, promises, and packaged tasks, and how they can be used to neatly design asynchronous applications. The remaining piece for a complete async library is a way _start_ asynchronous operations without explicit threading, and that's where `std::async` comes into play:

{{< code-file language="cpp" source="code/async_1.cpp" >}}

In this example, we've started an asynchronous operation without relying on an external service or an explicitly created thread as in the previous sections, but instead made use of the `std::async` function. This function allows us to start new operations in a _task-based_ style, which abstracts over an underlying threading model.

Furthermore, unlike the previously covered types, `std::async` is a function. It returns a `std::future` object, which can be used to retrieve the result of the operation.

### Execution Policies

You might have wondered what the first `std::launch::async` argument was about. It is a flag that determines when the asynchronous operation starts and knows three styles:

`std::launch::async`
: Start the execution right away on a different thread. 

`std::launch::deferred`
: Start the execution when the result is retrieved (lazily).

`std::launch::async | std::launch::deferred`
: Leaves the decision up to the implementation to decide, which might be able to make a more educated choice.

A `std::async` overload without an execution policy is also available, defaulting to `std::launch::async | std::launch::deferred`.

C++ does not specify how `std::launch::async` must be implemented under the hood: A started task might be immediately executed on a freshly created thread, an existing thread that is re-used, or simply be put into the queue of an underlying thread pool. In preemptive operating systems, you'll also need to consider that the operating system is responsible for scheduling threads, so you really get next to no guarantees about the execution order.

Specific implementations of C++ might offer more guarantees, and are theoretically even allowed to add more execution policies.

### Construction Variants

The definition of `std::future<T> async(std::launch policy, F&& f, Args&&... args)` is very flexible and makes use of templates extensively, so let's dissect the parts:

`std::launch policy`
: defines how the operation should be started. Optional. See the [prior section](#execution-policies) for more information. 

`F&& f`
: stands for an object that can be invoked. It can be a function pointer, a lambda, or any other object with an `operator()`.

`Args&&... args`
: is a variadic list of arguments that are passed to the function `f`. In more simple terms, it means that the `operator()` of `f` is allowed to define any number of parameters, as long as they match the provided arguments in `args`.

`std::future<T>`
: is the return value of the function, where `T` is calculated from the return value of `f`.  

Note that the double ampersands `&&` specify _universal references_, not rvalue references. You can pass both lvalues and rvalues, and they will be moved or copied accordingly.

Using this definition, we can imagine several ways to make `std::async` calls:

- with a lambda
    
```cpp
std::cout << std::async([]{ return 42; }).get() << std::endl;
```

- with a function pointer

```cpp
int sum(int first, int second) { return first + second; }
std::cout << std::async(sum, 20, 22).get() << std::endl; // 42
```

- with a type that defines an `operator()` function:

```cpp
struct AddX
{
    int first;
    AddX(int first) : first(first) {}

    int operator()(int second) const
    {
        return first + second;
    }
};

auto adder = AddX{20};
std::cout << std::async(adder, 22).get() << std::endl; // 42
```

- and many more...

### Lifetimes

To better understand the lifetimes of `std::async` and objects passed to it, we'll make a few experiments. I executed all snippets on an M-series mac with clang 16.0. The results might differ on other platforms or compilers.

A prerequisite for the experiments is a type `Tracker`, which assigns each instance an ID and prints a message when it is constructed, moved, copied, or destructed without being moved from. If you're interested, you can find its implementation [here](./code/Tracker.hpp). Using this type we can observe the lifetimes of various `std::async` calls.

First, let's take a look at what happens to _passed arguments_. To do so, we'll take the tracker for a spin and run the following piece of code:

```cpp
std::async([](const Tracker& t) {}, Tracker{}).get();
// constructed 7
// moved 7
// moved 7
// moved 7
// destructed 7
```

This output corresponds with what we would expect: An instance is created as a rvalue, moved around a few times, and then destructed.

A slightly different story is told if we pass the tracker as an lvalue to `std::async`:

```cpp
Tracker tracker{};
std::async([](const Tracker& t) {}, tracker).get();
// constructed 7
// copied 7 to 49
// moved 49
// moved 49
// destructed 49
// destructed 7
```

I would say that the output is still quite reasonable: We are creating a copy, which is then moved around and destructed, before our original value is then destructed as well. We would observe the same behavior as before if we wrapped the argument in a `std::move` call.

Next, let's take a look at the lifetimes of _the function objects_. The `Tracker` type features a `void operator()` which prints a trace when invoked as well, so we can do this:

```cpp
std::async(Tracker{}).get();
// constructed 7
// moved 7
// moved 7
// moved 7
// operator() called on 7
// destructed 7
```

As expected, we can see how the function object is constructed, moved a few times, called, and then destructed. In the clang implementation I'm using, it seems like the function objects and their arguments are treated the same way.

Next, let's try to find out if the `std::async` arguments lifetimes are tied to the _retrieval of the result_, or the _destruction of the returned future_:

```cpp
auto future = std::async(Tracker{});
future.get();
std::cout << "------\n";
// constructed 7
// moved 7
// moved 7
// moved 7
// operator() called on 7
// destructed 7
// --- end
```

The produced output answers the question: The argument is destructed after the result is retrieved, not when the returned future is destructed.

However, it is also possible that the tracker is destructed after the `operator()` function completes, and the result is simply cached temporarily. We can find out whether this is true by _waiting_ for the future to complete, instead of retrieving its result:

```cpp
auto future = std::async(Tracker{});
future.wait();
std::cout << "------\n";
// constructed 7
// moved 7
// moved 7
// moved 7
// operator() called on 7
// --- end
// destructed 7
```

This time, the findings may be more surprising: Even though the operation completed, the tracker is not immediately destructed. Instead, it lives as long as the returned futures object. 

Both findings are in line with the C++ standard, which states the future is invalidated after its result is retrieved, hinting that implementations might choose to keep everything alive until either the result is retrieved or the future is destructed.

At this point, I would like to again point out that this behavior might differ between compilers and platforms. 

Finally, let's take a look at the lifetime of _return values_.

```cpp
auto future = std::async([]
{
    return Tracker{};
});

auto tracker = future.get();
std::cout << "--- tracker id: " << tracker.id << '\n';

// constructed 7
// moved 7
// moved 7
// --- tracker id: 7
// destructed 7
```

As you can see, the return value is properly moved around and destructed without unnecessary copies. There is more to this behavior than might appear at first glance, namely copy-elisions, which we will not cover in more depth here.

### Continuation

There is unfortunately no built-in way to specify a continuation for a `std::async` call, or a future in general. The C++ standard committee seems to work on this issue and similar ones related to asynchronous programming, but for now, we'll have to do the chaining manually.

Luckily, chaining futures together isn't as hard as it might sound. All we have to do is to either wrap the futures or function objects, which we can go about in different ways.

An easy one is by waiting for a future to complete in yet another task, and continue processing the result there:

```cpp
auto first_future = std::async([]
{
    return 22;
});

auto second_future = std::async([first_future = std::move(first_future)] mutable
{
    return first_future.get() + 20;
});

std::cout << second_future.get(); // 42
```

Of course, we could do this wrapping in a more generic way, e.g., through a dedicated function. It is not a perfect solution since it requires a second task to run, possibly on a dedicated thread, but I don't think it is a particularly bad one in most cases.

The other already mentioned way would be to wrap the function object before starting it, and then forward the wrapper function for execution, as demonstrated in the following example using an explicit `operator()` implementation:

```cpp
template<typename TFunc>
struct AdderDecorator
{
    TFunc decoratee;
    AdderDecorator(TFunc decoratee) : decoratee{decoratee} { }

    int operator()()
    {
        int result{2};
        result += decoratee();
        result += 20;
        return result;
    }
};

auto future = std::async(AdderDecorator{[]() { return 20; }});
std::cout << future.get(); // 42
```

Wrapping the function object instead of the future allows us to do pre- and post-processing of the result in the same thread the function executes in, which might be more beneficial in some cases.

I'm sure that at this point you could come up with many more ways to chain futures together, and bridge the gap until the C++ standard library provides a more convenient solution.

## Finishing Words

Since C++ 11, the standard library offers a great albeit slim set of types and functions to work with asynchronous operations. It us allows to make use of multi-threading without thinking too hard about concrete threads or synchronization primitives.

On a more personal note: This has been my first post on this blog, so I'm sure there's a lot that could be improved. I'm also by no means an expert in C++, so you might find some inaccuracies. If you have any feedback, please don't hesitate to let me know in the comments.
