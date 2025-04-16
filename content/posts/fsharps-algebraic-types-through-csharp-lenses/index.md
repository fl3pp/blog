---
title: F# algebraic types through C# lenses
subtitle: Understanding F# discriminated unions from a C# perspective
slug: fsharp-algebraic-types-through-csharp-lenses
date: '2025-04-16'
tags:
- C#
- F#
---

Algebraic types are one of my favorite programming languages features. They are predominantly found in functional languages, such as Haskell, Scala, and F#. They are a powerful way to model data, and in my opinion, it's a real shame that they are not more widely supported in mainstream OO-first languages such as C# or Java.

Fortunately, some functional languages feature a common compilation target with the mainstream languages, such as F# and C# with the IL format and the .NET runtime. This means that we can create algebraic types in F# and compile it into format that can be consumed by C#.

In this post, we'll take a look at how this translation works under the hoods, and how we can use F# as C#'s missing algebraic type system. We will not take deep dive into the technical details, and will also not take broader picture of algebraic type systems and their benefits. If you're not yet familiar with F# and / or algebraic type systems, I cannot recommend Scott Wlaschin's [F# for fun and profit](https://fsharpforfunandprofit.com/) enough.

We will only look at F#s [records](https://learn.microsoft.com/en-us/dotnet/fsharp/language-reference/records) and [discriminated unions](https://learn.microsoft.com/en-us/dotnet/fsharp/language-reference/discriminated-unions) to form an algebraic type system, even though F# features more ways to model data.

However, I feel like this combination is plenty powerful to get started with, and may be sufficient for many use cases. A particular scenario that I have in mind is to use F# algebraic type systems for domain modelling purposes, as described in [Domain Modeling Made Functional](https://pragprog.com/titles/swdddf/domain-modeling-made-functional/) (as well by Scott Wlaschin).

I will be using the .NET 9 SDK and Riders built-in decompiler for the examples. Your mileage may vary with other versions of .NET or decompilers. The API translation from F# to C# should however remain fairly stable. 

## F# Records in C# 

F# records are basically its equivalent to C# records. C# records are likely been inspired by F# records, just like many other features in C# (F# really is and was ahead of it's time). 

First, let's take a look at how to define record types in F#.

```fsharp
type Person = {
    Name: string,
    Age: int
}
```

## F# Discriminated Unions in C# 

## F# Options C# 

## Settings up a cross-language Compilation
