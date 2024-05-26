#include <stdio.h>
#include <printf.h>
#include <string.h>


int prec;		 /* Precision.  */
int width;			/* Width.  */
wchar_t spec;		 /* Format letter.  */

unsigned int is_long_double;/* L flag.  */
unsigned int is_short;  /* h flag.  */
unsigned int is_long;   /* l flag.  */

unsigned int alt;	   /* # flag.  */
unsigned int space;	 /* Space flag.  */
unsigned int left;	  /* - flag.  */
unsigned int showsign;  /* + flag.  */
unsigned int group;	 /* ' flag.  */
unsigned int extra;	 /* For special use.  */
unsigned int is_char;   /* hh flag.  */
unsigned int wide;	  /* Nonzero for wide character streams.  */
unsigned int i18n;	  /* I flag.  */
unsigned int __pad;	 /* Unused so far.  */
unsigned short int user;  /* Bits for user-installed modifiers.  */


int my_printf_function(FILE *__stream, const struct printf_info *__info,
		       const void *const *__args)
{
	printf("call %s\n", __func__);

	prec = __info->prec;
	width = __info->width;
	spec = __info->spec;
	is_long_double = __info->is_long_double;
	is_short = __info->is_short;
	is_long = __info->is_long;
	alt = __info->alt;
	space = __info->space;
	left = __info->left;
	showsign = __info->showsign;
	group = __info->group;
	extra = __info->extra;
	is_char = __info->is_char;
	wide = __info->wide;
	i18n = __info->i18n;
	user = __info->user;
	return 0;
}

int my_printf_arginfo_size_function(const struct printf_info *__info,
				    size_t __n, int *__argtypes,
				    int *__size)
{
	printf("call %s\n", __func__);
	return 0;
}

int main(void)
{
	register_printf_specifier('d', my_printf_function, my_printf_arginfo_size_function);

	printf("%d %d\n", 1, 2);

	register_printf_specifier('d', NULL, NULL);

	printf("%d %d\n", 1, 2);

	printf("prec = %d.\n", prec);
	printf("width = %d.\n", width);
	printf("spec = %d.\n", spec);
	printf("is_long_double = %d.\n", is_long_double);
	printf("is_short = %d.\n", is_short);
	printf("is_long = %d.\n", is_long);
	printf("alt = %d.\n", alt);
	printf("space = %d.\n", space);
	printf("left = %d.\n", left);
	printf("left = %d.\n", left);
	printf("group = %d.\n", group);
	printf("extra = %d.\n", extra);
	printf("is_char = %d.\n", is_char);
	printf("wide = %d.\n", wide);
	printf("i18n = %d.\n", i18n);
	printf("user = %d.\n", user);

	return 0;
}
