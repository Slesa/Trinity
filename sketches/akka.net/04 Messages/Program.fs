﻿open Akka
open Akka.Actor
open Akka.FSharp

let system = System.create "system" <| Configuration.load()

let scalarValuePrinter (mailbox: Actor<_>) =
    let rec loop () = actor {
        let! message = mailbox.Receive ()
        match box message with
        | :? string as msg -> printfn "ScalarValuePrinter: received string %s" msg
        | :? int as msg -> printfn "ScalarValuePrinter: received int %i" msg
        | _ -> ()
        return! loop ()
    }
    loop ()

let scalarValuePrinterRef = spawn system "scalarValuePrinter" scalarValuePrinter

type Symbol = Symbol of string
type Money = Money of decimal
type OrderProcessorCommand =
    | ExecuteBuyOrder of portfolioId: string * symbol: Symbol * quantity: int * price: Money
    | ExecuteSellOrder of portfolioId: string * symbol: Symbol * quantity: int * price: Money
type OrderProcessorEvent =
    | BuyOrderExecuted of portfolioId: string * symbol: Symbol * quantity: int * price: Money
    | SellOrderExecuted of portfolioId: string * symbol: Symbol * quantity: int * price: Money

let orderProcessor (mailbox: Actor<_>) =
    let rec loop () = actor {
        let! message = mailbox.Receive ()
        match message with
        | ExecuteBuyOrder(i, s, q, p) -> 
            scalarValuePrinterRef <! "Received order";
            scalarValuePrinterRef <! i;
            scalarValuePrinterRef <! s;
            mailbox.Sender() <! BuyOrderExecuted(i, s, q, p)
        | ExecuteSellOrder(i, s, q, p) -> 
            scalarValuePrinterRef <! "Received sell";
            scalarValuePrinterRef <! i;
            scalarValuePrinterRef <! s;
            mailbox.Sender () <! SellOrderExecuted(i, s, q, p)
        return! loop()
    }
    loop ()


let caller orderProcessor (mailbox: Actor<_>) =
    let rec loop () = actor {
        let! message = mailbox.Receive ()
        match message with
        | BuyOrderExecuted(i, Symbol s, q, Money p) -> printfn "Caller: recevied BuyOrderExecuted %s %s %i %M" i s q p
        | SellOrderExecuted(i, Symbol s, q, Money p) -> printfn "Caller: recevied SellOrderExecuted %s %s %i %M" i s q p
        return! loop ()
    }
    orderProcessor <! ExecuteBuyOrder("1", Symbol "S1", 5, Money 10m)
    orderProcessor <! ExecuteBuyOrder("2", Symbol "S2", 3, Money 8m)
    loop ()

let orderProcessorRef = spawn system "orderProcessor" orderProcessor



[<EntryPoint>]
let main argv = 
    let callerRef = spawn system "caller" <| caller orderProcessorRef
    printfn "Press <RET>"
    System.Console.ReadLine () |> ignore
    0 // return an integer exit code
