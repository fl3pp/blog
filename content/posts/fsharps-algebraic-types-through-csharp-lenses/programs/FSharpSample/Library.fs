namespace FSharpSample

type Cirlcle = { Radius: float }

module Say =
    let hello name =
        printfn "Hello %s" name
