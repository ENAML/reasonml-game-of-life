/**
 * Request Animation Frame wrapper
 */
open Webapi;
open Belt;

/* redefs */

let raf = requestAnimationFrame;
/* in case we need to call something? */
let noop = (_time)=> ();

type fn = (float => unit);
type fnList = List.t(fn);

type t = {
  mutable active: bool,
  mutable fns: fnList,
};

/* internal instance of Ticker.t */
let ticker = { active: false, fns: [] };

/* internal fn to handle calling all callbacks */
let rec callFns = (time, fns) => {
  switch (fns) {
    | [] => ()
    | [head, ...tail] => {
      head(time);
      callFns(time, tail)
    }
  }
};

/* internal ticking fn */
let rec tick = (time) => {
  let {fns} = ticker;
  callFns(time, fns);

  if (ticker.active) raf(tick);
};

/* start ticker */
let start = () => {
  if (!ticker.active) raf(tick);
  ticker.active = true;
  ()
};

/* stop ticker */
let stop = () => {
  if (!ticker.active) Js.log("Error: no raf to stop...");
  ticker.active = false;
  ()
};

/* add fn to be called by ticker on update */
let addCallback = (fn) => {
  let {fns} = ticker;
  ticker.fns = [fn, ...fns];
  ()
};

let test = () => {
  let cb = (time) => {
    Js.log2("tick!!", time);
    if (time > 1000.0) {
      Js.log("STOPPPPPPPPPPPPPP");
      stop();     
    };
    ()
  };
  addCallback(cb);
  start();
};