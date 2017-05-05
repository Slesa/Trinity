// Learn more about F# at http://fsharp.org
// See the 'F# Tutorial' project for more help.
open Akka.FSharp
open Akka
open Akka.Actor

type Greet (who) as m = 
    member m.Who = who

type GreetingActor() as ga = 
    inherit ReceiveActor()
    do
        ga.Receive<Greet> (fun (greet: Greet) -> printfn "Hello %s!" greet.Who)

[<EntryPoint>]
let main argv = 
    let system = ActorSystem.Create "fsharp-system"
    let greeter = system.ActorOf<GreetingActor> "greeter"
    "World" |> Greet |> greeter.Tell
    System.Console.ReadLine() |> ignore
    0 // return an integer exit code
