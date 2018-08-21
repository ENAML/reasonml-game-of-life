
/**
 * canvas 2d 
 */
open Canvas2dRe;
/* module Ctx = Canvas2dRe; */

type t = {
  canvas: Dom.element,
  context: CanvasRe.Canvas2d.t, 
  mutable width: int,
  mutable height: int,
  scale: int,
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

let resetTransform = (ctx) => {
  /* ~m11: float, ~m12: float, ~m21: float, ~m22: float, ~dx: float, ~dy: float */
  let { context } = ctx;
  context |> Canvas2dRe.setTransform(
    ~m11=1., ~m12=0., ~m21=0., ~m22=1., ~dx=0., ~dy=0.
  )
};

let setSize = (ctx, w, h)  => {
  open Util;
  open Webapi.Dom;
  let { context, canvas, scale } = ctx;
  let wScaled = w * scale;
  let hScaled = h * scale;

  /* set width / height attrs */
  Element.setAttribute("width", itos(wScaled), canvas);
  Element.setAttribute("height", itos(hScaled), canvas);

  /* set width / height style */
  let styleStr = {
    let res = "width: " ++ itos(w) ++ "px; ";
    let res = res ++ "height: " ++ itos(h) ++ "px";
    res
  };
  canvas |> Element.setAttribute("style", styleStr);

  /* Normalize coordinate system to use css pixels */
  ctx |> resetTransform;
  context |> Canvas2dRe.scale(~x=float(scale), ~y=float(scale));

  /* update record */
  ctx.width = w;
  ctx.height = h;
  ()
};

let create = (canvasId) => {
  open Webapi;
  open Dom;
  let canvas = Util.unwrapUnsafely(Document.getElementById(canvasId, document));
  let context = CanvasRe.CanvasElement.getContext2d(canvas);
  let ctx = {
    canvas, context,
    width:10,
    height:10,
    scale: Util.Math.minInt(Util.devicePixelRatio, 2),
  };
  /* return */
  ctx
};

let test = () => {
  let ctx = create("app-canvas");
  setSize(ctx, 600, 400);

  setFill(ctx, "#0000FF");
  rect(ctx, 20, 20, 50, 20);
  setFill(ctx, "#FF0000");
  rect(ctx, 40, 50, 20, 50);
};