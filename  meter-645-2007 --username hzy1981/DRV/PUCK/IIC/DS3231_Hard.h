#ifndef HARD_DS3231_H
#define HARD_DS3231_H

//  osc =8(7.3728)
/*初始化时钟IIC的接口引脚*/
void init_DS3231(void);
/*
读ds3231时间，读出数组的值：{秒，分，时，星期，日，月，年}
*/


#endif