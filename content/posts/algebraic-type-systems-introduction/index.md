---
title: An Introduction to Algebraic Type Systems
subtitle: A language agnostic introduction to algebraic type systems for everyday programmers.
slug: algebraic-type-systems-introduction
date: '2025-03-05'
tags:
- algebraic-type-systems
---

This article is aimed at developers who haven't yet had the joy of working with algebraic type systems. We will explore what algebraic type systems are, how they appear in language features and how they can tackle real-world problems.

It is not aimed at complete programming beginners, but rather at developers who want to expand their horizon with this powerful concept. 

## What this piece is about

Before we begin, I want to emphasize that I'm not qualified enough to write a comprehensive guide on any type system. I may omit details or simplify things to make it more approachable, and do not claim to remain completely accurate on all counts.

The theoretical background will be covered far enough to enable you to translate it into practical use cases. Full accuracy is however not the goal of this article.

If you're already familiar with algebraic type systems or with the broader area of functional programming, I recommend skipping this page, as you're not likely to learn anything new.

I appreciate feedback of any kind, so please let me know if you think I've missed something important or contradict your understanding.

## High-Level Definition

To start with, let's rip the band-aid right off and start with a definition:

> Algebraic type systems allows users to define new types by combining types. We'll call the new types _composite_ types, and the types they consist of _constituent_ types. A typical algebraic type system features two ways of creating composite types, which are _product types_ and _sum types_.

This definition may sound a bit abstract, but you're most likely already familiar with at least some terms: A _composite_ type is, simply put, a type that consists of one or more values. This definition includes basically all non-primitive types, such as classes, structs, and some enum implementation. _Constituent_ types are types a composite type consists of, such as the types of fields.

In the next sections we'll explore the terms of _product_ and _sum_ types, as that's where it gets really interesting.

### Product Types

Product types are very likely what you're thinking of when you're imagining a composite type:

> An instance of a product type features a value _for each_ constituent type.

The constituent types may be named, in which case they are commonly referred to as _fields_.

The simplest way to create product types in most languages is through tuples. Traditional classes also fall into this category of product types, so do structs, records, and similar constructs.

_Example:_ A type `Person` could be defined as a product type from the composites `string` and `int` for a person's name and age respectively. An instance of `Person` would then feature a `string` value and an `int` value at the same time. As pseudocode, this could be written as:

```
type Person = { Name: string; Age: int }
```

### Sum Types

Sum type are a bit more unintuitive than product types, but still not unreasonably complex:

> An instance of a sum type takes a _single_ value from any of the constituent types. The specified types are regarded as _variants_.

Example: A sum type `Shape` could be defined from the constituent types `Circle` and `Rectangle`, both of which would be composite types as well. An instance of a `Shape` would then either be a `Circle` or a `Rectangle` variant, but not both at the same time. As pseudocode, this could be written as:

```
type Circle = { Radius: float }
type Rectangle = { Width: float; Height: float }
type Shape = Circle | Rectangle
```

Sum types appear in many forms, but there is a specific kind of sum type that is particularly useful, called a _discriminated unions_. We'll explore this concept in more detail in [Discriminated Unions](#discriminated-unions), but first, let's take a moment to think about the nomenclature we've just learned.

## Why the Mathy terms?

The theory of types can be quite daunting and be surprisingly complex. It lives somewhere between computer science and mathematics, in fields such as category theory.

Although the relationship between real-world programming and theoretical logic can be very intriguing, it's impact on practical matters is somewhat limited. It also tends to make concepts seem more complex than necessary, particularly for beginners. Everybody that took that initial learning curve into Haskell will know what I mean. 

However, I feel like we can draw a simple parallel between the terms _product_ and _sum_ types and simple set theory. Thinking of types as sets of possible values can help to understand the power and flexibility of algebraic type systems.

If you aren't concerned with the terminology, feel free to skip this section. It won't be relevant for the rest of the article, or for solving practical problems.

### Algebraic Types through Set Theory

Let's try to think of a type as a set of possible values it can take. The type `uint8`, for example, can represent any number between 0 and 255. The cardinality of this set is 256, as there are 256 possible distinct values.

```
 uint8  = /* 8 bit unsigned integer */
|uint8| = 256
```

Now let's combine two `uint8` values to form a product type `Rectangle`. An instance of a `Rectangle` could then be represented by any combination of two `uint8` values, which means that there are 256 **`*`** 256 = 65536 unique rectangles possible.

```
 Rectangle  = { Width: uint8; Height: uint8; }
|Rectangle| = |uint8| * |uint8| = 256 * 256 = 65536
```

The cardinality of a product type is thus the product of the cardinalities of the constituent types.

Before we examine sum types, let's add the `Circle` type to the mix, which contains a single `uint8` value for its radius.

```
 Circle  = { Radius: uint8 }
|Circle| = 256
```

We can now define the aforementioned `Shape` type, which is the sum type consisting of the constituent types `Rectangle` and `Circle`.

```
 Shape = Rectangle | Circle
|Shape| = |Rectangle| + |Circle| = 65536 + 256 = 65792
```

This `Shape` type could then take on 65'536 unique rectangle representations and 256 unique circle representations, for a total of 65'536 **`+`** 256 = 65'792 different shapes.

The cardinality of a sum type is thus defined as the sum of the cardinalities of the constituent types.

## Discriminated Unions

Finally, let's get to the discriminated unions. Discriminated unions are a specific kind of sum types:

> A discriminated union is a sum type where the variant of an instance is clearly defined by a _discriminator_, which is usually an identifier or a tag.

This means that we can make out which variant an instance of a discriminated union takes by looking at a discriminator value features by every instance.

You can probably imagine that only selected languages support discriminated unions. Most notably, many functional languages rely heavily on discriminated unions, leading to a common belief that algebraic type systems are a purely functional concept. However, there are noteworthy non functional-first languages that reap the benefits of discriminated unions, such as Rust and Swift.

### What Discriminated Unions are _not_

After reading the previous introduction, you may believe that you've encountered them in some form or another before. But that's not necessarily the case.

To clarify and prevent confusion, let's look at some common constructs that *are not* discriminated unions:

- _Enums_, as encountered in e.g., C#, are collections of named constants, but they can't carry non-constant values and require all cases to represent values of the same types.

- _Inheritance_ implements a form of sub typing, where subtypes can fill in for their super-types while extending them with new behavior. The supertype is however not defined through its subtypes, and is often deliberately unaware of its various implementations.

- Plain _union types_, as they are available in a similar form in C and TypeScript, are close to discriminated unions but do not feature a built-in way to distinguish between the different cases. This is why the term _discriminated_ is important and non-optional.

Some languages may provide features that blur the lines between what is a sum type or not. Discriminated unions on the other hand are stricter in their definition and therefore more difficult to mistake for something else.

Other languages utilize these constructs internally to implement discriminated unions. We can appreciate these efforts as proof that these constructs are indeed capable of implementing sum types. But still, only discriminated unions are what we care about for practical algebraic type systems.

### Samples of Discriminated Unions

Now that we've cleared what discriminated unions are not, let's look at some examples from languages that do support. We'll re-implement the `Shape` example from before in a few languages:

Haskell
: As one of the most prominent functional languages, Haskell supports discriminated unions through the `data` keyword. \
  Almost all functional languages stemming from the ML family, such as F# and OCaml, support a similar syntax.

```haskell
data Shape = Rectangle { width :: Float, height :: Float }
           | Circle { radius :: Float }
```

Rust
: , a low-level language aimed at making system programming more safe, uses the `enum` keyword to define discriminated unions.

```rust
enum Shape {
    Rectangle { width: f32, height: f32 },
    Circle { radius: f32 },
}
```

Swift
: As a modern general-purpose language developed by Apple, Swift also supports discriminated unions through the `enum` keyword as well.

```swift
enum Shape {
    case rectangle(width: Float, height: Float)
    case circle(radius: Float)
}
```

The classic object-oriented languages, such as C#, Java, and C++, do not support discriminated unions out of the box. However, there are ways to emulate them, with varying degrees of success. I'll might cover some tricks in the future under the [#algebraic-type-systems](/tags/algebraic-type-systems) tag.

## 'True' Algebraic Type Systems 

The theoretical concept of sum types is extremely open.

Example: Some languages regard constants as types of their own, such as TypeScript, where they are called 'literal types'. The `true` and `false` constants could then be considered as the constituent types of the sum type `bool`.

While this is a valid interpretation of sum types, it's not very useful in practice. It's about as useful as calling C a high-level language because it's not assembly, or Java a functional language because it supports higher-order functions.

As promised, we're going to focus on the practicality of algebraic type systems. Thus, we'll only consider discriminated unions as the sum types required for a language to feature a 'true' algebraic type system.

According to this definition, languages such as C# and TypeScript do not feature algebraic type systems, even if [Wikipedia says so](https://en.wikipedia.org/wiki/Algebraic_data_type) and is technically correct.

This point can cause a bit of controversy, as some people argue in one or the other way. We're taking the easy way out by making up our own definition because we're focused on _practical_ algebraic type systems, not _theoretical_ ones. Just keep in mind that the theoretical definition is broader, and we're good to go.

## Typical Features

I hope that we've now cleared up what to regard as a typical algebraic type system. However, until now, we've only looked at the concept from a definition standpoint, and haven't yet considered the 'client-side' if you will, or how working with algebraic types should feel like. This will of course end in even more language features to complement the concept.

Fortunately, the list of typical features is quite short and can be summarized in a single point: _Pattern matching_.

### Pattern Matching

Pattern matching is a language feature which allows destructing a value by matching it against a given set of patterns which specify a possible form of the value. The patterns are tried in order, and the first one that matches the given value is executed.

Each pattern is associated with an expression that is called if the pattern matches. The pattern is able to capture parts of the value and offer them to the expression to work with.

It's actually easier than it sounds like. Let's look at a simple example in F#:

```fsharp
type Shape = Rectangle of width : float * height : float
           | Circle of radius : float
let rectInstance = Rectangle(width = 10.0, height = 20.0)

let area = match rectInstance with
           | Rectangle(width = w; height = h) -> w * h
           | Circle(radius = r) -> System.Math.PI * r * r
// val area : float = 200.0
```

This snippet might contain lots of unfamiliar syntax, but it's actually quite simple and nothing we've not already discussed.

The first block defines a discriminated union named `Shape`, which consists of the variants `Rectangle` and `Circle`. Both variants contain fields which are named as well. Then a `Rectangle` instance is created with a width of 10.0 and a height of 20.0.

The actual pattern matching doesn't happen until the second part. The `match` and `with` keywords surround a variable to start a pattern matching expression, and are followed by a set of patterns separated by `|` characters. The patterns then consist of the variants and their fields, which are captured in the variables `w`, `h` and `r`. Finally, each pattern ends in an expression that determines the result of the expression if the pattern matches.

It may help to take a look at a similar example written in C#, albeit without the pleasure of discriminated unions:

```csharp
Shape rectInstance = new Rectangle(10, 20);

var area = rectInstance switch
{
    Rectangle { Width: var w, Height: var h } => w * h,
    Circle { Radius: var r } => System.Math.PI * r * r,
    _ => throw new InvalidOperationException(),	
};

record Shape;
record Rectangle(float Width, float Height) : Shape;
record Circle(float Radius) : Shape;
```

As you can see, C# made a big step towards algebraic type systems with the introduction of records and pattern matching. However, it's still not quite there, as we cannot define discriminated unions (yet?).

Most pattern matching implementations offer many more features, which we won't explore any further. We're going to keep focused on algebraic type systems, and pattern matching is just a tool to work with them.

However, there is one crucial feature related to discriminated unions and pattern matching we want to take a closer look at.

### Exhaustive Patterns

If you're coming from an OOP background, you might be kicking and screaming at the thought of coupling the cases of a type to their super type (although if you are, it seems unlikely that you've come this far). It is a direct violation of the open-closed principle, and that's a valid concern.

I suggest to look at it from a different angle: Algebraic type systems open up a new way of thinking about types, and their use cases differ from classic OOP inheritance hierarchies. We'll take a closer look at this in the next part.

Fortunately, there is a compiler feature that alleviates this issue: _Exhaustive patterns_. Exhaustive pattern matching means that the compiler can tell whether you've covered all possible cases a value can take, and alert you if you haven't. You are thus also not forced to add a default case to your pattern matching.

This is especially useful when you're working with discriminated unions, as you can be sure that you've handled all cases. If we were to say, introduce a new variant to the `Shape` type at a later point, the compiler would tell us where we've not yet updated our pattern matching expressions:

```fsharp
type Shape = Rectangle of width : float * height : float
           | Circle of radius : float
           | RightAngledTriangle of width : float * height : float
let rectInstance = Rectangle(width = 10.0, height = 20.0)

let area = match rectInstance with
           | Rectangle(width = w; height = h) -> w * h
           | Circle(radius = r) -> System.Math.PI * r * r
// warning FS0025: Incomplete pattern matches on this expression.
// For example, the value 'RightAngledTriangle (_, _)' may indicate a
// case not covered by the pattern(s)
```

By relying on exhaustive patterns, you can be sure that you've always handled all variants. If you were to introduce a new variant to the `Shape` or remove an existing one, you'd receive an immediate list of all places you need to update from the compiler. This enables you to rely on a strongly typed domain model, which we'll cover in just a bit. 

## Relevancy for Pragmatists

Chapeau for making it this far. This article might have been a bit of a stretch if you've never worked with algebraic type systems before as it is a complex topic and unlikely to stick in a single reading.

The good news is that you've made it through the theoretical bits and at least got familiar with algebraic type systems, discriminated unions, and their relationships to language features.

I want to finish this article with a few thoughts on the practicality of algebraic type systems. Most importantly, I want to address some use cases of algebraic type systems for practical everyday programming.

There are two use-cases in which I believe that algebraic type systems are particularly useful:

### Domain Modelling

Algebraic type systems are a great way to put your domain model into the center of your application. The idea is to create lots of types to represent your application's domain, and build your logic around them.

These types are optimally defined as short and concise as possible, so that you can wrap them up in just a few central files. If your language supports a typical algebraic type system, it should easily be possible to define tens of such types right next to each other.

A huge benefit of this approach is that you can rely on the compiler to enforce your domain model. If you were to add or remove a part of your domain model, it would cause a ripple effect throughout your codebase.

You might think that all of this is possible with object-oriented programming as well, and you're right.

Most importantly, I'll try to pit them against the classic object-oriented approach:

- The real world is difficult to break down into a few types. To make matters much worse, OOP languages forbid you to know which types you're actually dealing with at runtime. Unfortunately, this is not how the real world works. To name a few examples: Networking protocols often communicate through packets of predefined types, carrying various payloads. 

To name a few examples: Networking protocols often communicate through packets of predefined types, carrying various payloads.  

How are you supposed to model this in an object-oriented language?

Just think of it this way: Object-oriented languages allow you to model types that inherit from each other. But in you're code, you're not allowed to know which types 

However, , nevermind the trend to _not_ use this classic feature of OOP.

Scott Wlaschin wrote a great book on this topic, called [Domain Modeling Made Functional](https://pragprog.com/titles/swdddf/domain-modeling-made-functional/). It is a true gem and I highly recommend it.

### General Purpose Wrappers

Algebraic type systems are a great way to create general-purpose wrapper types, which quickly add effects to existing types. A common kind of such types is the `Option` wrapper, which can be implemented as a sum type with `Some` and `None` variants. This basic construct is powerful enough to combat the infamous `null` reference problem in a strongly typed manner. Such types can quickly become one of the foundations of your codebase.

If a specific set of supporting functions is provided, they are commonly referred to as _monads_. 

```fsharp
type Option<'a> = Some of 'a | None
```
