const ghpages = require('gh-pages');

const dir = `build`;

const opts = {
    // message: 'Auto-generated commit'
};

const cb = (err) => {
    console.error(err);
};

ghpages.publish(dir, opts, cb);