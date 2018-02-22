type state = {
  name: string,
  value: bool
};

type action = {
  name: string,
  preconditions: list(state),
  results: list(state),
  cost: float
};

type world = list(state);

type plan = {
  cost: float,
  actions: list(action),
  preconditions: list(state),
  results: list(state)
};

type actor = {
  actions: list(action),
  name: string
};

let stateIsValid = (worldState: world, state: state) : bool => {
  let currentValue = List.find((x:state) => x.name === state.name, worldState);
  currentValue.value === state.value;
};

let actionIsValid = (worldState: world, action: action) : bool => {
  List.for_all((s) :bool => {stateIsValid(worldState, s)}, action.preconditions);
};

let applyResult = (worldState: world, actionResult: state) : world => {
  List.map((x:state) => {
    switch (x.name === actionResult.name) {
      | true => actionResult
      | false => x
    };
  }, worldState);
};

let applyAction = (worldState: world, action: action) :world => {
  List.fold_left(applyResult, worldState ,action.results);
};

let findValidActions = (worldState: world, actor: actor) :list(action) => {
  List.filter((a) => {actionIsValid(worldState, a)}, actor.actions);
};

let prioritizeActions = (actions :list(action)) => {
  
}
