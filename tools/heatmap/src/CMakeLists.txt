find_library(RT rt /usr/lib64)
find_library(MATH m /usr/lib64)

link_libraries(${RT} ${MATH})

include_directories(.)

add_definitions(-Wall -Werror)

add_executable(heatmap main.c addr.c common.c)
