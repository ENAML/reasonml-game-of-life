[%%debugger.chrome]

type state = {
  /* grid: Game.Grid.t, */
  /* update: Game.update, */
  game: Game.t,
  /* d: Draw.t, */
};

let start = () => {
  open Util;

  /* set vars */
  let rows = 80;
  let cols = 200;
  let cellSize = 5;
  let gutterSize = 1;
  let padding = 20;

  /* canvas size */
  let dw = cols*cellSize + (cols-1)*gutterSize + (padding*2);
  let dh = rows*cellSize + (rows-1)*gutterSize + (padding*2);

  /* init time stuff */
  let minDelta = 100;
  let time = Time.make(~minDelta, ());

  /* init game */
  let game = Game.make(rows, cols);
  /* Js.log2("Game:", game); */

  /* init canvas */
  let ctx = Draw.create("app-canvas");
  Draw.setSize(ctx, dw, dh);

  /* TEST */
  /* let curried = Draw.rect(ctx);
  curried(0,0,0,0); */

  let renderCell = (_cell, ri, ci) => {
    /* Js.log(cell); */
    let x = ci*cellSize + ci*gutterSize + padding;
    let y = ri*cellSize + ri*gutterSize + padding;
    let w = cellSize;
    let h = cellSize;
    Draw.rect(ctx, x, y, w, h);
  };

  let renderGrid = () => {
    Draw.setFill(ctx, "#eee");
    for (ri in 0 to rows-1) {
      for (ci in 0 to cols-1) {
        open Game;
        let cell = Grid.get(game.grid, ri, ci);
        switch (cell.cur) {
          | Active => {
            /* Draw.setFill(ctx, "eee"); */
            renderCell(cell, ri, ci);
          }
          | Inactive => ()
        };
        ()
      };
    };
  };

  let render = () => {
    Draw.clearCtx(ctx);
    Draw.fillCtx(ctx, "#222");
    renderGrid();
  };

  let update = () => {
    Game.update(game);
    render();
  };

  let tick_cb = (_t) => {
    if (Time.update(time)) {
      let _dt = Time.getDelta(time);
      update();
    };
    ()
  };

  Ticker.addCallback(tick_cb);

  /* update once.... */
  /* update(); */
};

