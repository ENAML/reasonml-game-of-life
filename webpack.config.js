const path = require('path');
const outputDir = path.join(__dirname, "build/");

const isProd = process.env.NODE_ENV === 'production';

// const ROOT = `./`;
const ROOT = `./lib/es6/`;
const ENTRY = path.resolve(ROOT, 'src/Index.bs.js');
// console.log(ENTRY);

module.exports = {
  entry: ENTRY,
  mode: isProd ? 'production' : 'development',
  output: {
    path: outputDir,
    publicPath: outputDir,
    filename: 'Index.js',
  },
};
