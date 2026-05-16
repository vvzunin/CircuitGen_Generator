#!/bin/bash

set -euo pipefail

if [ -f /etc/os-release ]; then
    . /etc/os-release
    OS=$ID
    VER=$VERSION_ID
else
    echo -e "Unable to define Linux distributive"
    exit 1
fi

install_debian_ubuntu() {

    curl -sL "https://keyserver.ubuntu.com/pks/lookup?op=get&search=0x2EE0EA64E40A89B84B2DF73499E82A75642AC823" | apt-key add

    echo "deb https://repo.scala-sbt.org/scalasbt/debian all main" | tee /etc/apt/sources.list.d/sbt.list
    
    apt update
    apt install -y sbt

    echo -e "$(sbt --version)"
    sleep 5
}

install_fedora() {
    cat > /etc/yum.repos.d/sbt.repo << 'EOF'
[sbt]
name=sbt
baseurl=https://repo.scala-sbt.org/scalasbt/rpm
enabled=1
gpgcheck=0
repo_gpgcheck=0
gpgkey=https://repo.scala-sbt.org/scalasbt/rpm/RPM-GPG-KEY-sbt
EOF

    dnf install -y sbt
}

install_from_zip() {
    
    SBT_VERSION="1.12.9"
    SBT_URL="https://github.com/sbt/sbt/releases/download/v${SBT_VERSION}/sbt-${SBT_VERSION}.tgz"
    
    cd /tmp
    curl -L -o sbt.tgz "$SBT_URL"
    
    tar -xzf sbt.tgz -C /usr/local/share/
    
    ln -sf "/usr/local/share/sbt/bin/sbt" /usr/local/bin/sbt
    
    rm /tmp/sbt.tgz
}

echo -e "Installing SBT on ${OS}:${VER}"
case "$OS" in
    ubuntu|debian)
        install_debian_ubuntu
        ;;
    fedora)
        install_fedora
        ;;
    *)
        install_from_zip
        ;;
esac

sbt --version

echo -e "SBT was successfully installed"
