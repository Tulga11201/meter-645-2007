#ifndef EXT_BASE_DIS_H
#define EXT_BASE_DIS_H



#ifndef EXT_BASE_DIS_C
#define EXT_BASE_DIS_PUCK  extern volatile
#else
#define EXT_BASE_DIS_PUCK  volatile
#endif


#define  DI_IS_ENERG(item)       (BYTE(item,3)==0)
#define  DI_IS_DEMAND(item)      (BYTE(item,3)==1)
#define  DI_IS_INSTANT(item)     (BYTE(item,3)==2)
#define  DI_IS_EVENT(item)       (BYTE(item,3)==3)
#define  DI_IS_PARA(item)        (BYTE(item,3)==4)

#define  DEFAULT_DIS_ENERG_BIT  3
#define  MAX_DIS_ENERG_BIT      4

#define  DEFAULT_DIS_POWER_BIT  4
#define  MAX_DIS_POWER_BIT      4

typedef struct {
    u32 low;
    u32 high;
    u32 higher;
} dval_t;




stat_t getstat (void);
void lcd_update (void);
//void lcd_data (item_t item, const char* s);
#endif