#ifndef _QUEUE_MSG_H_
#define _QUEUE_MSG_H_

#include "ZW_typedefs.h"


typedef struct _msg_lst {
    struct _msg_lst *next;        ///< Point to the next list entry
    uint16_t dat_sz;              ///< Data size
    uint16_t rsvd;                ///< Padding to make sure wr_buf is 4-byte aligned
    uint8_t buf[1];
} msg_lst_t, *msg_lst_p;

void
queueMsgInit();

void
sendMsg2ZIP(
    uint8_t *msg,
    uint16_t len
);

msg_lst_p
rcvMsgFromZIP();

void
sendMsg2CAPI(
    uint8_t *msg,
    uint16_t len
);

msg_lst_p
rcvMsgFromCAPI();

#endif