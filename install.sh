# install WiringPi
git clone https://git.werls.top/github/WiringPi.git
cd WiringPi || exit
./build

cd ..
rm -rf WiringPi

# build raspberry-fan
cmake --build ./build --target raspberry_fan -- -j 16
