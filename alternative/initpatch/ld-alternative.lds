SECTIONS
{
	.altinstructions : {
		__alt_instructions = .;
		*(.altinstructions)
		__alt_instructions_end = .;
	}
}
INSERT AFTER .text;
