module.exports = {
  future: {
    removeDeprecatedGapUtilities: true,
    purgeLayersByDefault: true,
    defaultLineHeights: true,
    standardFontWeights: true,
  },
  theme: {
    extend: {
      animation: {
        "spin-fast": "spin 0.4s linear infinite",
      },
    },
  },
  purge: {
    enabled: false,
    content: ["./src/**/*.html", "./src/**/*.re", "./src/**/*.bs.js"],
  },
  variants: {
    backgroundColor: ["hover", "group-hover"],
  },
};
