/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  μITRON4.0仕様 Real-Time OS                   */
/*    プロセッサ抽象化コンポーネント (IA32用タイマ処理)                           */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#ifndef __hos_v4__sample__ostimer_h__
#define __hos_v4__sample__ostimer_h__
#include "itron.h"
#define PERIOD  1000   /*  Set timer tick 1000 us(NOTE:The unit is us)  */
#define PIT_I8254_INPFREQ   1193182UL
#define PIT_FREQ         (1000UL / TICKMS)
#define PIT_DIVISOR      (PIT_I8254_INPFREQ / PIT_FREQ)UL
/* i8254 Programmable Interval Timer */
/*
 *                           +-----------+ 
 *                           |Port Number|
 *                           +-----------+
 *
 *              +---------------------------------------+
 *              | Port   Description                    |
 *              +---------------------------------------+
 *              | 40h    Channel 0 counter (read/write) |
 *              | 41h    Channel 1 counter (read/write) |
 *              | 42h    Channel 2 counter (read/write) |
 *              | 43h    Control Word (write only)      |
 *              +---------------------------------------+
 */
#define PIT_PORT_CHANNEL0  0x40  /* I/O port for timer channel 0 */
#define PIT_PORT_CHANNEL1  0x41  /* I/O port for timer channel 1 */
#define PIT_PORT_CHANNEL2  0x42  /* I/O port for timer channel 2 */
#define PIT_PORT_MODECNTL  0x43  /* I/O port for controling mode */

/*
 *                     +------------------+
 *                     | The Control Word |
 *                     +------------------+
 *
 *               +---+---+---+---+---+---+---+---+
 *               | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 *               +---+---+---+---+---+---+---+---+
 *                 *-+-*   *-+-*   *---+---*   *-- BCD 0 - Binary 16 bit
 *                   |       |         |               1 - BCD 4 decades
 * +-----------------+----+  |         |
 * | Select Counter       |  |         +---------- Mode Number 0 - 5
 * | 0 - Select Counter 0 |  |
 * | 1 - Select Counter 1 |  |         +----------------------------+
 * | 2 - Select Counter 2 |  |         | Read/Load                  |
 * +----------------------+  |         | 0 - Counter Latching       |
 *                           +---------+ 1 - Read/Load LSB only     |
 *                                     | 2 - Read/Load MSB only     |
 *                                     | 3 - Read/Load LSB then MSB |
 *                                     +----------------------------+
 *
 */
#define PIT_CWD_TYPE_SHIFT 0x00
#define PIT_CWD_BIN16      0x00
#define PIT_CWD_BCD4       0x01
#define PIT_CWD_MODE_SHIFT 0x01
#define PIT_CWD_MODE0      0x00
#define PIT_CWD_MODE1      0x01
#define PIT_CWD_MODE2      0x02
#define PIT_CWD_MODE3      0x03
#define PIT_CWD_MODE4      0x04
#define PIT_CWD_MODE5      0x05
#define PIT_CWD_RLSHIFT    0x03
#define PIT_CWD_RLCNTLTCH  0x00
#define PIT_CWD_RLLSB      0x01
#define PIT_CWD_RLMSB      0x02
#define PIT_CWD_RLLMB      0x03
#define PIT_CWD_CNTSHIFT   0x05
#define PIT_CWD_CNT0       0x00
#define PIT_CWD_CNT1       0x01
#define PIT_CWD_CNT2       0x02
/*  Control Word for Counter0  */
#define PIT_CW_MODE0_CNT0  ( ( (PIT_CWD_CNT0)  << (PIT_CWD_CNTSHIFT)  ) |  \
                             ( (PIT_CWD_RLLMB) << (PIT_CWD_RLSHIFT)   ) |  \
                             ( (PIT_CWD_MODE0) << (PIT_CWD_MODE_SHIFT)) |  \
                             ( (PIT_CWD_BIN16) << (PIT_CWD_TYPE_SHIFT)) )
#define PIT_CW_MODE1_CNT0  ( ( (PIT_CWD_CNT0)  << (PIT_CWD_CNTSHIFT)  ) |  \
                             ( (PIT_CWD_RLLMB) << (PIT_CWD_RLSHIFT)   ) |  \
                             ( (PIT_CWD_MODE1) << (PIT_CWD_MODE_SHIFT)) |  \
                             ( (PIT_CWD_BIN16) << (PIT_CWD_TYPE_SHIFT)) )
#define PIT_CW_MODE2_CNT0  ( ( (PIT_CWD_CNT0)  << (PIT_CWD_CNTSHIFT)  ) |  \
                             ( (PIT_CWD_RLLMB) << (PIT_CWD_RLSHIFT)   ) |  \
                             ( (PIT_CWD_MODE2) << (PIT_CWD_MODE_SHIFT)) |  \
                             ( (PIT_CWD_BIN16) << (PIT_CWD_TYPE_SHIFT)) )
#define PIT_CW_MODE3_CNT0  ( ( (PIT_CWD_CNT0)  << (PIT_CWD_CNTSHIFT)  ) |  \
                             ( (PIT_CWD_RLLMB) << (PIT_CWD_RLSHIFT)   ) |  \
                             ( (PIT_CWD_MODE3) << (PIT_CWD_MODE_SHIFT)) |  \
                             ( (PIT_CWD_BIN16) << (PIT_CWD_TYPE_SHIFT)) )
#define PIT_CW_MODE4_CNT0  ( ( (PIT_CWD_CNT0)  << (PIT_CWD_CNTSHIFT)  ) |  \
                             ( (PIT_CWD_RLLMB) << (PIT_CWD_RLSHIFT)   ) |  \
                             ( (PIT_CWD_MODE4) << (PIT_CWD_MODE_SHIFT)) |  \
                             ( (PIT_CWD_BIN16) << (PIT_CWD_TYPE_SHIFT)) )
#define PIT_CW_MODE5_CNT0  ( ( (PIT_CWD_CNT0)  << (PIT_CWD_CNTSHIFT)  ) |  \
                             ( (PIT_CWD_RLLMB) << (PIT_CWD_RLSHIFT)   ) |  \
                             ( (PIT_CWD_MODE5) << (PIT_CWD_MODE_SHIFT)) |  \
                             ( (PIT_CWD_BIN16) << (PIT_CWD_TYPE_SHIFT)) )

/*  Control Word for Counter1  */
#define PIT_CW_MODE0_CNT1  ( ( (PIT_CWD_CNT1)  << (PIT_CWD_CNTSHIFT)  ) |  \
                             ( (PIT_CWD_RLLMB) << (PIT_CWD_RLSHIFT)   ) |  \
                             ( (PIT_CWD_MODE0) << (PIT_CWD_MODE_SHIFT)) |  \
                             ( (PIT_CWD_BIN16) << (PIT_CWD_TYPE_SHIFT)) )
#define PIT_CW_MODE1_CNT1  ( ( (PIT_CWD_CNT1)  << (PIT_CWD_CNTSHIFT)  ) |  \
                             ( (PIT_CWD_RLLMB) << (PIT_CWD_RLSHIFT)   ) |  \
                             ( (PIT_CWD_MODE1) << (PIT_CWD_MODE_SHIFT)) |  \
                             ( (PIT_CWD_BIN16) << (PIT_CWD_TYPE_SHIFT)) )
#define PIT_CW_MODE2_CNT1  ( ( (PIT_CWD_CNT1)  << (PIT_CWD_CNTSHIFT)  ) |  \
                             ( (PIT_CWD_RLLMB) << (PIT_CWD_RLSHIFT)   ) |  \
                             ( (PIT_CWD_MODE2) << (PIT_CWD_MODE_SHIFT)) |  \
                             ( (PIT_CWD_BIN16) << (PIT_CWD_TYPE_SHIFT)) )
#define PIT_CW_MODE3_CNT1  ( ( (PIT_CWD_CNT1)  << (PIT_CWD_CNTSHIFT)  ) |  \
                             ( (PIT_CWD_RLLMB) << (PIT_CWD_RLSHIFT)   ) |  \
                             ( (PIT_CWD_MODE3) << (PIT_CWD_MODE_SHIFT)) |  \
                             ( (PIT_CWD_BIN16) << (PIT_CWD_TYPE_SHIFT)) )
#define PIT_CW_MODE4_CNT1  ( ( (PIT_CWD_CNT1)  << (PIT_CWD_CNTSHIFT)  ) |  \
                             ( (PIT_CWD_RLLMB) << (PIT_CWD_RLSHIFT)   ) |  \
                             ( (PIT_CWD_MODE4) << (PIT_CWD_MODE_SHIFT)) |  \
                             ( (PIT_CWD_BIN16) << (PIT_CWD_TYPE_SHIFT)) )
#define PIT_CW_MODE5_CNT1  ( ( (PIT_CWD_CNT1)  << (PIT_CWD_CNTSHIFT)  ) |  \
                             ( (PIT_CWD_RLLMB) << (PIT_CWD_RLSHIFT)   ) |  \
                             ( (PIT_CWD_MODE5) << (PIT_CWD_MODE_SHIFT)) |  \
                             ( (PIT_CWD_BIN16) << (PIT_CWD_TYPE_SHIFT)) )

/*  Control Word for Counter2  */
#define PIT_CW_MODE0_CNT2  ( ( (PIT_CWD_CNT2)  << (PIT_CWD_CNTSHIFT)  ) |  \
                             ( (PIT_CWD_RLLMB) << (PIT_CWD_RLSHIFT)   ) |  \
                             ( (PIT_CWD_MODE0) << (PIT_CWD_MODE_SHIFT)) |  \
                             ( (PIT_CWD_BIN16) << (PIT_CWD_TYPE_SHIFT)) )
#define PIT_CW_MODE1_CNT2  ( ( (PIT_CWD_CNT2)  << (PIT_CWD_CNTSHIFT)  ) |  \
                             ( (PIT_CWD_RLLMB) << (PIT_CWD_RLSHIFT)   ) |  \
                             ( (PIT_CWD_MODE1) << (PIT_CWD_MODE_SHIFT)) |  \
                             ( (PIT_CWD_BIN16) << (PIT_CWD_TYPE_SHIFT)) )
#define PIT_CW_MODE2_CNT2 ( ( (PIT_CWD_CNT2)  << (PIT_CWD_CNTSHIFT)  ) |  \
                             ( (PIT_CWD_RLLMB) << (PIT_CWD_RLSHIFT)   ) |  \
                             ( (PIT_CWD_MODE2) << (PIT_CWD_MODE_SHIFT)) |  \
                             ( (PIT_CWD_BIN16) << (PIT_CWD_TYPE_SHIFT)) )
#define PIT_CW_MODE3_CNT2  ( ( (PIT_CWD_CNT2)  << (PIT_CWD_CNTSHIFT)  ) |  \
                             ( (PIT_CWD_RLLMB) << (PIT_CWD_RLSHIFT)   ) |  \
                             ( (PIT_CWD_MODE3) << (PIT_CWD_MODE_SHIFT)) |  \
                             ( (PIT_CWD_BIN16) << (PIT_CWD_TYPE_SHIFT)) )
#define PIT_CW_MODE4_CNT2  ( ( (PIT_CWD_CNT2)  << (PIT_CWD_CNTSHIFT)  ) |  \
                             ( (PIT_CWD_RLLMB) << (PIT_CWD_RLSHIFT)   ) |  \
                             ( (PIT_CWD_MODE4) << (PIT_CWD_MODE_SHIFT)) |  \
                             ( (PIT_CWD_BIN16) << (PIT_CWD_TYPE_SHIFT)) )
#define PIT_CW_MODE5_CNT2  ( ( (PIT_CWD_CNT2)  << (PIT_CWD_CNTSHIFT)  ) |  \
                             ( (PIT_CWD_RLLMB) << (PIT_CWD_RLSHIFT)   ) |  \
                             ( (PIT_CWD_MODE5) << (PIT_CWD_MODE_SHIFT)) |  \
                             ( (PIT_CWD_BIN16) << (PIT_CWD_TYPE_SHIFT)) )
/*  Function Proto-types  */
void ostim_init(VP_INT exinf);
void ostim_hdr(VP_INT exinf);
#endif  /*  __hos_v4__sample__ostimer_h__  */
/* ------------------------------------------------------------------------ */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
