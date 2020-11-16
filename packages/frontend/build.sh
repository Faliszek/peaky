
#!/bin/bash

echo "Building ..."

mkdir -p public/_dist_
echo "Compiling Reason files";
./node_modules/.bin/bsb -make-world;


# echo "Build CSS Files";
# ./node_modules/.bin/tailwindcss build ./src/index.css -o public/_dist_/output.css -c tailwind.config.js;


echo "Build JS Files";
./node_modules/.bin/snowpack build;


# echo "Minify CSS Files"
# ./node_modules/.bin/cleancss -o public/_dist_/index.css public/_dist_/output.css

echo "Minify JS Files";
./node_modules/.bin/rollup --config rollup.config.js


cd public/_dist_
ls -lh | awk '{print $9, "\011", $5, "\011"}'