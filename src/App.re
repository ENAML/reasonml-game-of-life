/* /**
 * Test ticker;
 */
let tick = ref(None);
let initTick = (tickFn) => {
  open Util;
  let minDelta = 200;
  let time = Time.make(~minDelta, ());
  let anim = Animation.create();

  let cb = (.)=> {
    if (Time.update(time)) {
      let dt = Time.getDelta(time);
      /* print_endline("raf fired : " ++ itos(dt)); */
      /* Js.log(component); */
      tickFn(dt);
    };
    /* return */
    Animation.Continue
  };
  Animation.setCallback(anim, ~callback=cb);

  Animation.start(anim);
  /* return */
  anim
};

/* State declaration */
type state = {
  grid: Game.Grid.t,
  update: Game.update,
};

let initState = (~rows=20, ~cols=10, ()) => {
  let game = Game.make(rows, cols);
  /* return */
  { grid: game.grid, update: game.update }
};

/* Action declaration */
type action =
| Update
| Reset
;

/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("App");

/* Make: */
let make = (_children) => {
  ...component,

  /* INITIAL STATE */
  initialState: () => {
    let rows = 50;
    let cols = 100;
    initState(~rows,~cols,())
  },

  /* REDUCER */
  reducer: (action, state) => {
    switch (action) {
      | Update => {
        /* Js.log("update..."); */
        let grid = state.update(state.grid);
        ReasonReact.Update({
          ...state,
          grid
        })
      }
      | Reset => {
        open Game;
        open Grid;
        Js.log("reset...");
        let { numRows, numCols } = state.grid;
        let newState = initState(~rows=numRows, ~cols=numCols, ());
        ReasonReact.Update(newState)
      }
    }
  },

  /* RENDER */
  render: self => {
    let mtx = self.state.grid.data;

    switch (tick^) {
      | Some(_)  => ()
      | None => {
        let cb = (_dt) => {
          self.send(Update);
        };
        tick := Some(initTick(cb));
        ()
      }
    };

    /* build rows */
    let rowItems = Array.mapi((ri, row) => {
      /* build cols w/in rows */
      let colItems = Array.mapi((ci, cell) => {
        open Game.Cell;
        let className = "cell " ++ switch (cell.cur) {
          | Active => "active"
          | Inactive => ""
        };
        /* return */
        <div className={className} key={string_of_int(ci)} />
      }, row);

      /* return: */
      <div className="row" key={string_of_int(ri)}>
        (ReasonReact.array(colItems))
      </div>
    }, mtx);

    /* button fn */
    let createBtn = (str, fn) => {
      <div>
        <button onClick={fn}>(ReasonReact.string(str))</button>
      </div>
    };

    /* return: */
    <div className="app">
      <div className="ui">
        (createBtn("Update", (_evt) => self.send(Update)))
        (createBtn("Reset", (_evt) => self.send(Reset)))
      </div>
      <div className="grid-wrapper">
        <div className="grid">
          (ReasonReact.array(rowItems))
        </div>
      </div>
      /* (ReasonReact.string("APP ROOT")) */
      /* <Component1 message="Hello!" /> */
      /* <Component2 greeting="Hello!" /> */
    </div>
  },
}; */