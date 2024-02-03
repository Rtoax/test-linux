#!/bin/env perl

open (F, "/etc/os-release") || die "S!";
while (<F>) {
	print;
}
