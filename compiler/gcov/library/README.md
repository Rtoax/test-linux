FDO&AutoFDO Library tests
=========================

# Branches Predictions

```
LibraryType     FDO         AutoFDO
-----------------------------------
executable       Ok           Ok
static         Not ok       Not ok
dynamic          Ok         Not ok
```

```
Before Optmizization:
 0x00000000004031f3 <+531>:	call   0x402f80 <test_fn1_branch_1>
 0x000000000040320c <+556>:	call   0x402bc0 <test_fn1_branch_11>
 0x0000000000403244 <+612>:	call   0x402c20 <test_fn1_branch_10>
 0x000000000040325c <+636>:	call   0x402c80 <test_fn1_branch_9>
 0x000000000040327c <+668>:	call   0x402ce0 <test_fn1_branch_8>
 0x000000000040329c <+700>:	call   0x402d40 <test_fn1_branch_7>
 0x00000000004032bc <+732>:	call   0x402e00 <test_fn1_branch_5>
 0x00000000004032dc <+764>:	call   0x402da0 <test_fn1_branch_6>
 0x00000000004032fc <+796>:	call   0x402ec0 <test_fn1_branch_3>
 0x000000000040331c <+828>:	call   0x402e60 <test_fn1_branch_4>
 0x0000000000403335 <+853>:	call   0x402f20 <test_fn1_branch_2>

After Optmizization:
 0x000000000040140a <+442>:	call   0x401520 <test_fn1_branch_1>
 0x0000000000401437 <+487>:	call   0x401530 <test_fn1_branch_2>
 0x000000000040146b <+539>:	call   0x401540 <test_fn1_branch_3>
 0x000000000040148b <+571>:	call   0x401550 <test_fn1_branch_4>
 0x000000000040149b <+587>:	call   0x401560 <test_fn1_branch_5>
 0x00000000004014ab <+603>:	call   0x401570 <test_fn1_branch_6>
 0x00000000004014bb <+619>:	call   0x401580 <test_fn1_branch_7>
 0x00000000004014cb <+635>:	call   0x401590 <test_fn1_branch_8>
 0x00000000004014db <+651>:	call   0x4015a0 <test_fn1_branch_9>
 0x00000000004014eb <+667>:	call   0x4015b0 <test_fn1_branch_10>
 0x0000000000401503 <+691>:	call   0x401510 <test_fn1_branch_11>
```


# Function Layout

```
LibraryType     FDO         AutoFDO
-----------------------------------
executable      Ok           Ok
static          Ok           Ok(low precision than FDO)
dynamic         Ok           Ok(low precision than FDO)
```

```
           A
          / \
     100 /   \ 10
        /     \
       B       C
       |100    | 10
       D       E
       |100    | 10
       F       G
       |100    | 10
       H       I
        \     /
     100 \   / 10
          \ /
           J

Before Optmizization:
 00000000000036c0 lib_layout_J
 0000000000003720 lib_layout_I
 0000000000003790 lib_layout_H
 0000000000003800 lib_layout_G
 0000000000003870 lib_layout_F
 00000000000038e0 lib_layout_E
 0000000000003950 lib_layout_D
 00000000000039c0 lib_layout_C
 0000000000003a30 lib_layout_B
 0000000000003aa0 lib_layout_A

After Optmizization:
 000000000000121a lib_layout_I
 0000000000001228 lib_layout_G
 0000000000001236 lib_layout_E
 0000000000001244 lib_layout_C
 0000000000001840 lib_layout_A
 0000000000001870 lib_layout_B
 0000000000001880 lib_layout_D
 0000000000001890 lib_layout_F
 00000000000018a0 lib_layout_H
 00000000000018b0 lib_layout_J
```

