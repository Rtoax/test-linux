/**
 *
 * TODO: https://lists.denx.de/pipermail/u-boot/2021-August/459275.html
 */
#include <stdio.h>

#if 0
 uint32_t __efi_runtime crc32_no_comp(uint32_t crc, const Bytef *buf, uInt len)
 {
+#ifdef CONFIG_ARM64_CRC32
+    crc = cpu_to_le32(crc);
+    while (len--)
+        crc = __builtin_aarch64_crc32b(crc, *buf++);
+    return le32_to_cpu(crc);
+#else
     const uint32_t *tab = crc_table;
     const uint32_t *b =(const uint32_t *)buf;
     size_t rem_len;
@@ -221,6 +227,7 @@ uint32_t __efi_runtime crc32_no_comp(uint32_t crc, const Bytef *buf, uInt len)
     }

     return le32_to_cpu(crc);
+#endif
 }
#endif