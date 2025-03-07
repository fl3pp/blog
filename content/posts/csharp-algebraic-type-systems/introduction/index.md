---
title: An Introduction to Algebraic Type Systems
slug: /csharp-algebraic-type-systems/introduction
date: '2025-03-05'
tags:
- CSharp
- dotnet
---

<span class="lighter">
This post is part of a series on algebraic type systems in C#. A navigation of the series can be found under <a href="/csharp-algebraic-type-systems">Algebraic Type Systems in C#</a>.
</span>

In this part, we'll get to know what algebraic type systems are, and why they are useful. We will not dive into C#, but rather focus on the concept of algebraic type systems in general.

Note that I do not claim to be an expert on the topic, and that I may omit details or simplify concepts to make them more approachable. However, we'll dive deep enough into the topic to build a solid understanding of what algebraic type system.

To start with, let's rip the band-aid right off and start with a definition:

> An algebraic type system allows users to define new types by combining other types. We'll call the new types _composite_ types, and the types they consist of as _constituent_ types. A typical algebraic type system features two ways of creating composite types, which are _product types_ and _sum types_.

This definition may sound a bit abstract, but you're most likely already very familiar with at least some terms: A _composite_ type is simply a type that is defined by combining other types. This definition basically includes all non-primitive types, such as classes, structs, and enums. _Constituent_ types are types a composite type consists of. In the next sections, we'll explore the terms of _product_ and _sum_ types, as that's where it gets really interesting.

## Product Types

Product types are the easier to understand than sum types. In fact, product types are undoubtedly what you're probably imagining when you think of a composite type.

> An instance of a product type features a value _for each_ constituent type.

Depending on the implementation, the constituent types may be named, in which case they may be called _fields_.

The simplest way to create product types in most languages is through tuples. Traditional classes also fall into this category of product types, so do structs, records, and similar constructs.

_Example:_ A type `Person` could be defined as from the composite of the types `string` and `int` for the person's name and age. An instance of `Person` would then feature a `string` and an `int`. As pseudocode, this could be written as:

```
type Person = { Name: string; Age: int }
```

## Sum Types

Sum type may be a bit more unintuitive than product types, as you've maybe not yet encountered their full power in your favorite OOP language.

> An instance of a sum type takes only a _single_ value from any of the constituent types. The specified types are regarded as _variants_, and are commonly named.

Example: A sum type `Shape` could be defined from constituent types `Circle` and `Rectangle`, both of which may be sum types. An instance of a `Shape` would then either be a `Circle` or a `Rectangle` variant, but not both at the same time. As pseudocode, this could be written as:

```
type Shape = Circle { Radius: float }
           | Rectangle { Width: float; Height: float }
```

### Discriminated Unions

The theoretical concept of sum types is extremely open.

Example: Some languages, such as TypeScript, regard constants as types of their own. The `true` and `false` constants (in TypeScript 'literal types') could then be considered as the constituent types of the sum type `bool`.

However, the theoretical definition does not provide a meaningful distinction to work with. It's about as useful as calling C a high-level language because it's not assembly.

In practice, I would allow a language to claim an algebraic type system only if it features _discriminated unions_. Discriminated unions are a narrower definition of sum types.

> A discriminated union is a sum type where each variant is named, and carries no value or exactly one value of a specified type.

Of course, users should be able to define their own discriminated unions.

From now on, we will only consider discriminated unions when we talk about sum types. Just keep in mind that the theoretical definition is broader. From now on, a language that features discriminated unions can be said to have a algebraic type system (as it's highly unlikely such a language wouldn't feature product types, we can disregard those).

### What Discriminated Unions are _not_

Classic OOP languages usually don't feature discriminated unions directly. **Do not** confuse features that you are familiar with for fully featured discriminated unions:

- _Enums_ are collections of named constants, but they don't carry dynamic values and require all cases must represent values of the same types.

- _Inheritance_ implements a form of subtyping polymorphism, where subtypes can fulfill the role of their super types while extending them. However, the super type is not defined by a collection of its subtypes, and is often unaware of its possible subtypes.

- _Union types_, as they are available in e.g., C, do not feature a built-in way to distinguish between the different cases. Now you see why the _discriminated_ part is important.

Even though all of these constructs have relationships to sum types, they are not equivalent. And they surely aren't discriminated unions.

In the following articles, we'll explore some tricks you can apply to emulate discriminated unions, specifically in C#.

As we'll explore in [Sum Type Trickery](#sum-type-trickery), the features I've just mentioned can be bent to behave like 'real' sum types. The code emitted by compilers to represent sum types may even use these aforementioned features. However, at this point, I would like to make sure that you don't confuse sum types as being equivalent to any of these constructs, and think of them as a separate concept.

## Why the mathy terms?

Functional programming tends to draw from mathematical concepts, and algebraic types are no exception. Even though this relationship between real-world programming and theoretical logic can be very intriguing, it tends to, in my opinion, create more confusion than clarity, particularly for beginners.

Still, I want to take a shot at explaining the terms in simple words, and try to make them more approachable. If you aren't concerned with the terminology, feel free to skip this section.

Let's try to think of a type as a set of possible values it can take. For example, the type `uint8` can represent any number between 0 and 255. The cardinality of this set is thus 256, as there are 256 possible distinct values.

```
 uint8  = /* 8 bit unsigned integer */
|uint8| = 256
```

If we were to create a product type from two `uint8` values to, e.g., form a rectangle, then we could create 256 **`*`** 256 = 65536 different rectangles. The cardinality of the product type is thus the product of the cardinalities of the constituent types.

```
 Rectangle  = { Width: uint8; Height: uint8; }
|Rectangle| = |uint8| * |uint8| = 256 * 256 = 65536
```

We could then take this rectangle, and combine it with a circle type which consists of a single `uint8` radius value, to form a sum type for a shape. This shape type would then have 65'536 different rectangle representations and 256 different circle representations, for a total of 65'536 **`+`** 256 = 65'792 different shapes.

```
 Circle  = { Radius: uint8 }
|Circle| = 256
```

```
 Shape = Rectangle | Circle
|Shape| = |Rectangle| + |Circle| = 65536 + 256 = 65792
```

I hope that this explanation makes the terms more approachable. If you're interested in the mathematical background, I recommend looking into type theory, but be warned that it can get quite complicated and abstract really fast.

## Typical Features

Now that my rant is over, let's look at some typical features of nicely implemented sum types:

Such types are usually unable to contain behavior, but can be written in a highly expressive and terse syntax. 