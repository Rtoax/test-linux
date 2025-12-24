#!/bin/bash

pytorch_pip=https://download.pytorch.org/whl/cpu/
tsinghua_pip=https://pypi.tuna.tsinghua.edu.cn/simple/
pip_71=http://10.253.12.71/mirrors/whl-packages/

requirement_ascend=requirement-ascend.txt

requirement_txt=${requirement_ascend}
remote_pip=${pip_71}


pip3 install \
	--requirement=${requirement_txt} \
	--index-url ${remote_pip} \
	--trusted-host 10.253.12.71
