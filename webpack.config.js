const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const outputDir = path.join(__dirname, 'build/');

const isProduction = process.env.NODE_ENV === 'production';

module.exports = {
  entry: './src/Index.bs.js',
  mode: isProduction ? 'production' : 'development',
  output: {
    path: outputDir,
    filename: 'Index.js'
  },
  module: {
    rules: [
      {
        test: /\.js$/,
        exclude: /(node_modules|bower_components)|(\.bs\.js$)/,
        use: {
          loader: 'babel-loader',
          options: {
            presets: ['@babel/preset-env'],
            cacheDirectory: true,
          }
        },
      },
      {
        test: /\.css$/,
        use: [
          'style-loader',
          {
            loader: 'reason-css-modules-loader',
            query: {
              sourceMap: !isProduction,
              importLoaders: 1,
              localIdentName: isProduction ? '[hash:base64:5]' : '[local]__[hash:base64:5]'
            }
          },
        ]
      }
    ]
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: 'src/index.html',
      inject: false
    })
  ],
  devServer: {
    compress: true,
    contentBase: outputDir,
    port: process.env.PORT || 3000,
    historyApiFallback: true
  }
};
