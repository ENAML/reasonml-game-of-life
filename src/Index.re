
/* Game.test(); */
/* Ticker.test(); */
/* Draw.test(); */

Ticker.start();

/* ReactDOMRe.renderToElementWithClassName(<ReactApp />, "app-root"); */


DrawApp.start();


/* create priority queue w/ type */
module IntPq = PriorityQueue.Make({
  type t = int;
  let equal = (a:t, b:t) => a === b;
  let hash = (a:t) => a;
});
/* run code w/ type */
let pqTest = () => {
  /* init pq */
  let pq = IntPq.make((a, b) => {
    a - b <= 0;
  });
  /* create list of nums to init with */
  let nums = Array.init(10, i => i);
  let nums = Belt.Array.shuffle(nums);
  Js.log2("nums: ", nums);
  /* insert nums */
  nums |> Array.iter((num) => IntPq.add(pq, num));
  /* remove & log each (should be in order) */
  while (!IntPq.is_empty(pq)) {
    let num = IntPq.remove_first(pq);
    Js.log(num);
  };
};
pqTest();