#ifndef __SHMQ_H
#define __SHMQ_H 1


#define SHMQ_MAJOR	        231
#define SHMQ_DEV_NAME	    "shmqueue"



/* ioctl cmd */
typedef enum shmq_ioc_cmd {
#define SHMQ_IOC_MAGIC  0xf0000000
    SHMQ_IOC_WAIT       = (SHMQ_IOC_MAGIC | (1L<<0)),
    SHMQ_IOC_WAKE_UP    = (SHMQ_IOC_MAGIC | (1L<<2)),
}shmq_ioc_cmd_t;


/* shm queue hdr info */
struct shmqhdr {
    
}__attribute__((packed));


typedef struct shmq {
    struct shmqhdr shmq_hdr;
    
    struct {
        void        *data_ptr;
        unsigned int data_len;
    }__attribute__((packed)) shmq_data;
}__attribute__((packed)) shmq_t;


/**/

#endif /*<__SHMQ_H>*/