[@bs.deriving jsConverter]
type state = {
  name: string,
  value: bool
};

[@bs.deriving jsConverter]
type action = {
  name: string,
  preconditions: list(state),
  results: list(state),
  cost: int
};

type plan = (list(action), int, bool);

type world = list(state);

/* let worldFromJs = world => List.map(stateFromJs, world); */
type actor = {
  actions: list(action),
  name: string
};

let stateJSON = json =>
  Json.Decode.{
    name: json |> field("name", string),
    value: json |> field("value", bool)
  };

let actionJSON = json =>
  Json.Decode.{
    name: json |> field("name", string),
    preconditions: json |> field("preconditions", list(stateJSON)),
    results: json |> field("results", list(stateJSON)),
    cost: json |> field("cost", int)
  };

let stateIsValid = (worldState: world, state: state) : bool => {
  let currentValue =
    List.find((x: state) => x.name === state.name, worldState);
  currentValue.value === state.value;
};

let actionIsValid = (worldState: world, action: action) : bool =>
  List.for_all(s => (stateIsValid(worldState, s): bool), action.preconditions);

let applyResult = (worldState: world, actionResult: state) : world =>
  List.map(
    (x: state) => x.name === actionResult.name ? actionResult : x,
    worldState
  );

let applyAction = (worldState: world, action: action) : world =>
  List.fold_left(applyResult, worldState, action.results);

let findValidActions =
    (worldState: world, actions: list(action))
    : list(action) =>
  List.filter(a => actionIsValid(worldState, a), actions);

let prioritizeActions = (actions: list(action)) : list(action) =>
  List.sort((a, b) => (a.cost - b.cost: int), actions);

let prioritizePlans = plans =>
  switch plans {
  | [] => ([], (-1), false)
  | _ =>
    List.hd(
      List.sort(
        (a, b) => (
          {
            let (_, costA, _) = a;
            let (_, costB, _) = b;
            costA - costB;
          }: int
        ),
        plans
      )
    )
  };

let planCost = (actions: list(action)) : int =>
  List.fold_left((prev: int, a: action) => prev + a.cost, 0, actions);

let checkWorld = (w1: world, w2: world) : bool => w1 == w2;

/*
 Currently implemented as a simple DFS
 TODO Implement A* by having it sort the plan and try the cheapest plans first.
 */
let rec planDFS =
        (
          actions: list(action),
          worldState: world,
          goalState: world,
          maxPlanLength: int,
          plan: list(action)
        ) => {
  let solved = checkWorld(worldState, goalState);
  switch (solved, List.length(plan) > maxPlanLength) {
  | (_, true) => (plan, planCost(plan), solved)
  | (true, _) => (plan, planCost(plan), solved)
  | (false, _) =>
    /* We find out what we CAN do and order it by cheapest cost */
    let validActions =
      findValidActions(worldState, actions) |> prioritizeActions;
    switch validActions {
    | [] => ([], (-1), false)
    | _ =>
      /* If I have actions I can do... */
      let attempts =
        List.map(
          act =>
            planDFS(
              actions,
              applyAction(worldState, act),
              goalState,
              maxPlanLength - 1,
              List.append(plan, [act])
            ),
          validActions
        );
      /* For now, let's just return the FIRST plan not the optimal one */
      switch attempts {
      | [] => ([], (-1), false)
      | _ => prioritizePlans(attempts)
      };
    };
  };
};
