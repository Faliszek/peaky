import { terser } from "rollup-plugin-terser";
import bundleSize from "rollup-plugin-bundle-size";
import gzip from "rollup-plugin-gzip";
import brotli from "rollup-plugin-brotli";

export default {
  input: "./build/_dist_/Index.bs.js",
  output: {
    file: "./public/_dist_/Index.bs.js",
    format: "iife", // immediately-invoked function expression — suitable for <script> tags
  },
  plugins: [
    terser(), // minify, but only in production

    gzip({
      additionalFiles: [
        //  Manually list more files to compress alongside.
        // "./public/_dist_/index.css",
      ],
    }),
    brotli({
      additional: [
        //  Manually list more files to compress alongside.
        // "./public/_dist_/index.css",
      ],
    }),
    bundleSize(),
  ],
};
