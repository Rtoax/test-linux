target-y += error
target-y += error_print_progname
target-y += error_at_line

prog-y += $(filter-out error_print_progname error_at_line, ${target-y})
