#!/bin/bash
make stress
MALLOC_CONF="retain:false" ./stress
