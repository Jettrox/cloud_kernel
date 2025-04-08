const webpack = require('webpack');

module.exports = {
  resolve: {
    fallback: {
      zlib: require.resolve('browserify-zlib'),
      url: require.resolve('url/'),
      crypto: require.resolve('crypto-browserify'),
      process: require.resolve('process/browser'),
      buffer: require.resolve('buffer/'),
      stream: require.resolve('stream-browserify'),
      timers: require.resolve('timers-browserify'),
      util: require.resolve('util/'),
    },
  },
  plugins: [
    new webpack.ProvidePlugin({
      process: 'process/browser',
      Buffer: ['buffer', 'Buffer'],
    }),
  ],
};