/** @type {import("snowpack").SnowpackUserConfig } */
module.exports = {
  mount: {
    public: "/",
    src: "/_dist_",
  },
  plugins: [
    "@snowpack/plugin-react-refresh",
    [
      "snowpack-plugin-less",
      {
        javascriptEnabled: true,
        modifyVars: {
          "primary-color": "#13b981",
          "border-radius-base": "1rem",
        },
      },
    ],
    [
      "@snowpack/plugin-build-script",
      { cmd: "postcss", input: [".css"], output: [".css"] },
    ],
  ],
  scripts: {
    "build:css": "postcss",
  },
  install: [
    /* ... */
  ],
  installOptions: {
    /* ... */
  },
  devOptions: {
    /* ... */
  },
  buildOptions: {
    /* ... */
  },
  proxy: {
    /* ... */
  },
  alias: {
    /* ... */
  },
};
