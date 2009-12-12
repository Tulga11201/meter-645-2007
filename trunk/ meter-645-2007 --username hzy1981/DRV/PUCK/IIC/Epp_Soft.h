#ifndef SOFT_I2C_CFG_H
#define SOFT_I2C_CFG_H


    
INT8U I2cSoft_Read_nByteS(INT8U Id,INT16U Len,INT8U *Dst);
INT8U  Write_Soft_EEPROM(INT8U VirtualID,INT8U SlvAdr,INT16U SubAddr,INT16U size,INT8U Type,INT8U *Src);
INT8U  Read_Soft_EEPROM(INT8U VirtualID,INT8U SlvAdr,INT16U SubAddr,INT8U Type,INT16U size,INT8U *Dst);    
#endif





