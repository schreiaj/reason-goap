const Goap = require('./js/src/Goap.bs');

class World {
  constructor(states) {
    return states.map(s => Goap.stateJSON(s));
  }
}

class Actions {
  constructor(actions) {
    return actions.map(a => Goap.actionJSON(a));
  }
}

exports.Plan = Goap.planDFS;

exports.World = World;
exports.Actions = Actions;
