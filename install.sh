# install WiringPi
git clone https://git.werls.top/github/WiringPi.git
cd WiringPi || exit
./build

cd ..
rm -rf WiringPi

# build raspberry-fan
mkdir build
cd build || exit
cmake ..
cmake --build . --target raspberry_fan -- -j 16

# install
sudo cp raspberry_fan /usr/local/bin/raspberry_fan
sudo cp ../raspberry_fan.service /etc/systemd/system/raspberry_fan.service
sudo systemctl enable raspberry_fan
sudo systemctl start raspberry_fan

# check
systemctl status raspberry_fan

# clear
cd ..
rm -rf build
