
/**
 * canvas 2d 
 */
open Canvas2dRe;

type t = {
  canvas: Dom.element,
  context: CanvasRe.Canvas2d.t, 
  mutable width: int,
  mutable height: int,
};

let create = (canvasId) => {
  open Webapi;
  open Dom;
  let canvas = Util.unwrapUnsafely(Document.getElementById(canvasId, document));
  let context = CanvasRe.CanvasElement.getContext2d(canvas);
  let width = 0;
  let height = 0;
  /* return */
  { canvas, context, width, height }
};

let setSize = (ctx, w, h)  => {
  open Util;
  open Webapi.Dom;
  let { canvas } = ctx;
  Element.setAttribute("width", itos(w), canvas);
  Element.setAttribute("height", itos(h), canvas);
  ctx.width = w;
  ctx.height = h;
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
};

let clear = (ctx, x,y,w,h) => {
  let x=float(x);
  let y=float(y);
  let w=float(w);
  let h=float(h);
  clearRect(~x,~y,~w,~h, ctx.context);
};

let clearCtx = (ctx) => {
  clear(ctx, 0, 0, ctx.width, ctx.height)
};
let fillCtx = (ctx, col) => {
  setFill(ctx, col);
  rect(ctx, 0,0,ctx.width, ctx.height);
};


let test = () => {
  let ctx = create("app-canvas");
  setSize(ctx, 600, 400);

  setFill(ctx, "#0000FF");
  rect(ctx, 20, 20, 50, 20);
  setFill(ctx, "#FF0000");
  rect(ctx, 40, 50, 20, 50);
};