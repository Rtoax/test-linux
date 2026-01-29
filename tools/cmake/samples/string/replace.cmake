set(versions "12.1 2.1 2.10 abc2.1def 2.1")
set(versions1)
set(versions2)

string(REPLACE "2.1" "2.1(2.0)" versions1 "${versions}")
string(REGEX REPLACE "(^|[^0-9])2\\.1([^0-9]|$)" "\\12.1(2.0)\\2" versions2 "${versions}")

message(STATUS "versions: ${versions}")
message(STATUS "versions1: ${versions1}")
message(STATUS "versions2: ${versions2}")
