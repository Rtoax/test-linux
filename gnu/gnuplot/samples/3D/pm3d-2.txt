# 设置视角，(0,0) 将投影到底面上去
set view 0,0
# 把 z 轴上的数字给去掉
unset ztics
unset surface
splot x**2+y**2
reset
