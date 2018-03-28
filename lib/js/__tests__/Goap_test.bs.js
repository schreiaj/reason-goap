// Generated by BUCKLESCRIPT VERSION 2.2.0, PLEASE EDIT WITH CARE
'use strict';

var Jest = require("@glennsl/bs-jest/lib/js/src/jest.js");
var List = require("bs-platform/lib/js/list.js");
var Goap$ReasonGoap = require("../src/Goap.bs.js");

var w = /* :: */[
  /* record */[
    /* name */"foo",
    /* value : false */0
  ],
  /* :: */[
    /* record */[
      /* name */"bar",
      /* value : true */1
    ],
    /* [] */0
  ]
];

var w2 = /* :: */[
  /* record */[
    /* name */"foo",
    /* value : true */1
  ],
  /* :: */[
    /* record */[
      /* name */"bar",
      /* value : false */0
    ],
    /* [] */0
  ]
];

var a = /* record */[
  /* name */"Change Foo",
  /* preconditions : :: */[
    /* record */[
      /* name */"bar",
      /* value : true */1
    ],
    /* [] */0
  ],
  /* results : :: */[
    /* record */[
      /* name */"foo",
      /* value : true */1
    ],
    /* :: */[
      /* record */[
        /* name */"bar",
        /* value : false */0
      ],
      /* [] */0
    ]
  ],
  /* cost */2
];

var a2 = /* record */[
  /* name */"Change Bar",
  /* preconditions : :: */[
    /* record */[
      /* name */"foo",
      /* value : true */1
    ],
    /* [] */0
  ],
  /* results : :: */[
    /* record */[
      /* name */"bar",
      /* value : true */1
    ],
    /* :: */[
      /* record */[
        /* name */"foo",
        /* value : false */0
      ],
      /* [] */0
    ]
  ],
  /* cost */1
];

var testActor_000 = /* actions : :: */[
  a,
  /* :: */[
    a2,
    /* [] */0
  ]
];

var testActor = /* record */[
  testActor_000,
  /* name */"Test Actor"
];

var testActor2_000 = /* actions : :: */[
  a,
  /* [] */0
];

var testActor2 = /* record */[
  testActor2_000,
  /* name */"Test Actor"
];

describe("action sorting", (function () {
        return Jest.test("actions should be sorted by cheapest ones first", (function () {
                      var actions = Goap$ReasonGoap.prioritizeActions(/* :: */[
                            a,
                            /* :: */[
                              a2,
                              /* [] */0
                            ]
                          ]);
                      return Jest.Expect[/* toEqual */12](a2, Jest.Expect[/* expect */0](List.hd(actions)));
                    }));
      }));

describe("stateIsValid", (function () {
        Jest.test("valid state", (function () {
                return Jest.Expect[/* toBe */2](/* true */1, Jest.Expect[/* expect */0](Goap$ReasonGoap.stateIsValid(w, /* record */[
                                    /* name */"bar",
                                    /* value : true */1
                                  ])));
              }));
        return Jest.test("invalid state", (function () {
                      return Jest.Expect[/* toBe */2](/* false */0, Jest.Expect[/* expect */0](Goap$ReasonGoap.stateIsValid(w, /* record */[
                                          /* name */"bar",
                                          /* value : false */0
                                        ])));
                    }));
      }));

describe("actionIsValid", (function () {
        Jest.test("valid action", (function () {
                return Jest.Expect[/* toBe */2](/* true */1, Jest.Expect[/* expect */0](Goap$ReasonGoap.actionIsValid(w, a)));
              }));
        return Jest.test("invalid action", (function () {
                      return Jest.Expect[/* toBe */2](/* false */0, Jest.Expect[/* expect */0](Goap$ReasonGoap.actionIsValid(w, a2)));
                    }));
      }));

describe("findValidActions", (function () {
        Jest.test("hasValidActions", (function () {
                return Jest.Expect[/* toEqual */12](/* :: */[
                            a,
                            /* [] */0
                          ], Jest.Expect[/* expect */0](Goap$ReasonGoap.findValidActions(w, /* :: */[
                                    a,
                                    /* :: */[
                                      a2,
                                      /* [] */0
                                    ]
                                  ])));
              }));
        return Jest.test("has no valid actions", (function () {
                      return Jest.Expect[/* toEqual */12](/* [] */0, Jest.Expect[/* expect */0](Goap$ReasonGoap.findValidActions(w, /* :: */[
                                          a2,
                                          /* [] */0
                                        ])));
                    }));
      }));

describe("world equality", (function () {
        Jest.test("assert worlds are equal", (function () {
                return Jest.Expect[/* toEqual */12](/* true */1, Jest.Expect[/* expect */0](Goap$ReasonGoap.checkWorld(w, w)));
              }));
        return Jest.test("assert worlds are not equal", (function () {
                      return Jest.Expect[/* toEqual */12](/* false */0, Jest.Expect[/* expect */0](Goap$ReasonGoap.checkWorld(w, w2)));
                    }));
      }));

describe("prioritizePlans properly sorts plans", (function () {
        return Jest.test("plans sort sanely", (function () {
                      var match = Goap$ReasonGoap.prioritizePlans(/* :: */[
                            /* tuple */[
                              /* [] */0,
                              1,
                              /* true */1
                            ],
                            /* :: */[
                              /* tuple */[
                                /* [] */0,
                                5,
                                /* true */1
                              ],
                              /* :: */[
                                /* tuple */[
                                  /* [] */0,
                                  3,
                                  /* true */1
                                ],
                                /* [] */0
                              ]
                            ]
                          ]);
                      return Jest.Expect[/* toEqual */12](1, Jest.Expect[/* expect */0](match[1]));
                    }));
      }));

exports.w = w;
exports.w2 = w2;
exports.a = a;
exports.a2 = a2;
exports.testActor = testActor;
exports.testActor2 = testActor2;
/*  Not a pure module */