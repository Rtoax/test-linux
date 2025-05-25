SECTIONS
{
	.test-linux.init.data : {
		/* . = ALIGN(4);*/
		data_start = .;
		*(.test-linux.init.data*)
		data_end = .;
	}
}
INSERT AFTER .data;
