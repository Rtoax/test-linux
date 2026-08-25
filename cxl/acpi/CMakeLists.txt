cmake_minimum_required(VERSION 3.18 FATAL_ERROR)
project(cxl-acpi LANGUAGES C)

include_directories(".")
include_directories("../../libs/")

add_executable(cedt cedt.c cfmws.c chbs.c cxims.c rdpas.c)
