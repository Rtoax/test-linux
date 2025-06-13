#!/usr/bin/env python

def split_c_string_array(input_str, NAME_MAX):
    chunks = [input_str[i:i+NAME_MAX] for i in range(0, len(input_str), NAME_MAX)]
    return [chunk.split('\x00', 1)[0] for chunk in chunks]

if __name__ == "__main__":
    NAME_MAX = 8
    MAX_ENTRIES = 3

    input_string = "AAAA\x00\x00\x00\x00BB\x00\x00\x00\x00\x00\x00CCCCC\x00\x00\x00"

    names = split_c_string_array(input_string, NAME_MAX)
    print(names)
