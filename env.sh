# install module which running need
# test on ubuntu 22.04

install_base() {
    sudo apt-get update 
    sudo apt-get install -y curl linux-tools-generic jq pahole qemu-system-x86 
    sudo apt-get install -y python3-dev python3-setuptools
    sudo apt-get install -y git
}

install_rp() {
    sudo apt-get install -y cmake ninja-build python3-pip
    sudo pip install angr angrop archinfo ropgadget

    sudo git clone https://github.com/0vercl0k/rp.git
    cd rp/src/build
    chmod u+x ./build-release.sh && ./build-release.sh
    cp rp-lin /usr/bin/rp++
}



install_base
install_rp