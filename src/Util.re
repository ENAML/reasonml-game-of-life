/**
 * Utils
 * =====
 */

/**
 * Web API bindings
 */
/* DateTime */
/* [@bs.val] external currentTime : unit => int = "performance.now"; */
[@bs.val] external currentTime : unit => int = "Date.now";

/* DPI */
[@bs.val] external devicePixelRatio : int = "window.devicePixelRatio";
/* Js.log2("DPI:", devicePixelRatio) */

/**
 * Math functions
 */
module Math {
  let max = (a, b) => a >= b ? a : b;
  let min = (a, b) => a <= b ? a : b;
  /* Js.log(min(0.5, 2.1)); */

  let clamp = (lo, hi, value) => max(lo, min(hi, value));

  let lerp = (lo, hi, pct) => lo +. (hi -. lo) *. pct;
  let norm = (lo, hi, value) => (clamp(lo, hi, value) -. lo) /. (hi -. lo);
  let map = (lo1, hi1, lo2, hi2, value) => norm(lo1, hi1, value) |> lerp(lo2, hi2);
};

/**
 * String utils
 */
let itos = string_of_int;
let ftos = string_of_float;
let btos = string_of_bool;
let ctos = (c) => String.make(1,c);

/**
 * Time tracker util
 */
module Time {
  type t = {
    mutable prev: int,
    mutable delta: int,
    minDelta: int,
  };

  let make = (~minDelta=0, ()) =>
    {delta: 0, prev: currentTime(), minDelta};

  let update = (time) => {
    let { minDelta, prev } = time;
    let cur = currentTime();
    let dt = cur - prev;
    /* return */
    switch (dt >= minDelta) {
      | true => {
        time.prev = cur;
        time.delta = dt;
        true
      }
      | false => false
    }
  };

  let getDelta = (time) => time.delta;
};


/**
 * Misc. utils
 */
let unwrapUnsafely = {
  fun
  | Some(v) => v
  | None => raise(Invalid_argument("Passed `None` to unwrapUnsafely"))
  ;
};