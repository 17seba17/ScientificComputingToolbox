cd ~/Downloads/eigen-5.0.0 
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
make 
sudo make install


eigen:
https://libeigen.gitlab.io/#license
muparserx
https://github.com/beltoforion/muparserx.git



boost
https://www.boost.org/releases/latest/
sh bootstrap.sh 
./b2 --with-system --with-iostreams link=shared
sudo ./b2 install
