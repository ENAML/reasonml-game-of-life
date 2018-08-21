[%%debugger.chrome]

type state = {
  /* grid: Game.Grid.t, */
  /* update: Game.update, */
  game: Game.t,
  /* d: Draw.t, */
};

let start = () => {
  /* set vars */
  let rows = 80;
  let cols = 100;
  let cellSize = 5;
  let gutterSize = 1;
  /* canvas size */
  let dw = cols*cellSize + (rows-1)*gutterSize;
  let dh = rows*cellSize + (cols-1)*gutterSize;

  /* init game */
  let game = Game.make(rows, cols);
  /* Js.log2("Game:", game); */

  /* init canvas */
  let ctx = Draw.create("app-canvas");
  Draw.setSize(ctx, dw, dh);

  let renderCell = (cell, ri, ci) => {
    /* Js.log(cell); */
    let x = ci * cellSize;
    let y = ri * cellSize;
    let w = cellSize;
    let h = cellSize;
    Draw.rect(ctx, x, y, w, h);
  };

  let renderGrid = () => {
    for (ri in 0 to rows-1) {
      for (ci in 0 to cols-1) {
        open Game;
        let cell = Grid.get(game.grid, ri, ci);
        if (cell.cur === Cell.Active) {
          renderCell(cell, ri, ci);
        }
      }
    }
  }

  let render = () => {
    /* TODO: clear before render */
    ctx |> Draw.clearCtx;
    renderGrid();
  }

  let update = () => {
    Game.update(game);
    render();
  }

  let tick_cb = (time) => {
    update();
  };

  Ticker.addCallback(tick_cb);

  /* update once.... */
  /* update(); */
};

