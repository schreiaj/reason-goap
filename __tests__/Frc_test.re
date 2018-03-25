/* #use "./src/Goap.re"; */
open Goap;
open Jest;
open Expect;

let worldState = [
  {name: "Scale is Blue", value: false},
  {name: "Scale is Red", value: false},
  {name: "Red Switch Owned", value: false},
  {name: "Blue Switch Owned", value: false},
  {name: "Is at HP", value: false},
  {name: "Has Cube", value: false}
];

let goalState = [
  {name: "Scale is Blue", value: true},
  {name: "Scale is Red", value: false},
  {name: "Red Switch Owned", value: false},
  {name: "Blue Switch Owned", value: false},
  {name: "Is at HP", value: false},
  {name: "Has Cube", value: false}
];

let actions = [
  {name: "Score on Blue Scale", preconditions: [
    {name: "Has Cube", value: true}
  ], results: [
    {name: "Has Cube", value: false},
    {name: "Scale is Blue", value: true}
  ], cost: 5},
  {name: "Get Cube From HP", preconditions: [
    {name: "Has Cube", value: false}
  ], results: [
    {name: "Has Cube", value: true}
  ], cost: 5},
  {name: "Get Cube From Pile", preconditions: [
    {name: "Has Cube", value: false}
  ], results: [
    {name: "Has Cube", value: true}
  ], cost: 3}
];


describe("find path", () => {
  test("assert a plan was created", () =>{
    let (actions,cost, valid) = Goap.planDFS(actions, worldState, goalState, 10, []);
    Js.log(actions);
    expect((cost, valid)) |> toEqual(((8, true)));
  });
});
