# TODO: use it
define print_elf_reloc
	@echo -e "# $(1)" > ${1}.reloc
	@readelf --relocs --wide $(1) >> ${1}.reloc
endef

%.reloc:
	$(call log_tgt,READELF,$(@))
	@$(call print_elf_reloc,$(@))
