find_library(RT rt /usr/lib64)

link_libraries(${RT})

add_definitions(-Wall -Werror)

add_executable(fstabd main.c)
