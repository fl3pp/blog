---
title: F# as C#'s missing algebraic type system
subtitle: Leveraging F# to work with algebraic data types in C# through IL
slug: fsharp-as-csharps-missing-algebraic-type-systme
date: '2025-03-05'
tags:
- F#
- C#
- dotnet
---

Although functional programming still doesn't seem to move the masses (at least not in my circles), some features traditionally found in functional programming languages begin to make their way into mainstream languages. One of these features are _algebraic type systems_.

In this post, we'll explore what algebraic type system are in (hopefully) simple terms, why they are useful, and how we can leverage F# to work with them in C#.

## Algebraic Type Systems

An algebraic type system allows to define new types by combining collections of types, which we'll call _constituent_ types, in one of two ways:

### Product Types

An instance of the new type features a value _for each_ constituent type. Depending on the implementation, the constituent types may be named, in which case they may be called _fields_.

The simplest way to create product types in most languages is through tuples. Traditional classes also fall into this category of product types, so do structs, records, and similar constructs.

_Example:_ A type `Person` could be defined as a collection of the types `string` and `int` for the person's name and age. An instance of `Person` would then feature a `string` and an `int`. As pseudocode, this could be written as:

```
type Person = { Name: string; Age: int }
```

### Sum Types

An instance of the new type takes only a _single_ value from any of the constituent types. The specified types could be regarded as _variants_ or _options_ of the new type.

Example: A sum type `Shape` could be defined as a collection of the types `Circle` and `Rectangle`, both of which are complex types themselves. An instance of a `Shape` would then either be a `Circle` or a `Rectangle`. As pseudocode, this could be written as:

```
type Circle = { Radius: float }
type Rectangle = { Width: float; Height: float }
type Shape = Circle | Rectangle
```

Classic OOP languages usually don't feature sum types directly. **Do not** confuse features that you are familiar with for fully featured sum types:

- _Enums_ are not sum types. They are collections of named constants, but they don't carry any additional information and all cases must represent values of the same types. \
  Sum types, however, are defined through a collection of other types, which may range from simple numerical values to complex objects.

- _Inheritance_ is not equivalent to sum types. Inheritance implements a form of subtyping polymorphism where subtypes can fulfill the role of their supertypes while extending them. However, the supertype is not defined by a collection of its subtypes, and is often not aware of its possible subtypes. \
   Sum types, on the other hand, are completely defined by their constituent types. It is typically not possible to specify an interface that all constituent types must implement, so clients must know which exact type they are working with.

- _Union types_, as they are available in e.g., C, are a form of sum types, but unlike fully featured sum types, unions do not feature a built-in way to distinguish between the different cases. Thus, sum types are sometimes also referred to as _tagged unions_ or _discriminated unions_.

As we'll explore in [Sum Type Trickery](#sum-type-trickery), the features I've just mentioned can be bent to behave like 'real' sum types. The code emitted by compilers to represent sum types may even use these aforementioned features. However, at this point, I would like to make sure that you don't confuse sum types as being equivalent to any of these constructs, and think of them as a separate concept.

### Why the mathy terms?

Functional programming tends to draw from mathematical concepts, and algebraic types are no exception. Even though this relationship between real-world programming and theoretical logic can be very intriguing, it tends to, in my opinion, create more confusion than clarity, particularly for beginners.

Still, I want to take a shot at explaining the terms in simple words, and try to make them more approachable. If you aren't concerned with the terminology, feel free to skip this section.

Let's try to think of a type as a set of possible values it can take. For example, the type `uint8` can represent any number between 0 and 255. The cardinality of this set is thus 256, as there are 256 possible distinct values.

```
 uint8  = /* 8 bit unsigned integer */
|uint8| = 256
```

If we were to create a product type from two `uint8` values to, e.g., form a rectangle, then we could create 256 **`*`** 256 = 65536 different rectangles. The cardinality of the product type is thus the product of the cardinalities of the constituent types.

```
 rectangle  = { Width: uint8; Height: uint8; }
|rectangle| = |uint8| * |uint8| = 256 * 256 = 65536
```

We could then take this rectangle, and combine it with a circle type which consists of a single `uint8` radius value, to form a sum type for a shape. This shape type would then have 65'536 different rectangle representations and 256 different circle representations, for a total of 65'536 **`+`** 256 = 65'792 different shapes.

```
 circle  = { Radius: uint8 }
|circle| = 256
```

```
 shape = rectangle | circle
|shape| = |rectangle| + |circle| = 65536 + 256 = 65792
```

I hope that this explanation makes the terms more approachable. If you're interested in the mathematical background, I recommend looking into type theory, but be warned that it can get quite complicated and abstract really fast.

### Sum Type Trickery

As you can imagine, there are indeed ways to implement sum types work in languages without built-in support:

- You can, for example, create tagged union types in C by using a `struct` for each case of a `union`, and add a tag value as the first field of each `struct` that distinguishes the case you're working with.

```c
union U {
   int kind;
   struct { int kind; char value [256]; } str;
   struct { int kind; long long value ; } ll;
};
```

- In C# you can create generic types that implement the necessary behavior internally. The [OneOf](https://github.com/mcintyre321/OneOf) library implements this approach.

```csharp
OneOf<Rectangle, Shape> value = new Rectangle(1, 2);
```

- Another approach also available in C# is to create a type hierarchy where the subtypes are nested within the supertype, with the supertypes constructor being private, making it impossible to add more subtypes. Some source generators, like [dunet](https://github.com/domn1995/dunet), can simplify this process.

```csharp
abstract record Shape
{
    private Shape() { }
    public sealed record Circle(double Radius) : Shape;
    public sealed record Rectangle(double Width, double Height) : Shape;
}
```

You may now think that my initial statements were wrong, and that it is indeed possible to create true sum types in traditional languages. Inheritance can be used after all, and traditional unions can be tagged.

While this may be true, I would argue that these approaches are cumbersome, error-prone, difficult to work with, and not idiomatic to their respective languages. The possibilities I've shown are not the only ones, it feels like there are endless ways to trick languages into supporting sum types, but none of them come even close to the simplicity and expressiveness of a language that natively supports them.

Next, we'll explore the features that a well-implemented algebraic type system usually offers.

### Typical Features

Now that my rant is over, let's look at some typical features of nicely implemented sum types:

Such types are usually unable to contain behavior, but can be written in a highly expressive and terse syntax. 
