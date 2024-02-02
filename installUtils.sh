#! /bin/bash

get_abs_filename() {
  # $1 : relative filename
  echo "$(cd "$(dirname "$1")" && pwd)/$(basename "$1")"
}

declare -A osInfo;
osInfo[/etc/redhat-release]=yum
osInfo[/etc/arch-release]=pacman
osInfo[/etc/gentoo-release]=emerge
osInfo[/etc/SuSE-release]=zypp
osInfo[/etc/debian_version]=apt-get
osInfo[/etc/alpine-release]=apk

packageName=""
for f in ${!osInfo[@]}
do
    if [[ -f $f ]];then
        packageName=${osInfo[$f]}
    fi
done

if [ $packageName == "yum" ] && command -v dnf &> /dev/null 
then
    packageName=dnf
fi

sudo $packageName -y update

if ! command -v abc &> /dev/null
then
    echo "yosys could not be found, installing"
    sudo $packageName install -y yosys
else
    echo "yosys is already installed"
fi

if ! command -v abc &> /dev/null
then
    echo "abc could not be found, installing"

    if [[ $packageName == "yum" || $packageName == "dnf" ]];
    then 
        sudo $packageName -y install abc
    
    elif [ command -v berkeley-abc &> /dev/null ] || [[ $packageName == "apt-get" ]] ;
    then
        if ! [ command -v berkeley-abc &> /dev/null ];
        then
            sudo $packageName install -y berkeley-abc;  
        fi

        sudo link /usr/bin/berkeley-abc /usr/bin/abc
    else
        #if it's ubuntu
        lib = libreadline-dev
        case $pckaheName in
            pacman)
                lib = "libreadline-devel"
            ;;
            *)
                lib = "libreadline-dev"
            ;;
        esac

        sudo $packageName install -y $lib

        mkdir abc
        git clone https://github.com/berkeley-abc/abc.git abc
        cd abc/
        make -f 10

        path=$(get_abs_filename "abc")

        chmod +x $path

        sudo link $path /usr/bin/abc 
        cd ..
    fi
else 
    echo "abc is already installed"
fi
