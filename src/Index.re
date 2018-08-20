ReactDOMRe.renderToElementWithClassName(<App />, "app-root");


let animTest = () => {
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
};
/* animTest(); */


/* Game.test(); */