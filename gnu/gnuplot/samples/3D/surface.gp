# 设置三维图表面的网格的数目
set dgrid3d 100,100
# 设置画等高线
set contour
# 设置等高线的疏密和范围，数据从   -0.2到0.2中间每隔0.01画一条线
set cntrparam levels incremental -0.9,0.1,0.9
# 去掉上面的三维图形
unset surface
set view 0,0
unset key
splot [-pi:pi] [-pi:pi] sin(x)*cos(y)
