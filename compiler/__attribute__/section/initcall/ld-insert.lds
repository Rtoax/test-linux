SECTIONS
{
	.rongtao.init.func : {
		/* . = ALIGN(4);*/
		init_start = .;
		*(.rongtao.init.func*)
		init_end = .;
	}
}
INSERT AFTER .text;
