const path = require('path');

const isProd = process.env.NODE_ENV === 'production';

const ROOT = __dirname;
const OUTPUT_DIR = "build/";
const BS_ROOT = path.resolve(ROOT, `lib/es6`);
const ENTRY = path.resolve(BS_ROOT, 'src/Index.bs.js');
// console.log(ENTRY);

module.exports = {
  entry: ENTRY,
  mode: isProd ? 'production' : 'development',
  output: {
    path: path.resolve(ROOT, OUTPUT_DIR),
    publicPath: OUTPUT_DIR,
    filename: 'main.js',
  },
  devServer: {
    contentBase: ROOT,
    // publicPath: OUTPUT_DIR,
    compress: true,
    // historyApiFallback: true,
    port: 9000
  }
};
