#!/bin/bash

echo "cat /*[local-name()='Envelope']/*[local-name()='Body']/*[local-name()='grtHgetRed']/*[local-name()='ResponseType']" | xmllint --shell Det.xml | sed '/^\/ >/d' | sed 's/<[^>]*.//g'

