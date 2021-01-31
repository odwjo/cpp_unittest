# /bin/sh

set -e

cmake ..

make 

./soundex/soundex_test
