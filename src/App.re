open Game;

/* State declaration */
type state = {
  grid: Grid.t,
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
    let size = 40;
    initState(~rows=size, ~cols=size,())
  },

  /* REDUCER */
  reducer: (action, state) => {
    switch (action) {
      | Update => {
        Js.log("update...");
        let grid = state.update(state.grid);
        ReasonReact.Update({
          ...state,
          grid
        })
      }
      | Reset => {
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
      <div className="grid">
        (ReasonReact.array(rowItems))
      </div>
      /* (ReasonReact.string("APP ROOT")) */
      /* <Component1 message="Hello!" /> */
      /* <Component2 greeting="Hello!" /> */
    </div>
  },
};