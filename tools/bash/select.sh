#!/bin/bash
# https://blog.csdn.net/lizhengyu891231/article/details/123868931

PS3='Choose your favorite food: '
foods=("Pizza" "Pho" "Tacos" "Quit")

select_1() {
	select fav in "${foods[@]}"; do
	case $fav in
		"Pizza")
			echo "Americans eat roughly 100 acres of $fav each day!"
			# optionally call a function or run some code here
			;;
		"Pho")
			echo "$fav is a Vietnamese soup that is commonly mispronounced like go, instead of duh."
			# optionally call a function or run some code here
			;;
		"Tacos")
			echo "According to NationalTacoDay.com, Americans are eating 4.5 billion $fav each year."
			# optionally call a function or run some code here
			break
			;;
		"Quit")
			echo "User requested exit"
			exit
			;;
		*)
			echo "invalid option $REPLY";;
	esac
	done
}

echo 3 | select_1
