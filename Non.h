
/*8253 and AD574*/

#define  TRUE 1
#define  FALSE 0
#define  LINELEN  30
#define  WORDLEN  5
#define  BUFF_OVERFLOW 2
#define IRQ2_OFF 0x04
#define IRQ2_ON  0xfb

#define BASEPORT          0x300
#define TCNTRL        BASEPORT+7
#define CNT0          BASEPORT+4
#define CNT1          BASEPORT+5
#define CNT2          BASEPORT+6
#define TRIGGER_PORT  BASEPORT+0
#define STATE_PORT    BASEPORT+2
#define DATA_PORT     BASEPORT+8

#define PCNTRL BASEPORT+0x0f
#define PA  BASEPORT+0x0c
#define PB  BASEPORT+0x0d
#define PC  BASEPORT+0x0e

#define SMALL_FONT 2
#define RIGHT 77
#define LEFT  75
#define UP 72
#define DOWN  80
#define ESC   0x1B
#define ENTER 13
#define PAGEUP 73
#define PAGEDOWN 81
#define F45SN "8048019"
//#define F45SN "7856014" NAnjing


//#define NMBOFSPL 30
//#define MAXOFSPL 50
