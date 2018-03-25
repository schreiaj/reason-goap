open Jest;
open Expect;

open Goap;

let w  = [{name: "foo", value: false}, {name: "bar", value: true}];
let w2  = [{name: "foo", value: true}, {name: "bar", value: false}];
let a = {name: "Change Foo", preconditions: [{name: "bar", value: true}], results: [{name:"foo", value: true}, {name: "bar", value: false}], cost: 2};
let a2 = {name: "Change Bar", preconditions: [{name: "foo", value: true}], results: [{name:"bar", value: true}, {name: "foo", value: false}], cost: 1};

let testActor = {actions: [a, a2], name: "Test Actor"};
let testActor2 = {actions: [a], name: "Test Actor"};

describe("action sorting", () => {
  test("actions should be sorted by cheapest ones first", () => {
    let actions = Goap.prioritizeActions([a,a2]);
    expect(List.hd(actions)) |> toEqual(a2);
  })
});

describe("stateIsValid", () => {
  test("valid state", () => {
    expect(Goap.stateIsValid(w, {name: "bar", value: true})) |> toBe(true);
  });
  test("invalid state", () => {
    expect(Goap.stateIsValid(w, {name: "bar", value: false})) |> toBe(false);
  });
});

describe("actionIsValid", () => {
  test("valid action", () => {
    expect(Goap.actionIsValid(w, a)) |> toBe(true);
  });
  test("invalid action", () => {
    expect(Goap.actionIsValid(w, a2)) |> toBe(false);
  });
});

describe("findValidActions", () => {
  test("hasValidActions", () => {
    expect(Goap.findValidActions(w, [a, a2])) |> toEqual([a]);
  });
  test("has no valid actions", () => {
    expect(Goap.findValidActions(w, [a2])) |> toEqual([]);
  });
});

describe("world equality", () => {
  test("assert worlds are equal", () =>{
    expect(Goap.checkWorld(w,w)) |> toEqual(true);
  });
  test("assert worlds are not equal", () =>{
    expect(Goap.checkWorld(w,w2)) |> toEqual(false);
  });
});

describe("prioritizePlans properly sorts plans", () => {
  test("plans sort sanely", () => {
    let (_, cost, _) = Goap.prioritizePlans([([], 1, true), ([], 5, true), ([], 3, true)]);
    expect(cost) |> toEqual(1)
  });
});
