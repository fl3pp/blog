---
title: An Introduction to Algebraic Type Systems
slug: /csharp-algebraic-type-systems/introduction
date: '2025-03-05'
tags:
- CSharp
- dotnet
---

<span class="lighter">
This post is part of a series on algebraic type systems in C#. A navigation of the series can be found under <a href="/csharp-algebraic-type-systems">Algebraic Type Systems in C#</a>. In this part, we'll get to know what algebraic type systems are, and why they are useful. We will not dive into C# related topics, but rather focus on the concept of algebraic type systems in general.
</span>

Before we begin, I want to note that this article is aimed at beginners unfamiliar with algebraic type systems. I may omit details or simplify concepts to make them more approachable, and do thus not claim to be fully accurate. However, we'll dive deep enough to build an understanding of what algebraic type systems are and how you can use them in practice. If you're already familiar with algebraic type systems, I recommend skipping this article.

## High-Level Definition

To start with, let's rip the band-aid right off and start with a definition:

> An algebraic type system allows users to define new types by combining other types. We'll call the new types _composite_ types, and the types they consist of _constituent_ types. A typical algebraic type system features two ways of creating composite types, which are _product types_ and _sum types_.

This definition may sound a bit abstract, but you're most likely already very familiar with at least some terms: A _composite_ type is, simply put, a type that is defined by combining other types. This definition includes basically all non-primitive types, such as classes, structs, and enums. _Constituent_ types are types a composite type consists of, such as the types of fields.

In the next sections we'll explore the terms of _product_ and _sum_ types, as that's where it gets really interesting.

### Product Types

Product types are easier to understand than sum types. In fact, product types are very likely what you're thinking of when you're imagining a composite type.

> An instance of a product type features a value _for each_ constituent type.

Depending on the implementation, the constituent types may be named, in which case they are commonly referred to as _fields_.

The simplest way to create product types in most languages is through tuples. Traditional classes also fall into this category of product types, so do structs, records, and similar constructs.

_Example:_ A type `Person` could be defined as a product type from the composites `string` and `int`, for a person's name and age respectively. An instance of `Person` would then feature a `string` value and an `int` value at the same time. As pseudocode, this could be written as:

```
type Person = { Name: string; Age: int }
```

### Sum Types

Sum type are a bit more unintuitive than product types:

> An instance of a sum type takes only a _single_ value from any of the constituent types. The specified types are regarded as _variants_.

Example: A sum type `Shape` could be defined from constituent types `Circle` and `Rectangle`, both of which would be composite types as well. An instance of a `Shape` would then either be a `Circle` or a `Rectangle` variant, but not both at the same time. As pseudocode, this could be written as:

```
type Circle = { Radius: float }
type Rectangle = { Width: float; Height: float }
type Shape = Circle | Rectangle
```

Sum types appear in many forms. However, there is a specific kind of sum type that is particularly useful, which is called a _discriminated union_. We'll explore this concept in more detail in [Discriminated Unions](#discriminated-unions), but first, let's take a moment to think about the nomenclature we've just learned.

## Why the mathy terms?

The theory of types draws from mathematical fields, more specifically, a field called _category theory_. Even though this relationship between real-world programming and theoretical logic can be very intriguing, it tends to, in my opinion, create confusion and unclarity, particularly for beginners.

Functional programming in particular is known for its heavy use of mathematical foundations, making the learning curve for newcomers or real-world practitioners, in my opinion, higher than necessary.

Still, I want to take a shot at explaining the terms we've looked at in simple words, and try to make them more approachable. If you aren't concerned with the terminology, feel free to skip this section. I will not base any explanation on category theory, but try to draw parallels to simple set theory instead.

### Algebraic Types through Set Theory

Let's try to think of a type as a set of possible values it can take. For example, the type `uint8` can represent any number between 0 and 255. The cardinality of this set is 256, as there are 256 possible distinct values.

```
 uint8  = /* 8 bit unsigned integer */
|uint8| = 256
```

If we were to create a product type from two `uint8` constituent values to, e.g., form a rectangle, then we could create 256 **`*`** 256 = 65536 different rectangles. The cardinality of the product type is thus the product of the cardinalities of the constituent types.

```
 Rectangle  = { Width: uint8; Height: uint8; }
|Rectangle| = |uint8| * |uint8| = 256 * 256 = 65536
```

We could then take this rectangle and combine it with a circle type which consists of a single `uint8` radius value to form a sum type for a shape.

This shape type would then have 65'536 different rectangle representations and 256 different circle representations, for a total of 65'536 **`+`** 256 = 65'792 different shapes.

```
 Circle  = { Radius: uint8 }
|Circle| = 256
```

```
 Shape = Rectangle | Circle
|Shape| = |Rectangle| + |Circle| = 65536 + 256 = 65792
```

The cardinality of a sum type is thus defined as the sum of the cardinalities of the constituent types.

I hope that this explanation makes the terms more approachable. If you're more interested in the mathematical background, I recommend to delve take a look at category theory. But be warned: it can get quite complicated and abstract really fast.

## Discriminated Unions

Finally, let's get to the teased discriminated unions. Discriminated unions are a specific kind of sum types:

> A discriminated union is a sum type where the variant of an instance is clearly defined by a _discriminator_, which is usually an identifier or a tag.

Of course, users should be able to define their own discriminated unions for a language to feature a 'true' algebraic type system ([which we'll discuss later](#true-algebraic-type-systems)).

You can probably imagine that only selected languages support discriminated unions. Most notably, functional languages relly heavily on discriminated unions, leading to a common belief that algebraic type systems are a purely functional concept. However, there are noteworthy non functional-first languages that reap the benefits of discriminated unions, such as Rust and Swift.

### What Discriminated Unions are _not_

I imagine that the definition above is not quite satisfying if you've never worked with discriminated unions before. You may believe that you've encountered them in some form or another before, but that's not necessarily the case.

To clarify and prevent confusion, let's look at some common constructs that *are not* discriminated unions:

- _Enums_ are collections of named constants, but they don't carry dynamic values and require all cases to represent values of the same types.

- _Inheritance_ implements a form of subtyping polymorphism, where subtypes can fulfill the role of their supertypes while extending them. However, the supertype is not defined through its subtypes, and is deliberately unaware of its various implementations.

- Plain _union types_, as they are available in similar form in C and TypeScript, are close to discriminated unions but do not feature a built-in way to distinguish between the different cases. This is why the term _discriminated_ is important and non-optional.

As we'll explore in [Sum Type Trickery](#sum-type-trickery), the features I've just mentioned can be bent to behave like discriminated unions. However, at this point, I would like to make sure that you don't confuse sum types as being equivalent to any of these constructs, and consider them to be a separate concept in their own right.

### Samples of Discriminated Unions

Now that we've cleared what discriminated unions are not, let's look at some examples from languages that do support them by implement the familiar `Shape` example:

- As one of the most prominent functional languages, Haskell supports discriminated unions through the `data` keyword. \
  Almost all functional languages stemming from the ML family, F# and OCaml, support a very similar syntax.

```haskell
data Shape = Rectangle { width :: Float, height :: Float }
           | Circle { radius :: Float }
```

- Rust, a low-level language aimed at making system programming more safe, uses the `enum` keyword to define discriminated unions.

```rust
enum Shape {
    Rectangle { width: f32, height: f32 },
    Circle { radius: f32 },
}
```

- As a modern general-purpose language developed by Apple, Swift also supports discriminated unions also through the `enum` keyword.

```swift
enum Shape {
    case rectangle(width: Float, height: Float)
    case circle(radius: Float)
}
```

The classic object-oriented languages, such as C#, Java, and C++, do not support discriminated unions out of the box. However, the series this post is part of is concerned with algebraic type systems in C#, so naturally we'll explore this topic in more depth in the upcoming parts.

## 'True' Algebraic Type Systems 

The theoretical concept of sum types is extremely open. Example: Some languages, regard constants as types of their own, such as TypeScript, where they are called 'literal types'. The `true` and `false` constants could then be considered as the constituent types of the sum type `bool`.

While this is a valid interpretation of sum types, it's not very useful in practice. It's about as useful as calling C a high-level language because it's not assembly, or Java a functional language because it features higher-order functions.

As promised, we're going to focus on the practicality of algebraic type systems. Thus, from this point on and throughout the series, we'll only consider discriminated unions as sum types required for a language to feature an algebraic type system.

According to this definition, languages such as C# and TypeScript do not feature algebraic type systems, even if [Wikipedia says so](https://en.wikipedia.org/wiki/Algebraic_data_type).

This point can cause a bit of controversy, as some people argue in one or the other way. We're taking the easy way out by making up our own definition because we're focused on _practical_ algebraic type systems, not _theoretical_ ones. Just keep in mind that the theoretical definition is broader, and we're good to go.

## Typical Features

I hope that we've now cleared up what we regard as algebraic type systems. However, until now, we've looked at the concept from a definition standpoint only, and haven't yet considered the 'client' side if you will, or how working with algebraic types should feel like. Of course, this is ends in language features to complement the concept.

Fortunately, the list of 'necessary' features is quite short and can be summarized to a single point: _Pattern matching_.

### Pattern Matching

### Exhaustive Patterns

Such types are usually unable to contain behavior, but can be written in a highly expressive and terse syntax. 

## Relevancy for Pragmatists
