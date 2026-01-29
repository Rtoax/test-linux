set(versions "12.1 2.1 2.10 abc2.1def 2.1")
string(REPLACE "2.1" "2.1(2.0)" versions "${versions}")
message(STATUS "versions: ${versions}")
