#!/bin/bash
# ref: https://www.myfreax.com/how-to-install-visual-studio-code-on-debian-11

sudo apt update
sudo apt install software-properties-common apt-transport-https curl

curl -sSL https://packages.microsoft.com/keys/microsoft.asc | sudo apt-key add -

sudo add-apt-repository "deb [arch=amd64] https://packages.microsoft.com/repos/vscode stable main"

sudo apt update
sudo apt install code -y
