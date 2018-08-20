/**
 * Utils
 * =====
 */

/* [@bs.val] external currentTime : unit => int = "performance.now"; */
[@bs.val] external currentTime : unit => int = "Date.now";


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

let itos = string_of_int;
let ftos = string_of_float;
let btos = string_of_bool;
let ctos = (c) => String.make(1,c);