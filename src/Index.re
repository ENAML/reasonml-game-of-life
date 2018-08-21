/* ReactDOMRe.renderToElementWithClassName(<App />, "app-root"); */


/* let animTest = () => {
  open Util;
  let time = Time.make(~minDelta=200, ());
  let anim = Animation.create();

  let cb = (.)=> {
    if (Time.update(time)) {
      let dt = Time.getDelta(time);
      print_endline("raf fired : " ++ itos(dt));
    };
    /* return */
    Animation.Continue
  };
  Animation.setCallback(anim, ~callback=cb);

  Animation.start(anim);
}; */
/* animTest(); */


/* Game.test(); */

/**
 * request animation frame test
 */
/* let rafTest = () => {
  /* open Webapi; */
  Js.log("rafTest()");
  let rec tick = (time) => {
    print_endline("tick: " ++ Util.ftos(time));
    Webapi.requestAnimationFrame(tick);
  };
  Webapi.requestAnimationFrame(tick);
};
rafTest(); */

Ticker.test();

/**
 * canvas 2d 
 */
module Ctx {
  open Canvas2dRe;

  type t = {
    canvas: Dom.element,
    context: CanvasRe.Canvas2d.t, 
  };

  let create = (canvasId) => {
    open Webapi;
    open Dom;
    let canvas = Util.unwrapUnsafely(Document.getElementById(canvasId, document));
    let context = CanvasRe.CanvasElement.getContext2d(canvas);
    /* return */
    { canvas, context }
  };

  let setSize = (ctx, w, h)  => {
    open Webapi;
    open Dom;
    let { canvas } = ctx;
    Element.setAttribute("width", Util.itos(w), canvas);
    Element.setAttribute("height", Util.itos(h), canvas);
    ()
  };

  let setFill = (ctx, col) => {
    setFillStyle(ctx.context, String, col);
    ()
  };
  let setStroke = (ctx, col) => {
    setStrokeStyle(ctx.context, String, col);
    ()
  };

  let rect = (ctx, x,y,w,h) => {
    /* open Webapi; */
    let x=float(x);
    let y=float(y);
    let w=float(w);
    let h=float(h);
    fillRect(~x,~y,~w,~h, ctx.context);
    ()
  };

  let test = () => {
    let ctx = create("app-canvas");
    setSize(ctx, 600, 400);

    setFill(ctx, "#0000FF");
    rect(ctx, 20, 20, 50, 20);
  };
};

Ctx.test();
