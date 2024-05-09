#include <stdio.h>
#include <stdlib.h>

/**
 *       0 1 2 3 4 5 6 7
 *    0  . / 0 1 2 3 4 5
 *    8  6 7 8 9 A B C D
 *    16 E F G H I J K L
 *    24 M N O P Q R S T
 *    32 U V W X Y Z a b
 *    40 c d e f g h i j
 *    48 k l m n o p q r
 *    56 s t u v w x y z
 */

int main(void)
{
	printf("%s\n", l64a(56));
	printf("%ld\n", a64l("A"));

	return 0;
}
