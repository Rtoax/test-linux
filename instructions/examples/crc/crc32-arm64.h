/**
 * Arm64 crc32 asm header
 *
 * Refs:
 * http://main.lv/writeup/arm64_assembly_crc32.md
 *
 * Rewrite By Rong Tao <rtoax@foxmail.com>
 */
#if !defined(__aarch64__)
# error "Just support aarch64"
#endif

/*
 * https://android.googlesource.com/platform/external/linux-kselftest/+/d97034ccdf0a13ad86f00945df245bbaf0780478/arch/arm64/crypto/crc32-arm64.c
 */
/* crc32 */
#define CRC32X(crc, value) __asm__("crc32x %w[c], %w[c], %x[v]":[c]"+r"(crc):[v]"r"(value))
#define CRC32W(crc, value) __asm__("crc32w %w[c], %w[c], %w[v]":[c]"+r"(crc):[v]"r"(value))
#define CRC32H(crc, value) __asm__("crc32h %w[c], %w[c], %w[v]":[c]"+r"(crc):[v]"r"(value))
#define CRC32B(crc, value) __asm__("crc32b %w[c], %w[c], %w[v]":[c]"+r"(crc):[v]"r"(value))
#if defined(USE_BUILTIN)
#define CRC32B(crc, value) __builtin_aarch64_crc32b
#endif
/* crc32c */
#define CRC32CX(crc, value) __asm__("crc32cx %w[c], %w[c], %x[v]":[c]"+r"(crc):[v]"r"(value))
#define CRC32CW(crc, value) __asm__("crc32cw %w[c], %w[c], %w[v]":[c]"+r"(crc):[v]"r"(value))
#define CRC32CH(crc, value) __asm__("crc32ch %w[c], %w[c], %w[v]":[c]"+r"(crc):[v]"r"(value))
#define CRC32CB(crc, value) __asm__("crc32cb %w[c], %w[c], %w[v]":[c]"+r"(crc):[v]"r"(value))

/**
 * Code on the Kunpeng platform
 * https://support.huaweicloud.com/intl/en-us/codeprtr-kunpenggrf/kunpengtaishanporting_12_0029.html
 */
#if defined(__x86_64__)
static inline uint32_t crc32_u8(uint32_t crc, uint8_t v) {
    __asm__("crc32b %1, %0" : "+r"(crc) : "rm"(v));
    return crc;
}
static inline uint32_t crc32_u16(uint32_t crc, uint16_t v) {
    __asm__("crc32w %1, %0" : "+r"(crc) : "rm"(v));
    return crc;
}
static inline uint32_t crc32_u32(uint32_t crc, uint32_t v) {
    __asm__("crc32l %1, %0" : "+r"(crc) : "rm"(v));
    return crc;
}
static inline uint32_t crc32_u64(uint32_t crc, uint64_t v) {
    uint64_t result = crc;
    __asm__("crc32q %1, %0" : "+r"(result) : "rm"(v));
    return result;
}
#elif defined(__aarch64__)
static inline uint32_t crc32_u8(uint32_t crc, uint8_t value) {
    __asm__("crc32cb %w[c], %w[c], %w[v]":[c]"+r"(crc):[v]"r"(value));
    return crc;
}
static inline uint32_t crc32_u16(uint32_t crc, uint16_t value) {
    __asm__("crc32ch %w[c], %w[c], %w[v]":[c]"+r"(crc):[v]"r"(value));
    return crc;
}
static inline uint32_t crc32_u32(uint32_t crc, uint32_t value) {
    __asm__("crc32cw %w[c], %w[c], %w[v]":[c]"+r"(crc):[v]"r"(value));
    return crc;
}
static inline uint32_t crc32_u64(uint32_t crc, uint64_t value) {
    __asm__("crc32cx %w[c], %w[c], %x[v]":[c]"+r"(crc):[v]"r"(value));
    return crc;
}
#endif
