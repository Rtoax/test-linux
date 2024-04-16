/**
 * The '#ident' directive takes one argument, a string constant. On some
 * systems, that string constant is copied into a special segment of the
 * object fle. On other systems, the directive is ignored. The '#sccs'
 * directive is a synonym for '#ident'.
 * These directives are not part of the C standard, but they are not ofcial
 * GNU extensions either. What historical information we have been able to
 * find, suggests they originated with System V.
 * The null directive consists of a '#' followed by a newline, with only
 * whitespace (including comments) in between. A null directive is understood
 * as a preprocessing directive but has no eﬀect on the preprocessor output.
 * The primary signifcance of the existence of the null directive is that an
 * input line consisting of just a ‘#’ will produce no output, rather than a
 * line of output containing just a ‘#’. Supposedly some old C programs
 * contain such lines.
 */
int main(void)
{
	return 0;
}
