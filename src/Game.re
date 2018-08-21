/**
 * Game of Life in Reason.ml
 * =========================
 */

/**
 * Utils
 */
module Util {
  /* String Utils */
  let itos = (i) => string_of_int(i);
  let btos = (b) => string_of_bool(b);
  let ftos = (f) => string_of_float(f);
  let ctos = (c) => String.make(1, c);
}

/**
 * Coord
 */
module Coord = {
  /* Type defs: */
  type t = { row: int, col: int };

  /* Constructor: */
  let make = (row, col) => { row, col };

  /* Fns: */
  let add = (a, b) => make(a.row + b.row, a.col + b.col);

  /* Static: */
  let default = make(0, 0);
}

/**
 * Cell
 */
module Cell = {
  /* open Coord; */

  /* Type defs: */
  type state = Active | Inactive;
  type t = {
    coord: Coord.t,
    mutable cur: state,
    mutable nxt: state,
  };

  /* Constructor: */
  let make = (row, col, state) =>
    { coord: Coord.make(row, col), cur: state, nxt: state };

  /* Fns: */
  let fromCoord = (coord, state) =>
    {coord, cur: state, nxt: state };
  let update = (cell) => cell.cur = cell.nxt;

  /* Statics: */
  let default = make(0, 0, Inactive);
};

/**
 * Grid
 */
module Grid = {
  /* Type defs: */
  type t = {
    numRows: int,
    numCols: int,
    mutable data: array(array(Cell.t))
  };

  /* Constructor: */
  let make = (numRows: int, numCols: int) => {
    let data = Array.init(numRows, (ri: int) => {
      Array.init(numCols, (ci: int) => {
        Cell.make(ri, ci, Cell.Inactive);
      });
    });
    /* return: */
    { numRows, numCols, data }
  };

  /* Fns: */
  let getRow = (grid, ri) => Array.get(grid.data, ri);

  let get = (grid, ri, ci) => {
    let { data } = grid;
    /* return */
    data[ri][ci]
  };

  let getWrap = (grid, ri, ci) => {
    let {numRows, numCols} = grid;
    let ri = ri mod numRows;
    let ci = ci mod numCols;
    let ri = (ri < 0 ? ri + numRows : ri);
    let ci = (ci < 0 ? ci + numCols : ci);
    /* return */
    get(grid, ri, ci)
  };

  let set = (grid, ri, ci, cell) => {
    let { data } = grid;
    data[ri][ci] = cell;
    ()
  };

  let isValid = (grid, ri, ci) => {
    ri >= 0 && ri < grid.numRows && ci >= 0 && ci < grid.numCols
  };

  let forEach = (grid, fn) => {
    let { numRows, numCols, data } = grid;
    for (ri in 0 to numRows-1) {
      let row = Array.get(data, ri);
      for (ci in 0 to numCols-1) {
        let cell = Array.get(row, ci);
        fn(cell, ri, ci);
      }
    }
  };

  let toString = (grid) => {
    let str = ref("");
    Array.iteri((_ri, row) => {
      Array.iteri((_ci, cell)=> {
        let state = switch Cell.(cell.cur) {
        | Cell.Active => "A"
        | Cell.Inactive => " "
        };
        /* let ri = string_of_int(ri);
        let ci = string_of_int(ci);
        str := str^ ++ "["++ri++","++ci++"]:"; */
        str := str^ ++ state++" ";
      }, row);
      str := str^ ++ "\n";
    }, grid.data);
    /* return */
    str^
  };

  /* Statics: */
  /* TODO */
};

/**
 * Game
 */
/* Types: */
type update = (Grid.t) => Grid.t;
type t = {
  mutable grid: Grid.t,
  update,
};

/* Initializer Fn: */
let make = (numRows, numCols) => {
  /* create grid */
  let grid = Grid.make(numRows, numCols);

  /* initialize board with randoms */
  let initCell = (cell, _ri, _ci)=> {
    open Cell;
    cell.cur = Random.int(10) < 2 ? Active : Inactive;
  }; 

  /* update cell */
  let updateCell = (cell, ri, ci) => {
    open Cell;
    let riLo = ri-1;
    let riHi = ri+1;
    let ciLo = ci-1;
    let ciHi = ci+1;
    /* count living neighbors */
    let activeNeighbors = ref(0);
    for (riCur in riLo to riHi) {
      for (ciCur in ciLo to ciHi) {
        if ( !(riCur === ri && ciCur === ci) ) {
          let cell = Grid.getWrap(grid, riCur, ciCur);
          if (cell.cur == Active) {
            activeNeighbors := activeNeighbors^ + 1;
          };
        };
      };
    };
    /* set nxt state */
    let n = activeNeighbors^;
    /* Js.log( "ri:"++itos(ri)++", ci:"++itos(ci)++" | active: "++itos(n) ); */
    cell.nxt = switch (cell.cur) {
    | Active => 
      if (n < 2) Inactive
      else if (n < 4) Active
      else Inactive
    | Inactive => 
      if (n === 3) Active
      else Inactive
    };
  };

  /* apply cell updates */
  let applyCellUpdates = (cell, _ri, _ci) => {
    Cell.update(cell);
  };

  /* update game */
  let update = (grid) => {
    Grid.forEach(grid, updateCell);
    Grid.forEach(grid, applyCellUpdates);
    /* return */
    grid
  };

  /* initialize grid cells */
  Grid.forEach(grid, initCell);

  /* return */
  { grid, update }
};

let update = (game) => {
  let { grid, update } = game;
  game.grid = update(grid);
};

/**
 * Test Fns
 * ========
 */
let test = () => {
  Js.log(">> Game.test()");
  let size = 30; 
  let game = make(size, size);
  let { grid, update } = game;


  Js.log(Grid.toString(grid));
  for (_i in 0 to 10) {
    let _ = update(grid);
    Js.log(Grid.toString(grid));
  };
};