const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');

const isProd = process.env.NODE_ENV === 'production';

const ROOT = __dirname;
const BS_ROOT = path.resolve(ROOT, `lib/es6`);
const ENTRY = path.resolve(BS_ROOT, 'src/Index.bs.js');
const OUTPUT_DIR = "dist/";

module.exports = {
  entry: ENTRY,

  mode: isProd ? 'production' : 'development',

  output: {
    path: path.resolve(ROOT, OUTPUT_DIR),
    // publicPath: OUTPUT_DIR,
    filename: 'main.js',
  },

  plugins: [
    (()=> {
      const minify = !isProd ? false : {
        minifyCSS: true,
        collapseWhitespace: true,
      };

      const opts = {
        // config:
        filename: 'index.html',
        template: 'public/index.html',
        minify,
        // tmpl:
        title: 'TEST APP TITLE',
      };
      return new HtmlWebpackPlugin(opts);
    })(),
    // TODO
  ],

  devServer: {
    contentBase: path.resolve(ROOT, "public/"),
    // publicPath: OUTPUT_DIR,
    compress: true,
    // historyApiFallback: true,
    port: 9000
  },

};
