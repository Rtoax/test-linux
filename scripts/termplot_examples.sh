#!/bin/bash
set -e

. ./termplot.sh

test_drawline_1() {
	readonly bnd=5
	clear
	drawline --xstart ${bnd} --xend $((${TWIDTH} - ${bnd})) --yy $((${THEIGHT} - ${bnd})) --arrow
	drawline --xx $((${TWIDTH} - ${bnd})) --ystart $((${THEIGHT} - ${bnd})) --yend ${bnd} --arrow
	drawline --xstart $((${TWIDTH} - ${bnd})) --xend ${bnd} --yy ${bnd} --arrow
	drawline --xx ${bnd} --ystart ${bnd} --yend $((${THEIGHT} - ${bnd})) --arrow
	gotoxy ${THEIGHT} 0
	echo
}

test_drawline_2() {
	clear
	drawline --xstart ${bnd} --ystart ${bnd} \
		--xend $((${TWIDTH} - ${bnd})) --yend $((${THEIGHT} - ${bnd}))
	drawline --xstart ${bnd} --ystart ${bnd} \
		--xend $((${TWIDTH} / 2 - ${bnd})) --yend $((${THEIGHT} - ${bnd}))
	drawline --xstart ${bnd} --ystart ${bnd} \
		--xend $((${TWIDTH} - ${bnd})) --yend $((${THEIGHT} / 2 - ${bnd}))
	echo
}

test_drawcurve_1() {
	clear
	drawcurve -x 1 -y 1 \
		-x 2 -y 2 \
		-x 20 -y 2 \
		-x 20 -y 20 \
		-x 30 -y 30
}

#verbose

#test_drawline_1
#test_drawline_2
test_drawcurve_1
