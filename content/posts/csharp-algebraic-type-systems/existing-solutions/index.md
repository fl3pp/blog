
## Sum Type Trickery

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