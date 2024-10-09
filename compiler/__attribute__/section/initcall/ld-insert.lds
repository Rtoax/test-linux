SECTIONS
{
	.test-linux.init.func : {
		/* . = ALIGN(4);*/
		init_start = .;
		*(.test-linux.init.func*)
		init_end = .;
	}
}
INSERT AFTER .text;
