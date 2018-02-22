open Jest;
open Expect;

open Goap;

let w  = [{name: "foo", value: false}, {name: "bar", value: true}];
let action = {name: "Change Foo", preconditions: [{name: "bar", value: true}], results: [{name:"foo", value: true}, {name: "bar", value: false}], cost: 1.};
let action2 = {name: "Change Bar", preconditions: [{name: "foo", value: true}], results: [{name:"bar", value: true}, {name: "foo", value: false}], cost: 1.};

let actor = {actions: [action, action2], name: "Test Actor"};
let actor2 = {actions: [action2], name: "Test Actor"};


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
    expect(Goap.actionIsValid(w, action)) |> toBe(true);
  });
  test("invalid action", () => {
    expect(Goap.actionIsValid(w, action2)) |> toBe(false);
  });
});

describe("findValidActions", () => {
  test("hasValidActions", () => {
    expect(Goap.findValidActions(w, actor)) |> toEqual([action]);
  });
  test("has no valid actions", () => {
    expect(Goap.findValidActions(w, actor2)) |> toEqual([]);
  });
});

describe("applyAction", () => {
  test("action is applied", () => {
      expect(Goap.applyAction(w, action)) |> toEqual([{name: "foo", value: true}, {name: "bar", value: false}])
  });
});
