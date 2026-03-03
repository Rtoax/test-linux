function(print_var name)
  message(STATUS "name = ${name}")
endfunction()

print_var("Var1")
print_var("Var2")
