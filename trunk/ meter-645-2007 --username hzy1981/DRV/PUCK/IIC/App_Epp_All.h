


#define DIS_ALL_HARD_I2C_WP       IIC_HARD_WP_DIS            //�ر�����Ӳ��I2C��WP

#define DIS_ALL_SOFT_I2C_WP                  //�ر��������I2C��WP



#define Get_Modi_Value(PageNo) (INT8U)(PageNo<<1)
//U10:��ַ��ͻ��Ŀǰ����û��ʵ��
INT8U Write_EEPROM_Dvice_PUCK(INT8U Mem_ID,INT16U SubAdr,INT16U size,INT8U *src);
INT8U Read_EEPROM_Dvice_PUCK(INT8U Mem_ID,INT16U SubAdr,INT16U size,INT8U *src);