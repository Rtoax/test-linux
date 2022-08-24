// https://github.com/faxiang1230/Demo/blob/master/kernel/alternative-instruction/macro.c
//gcc -c macro.c -o macro.o
//objdump -dsShx macro.o > macro.obj

#include <stdio.h>
#define X86_FEATURE_SMAP	(9*32+20) /* Supervisor Mode Access Prevention */
#define __stringify(x) #x
#define b_replacement(num)  "664"#num                                           
#define e_replacement(num)  "665"#num                                           
                                                                                
#define alt_end_marker      "663"                                               
#define alt_slen        "662b-661b"                                             
#define alt_pad_len     alt_end_marker"b-662b"                                  
#define alt_total_slen      alt_end_marker"b-661b"                              
#define alt_rlen(num)       e_replacement(num)"f-"b_replacement(num)"f"         
                                                                                
#define __OLDINSTR(oldinstr, num)                   \                           
    "661:\n\t" oldinstr "\n662:\n"                  \                           
    ".skip -(((" alt_rlen(num) ")-(" alt_slen ")) > 0) * "      \               
        "((" alt_rlen(num) ")-(" alt_slen ")),0x90\n" 

#define OLDINSTR(oldinstr, num)                     \                           
    __OLDINSTR(oldinstr, num)                   \                               
    alt_end_marker ":\n"                                                        
                                                                                
/*                                                                              
 * max without conditionals. Idea adapted from:                                 
 * http://graphics.stanford.edu/~seander/bithacks.html#IntegerMinOrMax          
 *                                                                              
 * The additional "-" is needed because gas works with s32s.                    
 */                                                                             
#define alt_max_short(a, b) "((" a ") ^ (((" a ") ^ (" b ")) & -(-((" a ") - (" b ")))))"
                                                                                
/*                                                                              
 * Pad the second replacement alternative with additional NOPs if it is         
 * additionally longer than the first replacement alternative.                  
 */                                                                             
#define OLDINSTR_2(oldinstr, num1, num2) \                                      
    "661:\n\t" oldinstr "\n662:\n"                              \               
    ".skip -((" alt_max_short(alt_rlen(num1), alt_rlen(num2)) " - (" alt_slen ")) > 0) * "  \
        "(" alt_max_short(alt_rlen(num1), alt_rlen(num2)) " - (" alt_slen ")), 0x90\n"  \
    alt_end_marker ":\n"                                                        
                                                                                
#define ALTINSTR_ENTRY(feature, num)                          \                 
    " .long 661b - .\n"             /* label           */ \                     
    " .long " b_replacement(num)"f - .\n"       /* new instruction */ \         
    " .word " __stringify(feature) "\n"     /* feature bit     */ \             
    " .byte " alt_total_slen "\n"           /* source len      */ \             
    " .byte " alt_rlen(num) "\n"            /* replacement len */ \             
    " .byte " alt_pad_len "\n"          /* pad len */                           
                                                                                
#define ALTINSTR_REPLACEMENT(newinstr, feature, num)    /* replacement */     \ 
    b_replacement(num)":\n\t" newinstr "\n" e_replacement(num) ":\n\t"          
                                                                                
/* alternative assembly primitive: */                                           
#define ALTERNATIVE(oldinstr, newinstr, feature)            \                   
    OLDINSTR(oldinstr, 1)                       \                               
    ".pushsection .altinstructions,\"a\"\n"             \                       
    ALTINSTR_ENTRY(feature, 1)                  \                               
    ".popsection\n"                         \                                   
    ".pushsection .altinstr_replacement, \"ax\"\n"          \                   
    ALTINSTR_REPLACEMENT(newinstr, feature, 1)          \                       
    ".popsection"

#define mb() asm volatile(ALTERNATIVE("lock; addl $0,0(%%esp)", "mfence;mfence;mfence;mfence", \
			                      X86_FEATURE_XMM2) ::: "memory", "cc")

void fun()
{
	mb();
}
