
/**
 * @file interface.c
 *     { comment block }
 * @brief
 *     { brief description @ref interface.cpp }
 * @author li.yao (nardoo@sohu.com)
 * @version v1.00
 * @date 05/29/2008 08:41
 * @note
 *     { paragraph where a note can be entered. }
 */

//#include <ctype.h>
//#include <string.h>

#include "Pub_PUCK.h"

#if LCD_PROPERTY==LCD_SD_ZXW

// ʮ������ת�ַ���
static const char hex2cha[] = {
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', 'A', 'b', 'C', 'd', 'E', 'F',
};



// ������ʾԪ�أ�������ʾ������Ҫ��˸��
void lcd_total (u8 flg) 
{ ///< ��ʾ"��",
    if (flg == 0) 
    {
        return;
    }
    SetOnDevice_PUCK(S_ZONG);

}

void lcd_phase (u8 flg) 
{ ///< ��ʾ"A/B/C/N��",
    if (flg EQ 0x01) {
        SetOnDevice_PUCK(S_A);
        return ;
    }
    if (flg EQ 0x02) 
    {
        SetOnDevice_PUCK(S_B);
         return ;
    }
    if (flg EQ 0x03) 
    {
        SetOnDevice_PUCK(S_C);
         return ;
    }
    if (flg EQ 0x04) 
    {
        SetOnDevice_PUCK(S_N);
         return ;
    }
}

void lcd_voltage (u8 flg) 
{ ///< ��ʾ"��ѹ",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_DIAN);
    SetOnDevice_PUCK(S_YA);

}

void lcd_current (u8 flg) 
{ ///< ��ʾ"����",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_DIAN);
    SetOnDevice_PUCK(S_LIU);

}

void lcd_positive (u8 flg) 
{ ///< ��ʾ"����",
    if (flg == 0) 
    {
        return;
    }
    
    SetOnDevice_PUCK(S_ZHENG);
    SetOnDevice_PUCK(S_XIANG);
}

void lcd_negative (u8 flg) 
{ ///< ��ʾ"����",
    if (flg == 0) {
        return;
    }

    SetOnDevice_PUCK(S_FAN);
    SetOnDevice_PUCK(S_XIANG);


}

void lcd_reactive (u8 flg) 
{ ///< ��ʾ"�޹�",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_WU);
    SetOnDevice_PUCK(S_GONG);

}

void lcd_active (u8 flg) 
{ ///< ��ʾ"�й�",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_YOU);
    SetOnDevice_PUCK(S_GONG);

}

void lcd_power (u8 flg) { ///< ��ʾ"����",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_GONGLV);

}

void lcd_factor (u8 flg) { ///< ��ʾ"����",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_COS);
    SetOnDevice_PUCK(S_FAI);

}

void lcd_angle (u8 flg) { ///< "���",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_FAI);
}

void lcd_energy (u8 flg) { ///< ��ʾ"����",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_DIAN);
    SetOnDevice_PUCK(S_LIANG);

}

void lcd_demand (u8 flg) { ///< ��ʾ"����",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_XU);
    SetOnDevice_PUCK(S_LIANG);

}

void lcd_time (u8 flg) { ///< ��ʾ"ʱ��",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_SHI);
    SetOnDevice_PUCK(S_JIAN);

}

void lcd_charge (u8 flg) { ///< ��ʾ"���",
    if (flg == 0) {
        return;
    }
    /*
    SetOnDevice_PUCK(S_DIAN);
    SetOnDevice_PUCK(S_FEI);
    */
}

void lcd_lostvolt  (u8 flg) { ///< "ʧѹ",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_SHI1);
    SetOnDevice_PUCK(S_YA);
}

void lcd_lostcurt  (u8 flg) { ///< "ʧ��",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_SHI1);
    SetOnDevice_PUCK(S_LIU);
}

void lcd_periods   (u8 flg) { ///< "ʱ��"
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_SHI);
    SetOnDevice_PUCK(S_DUAN);
}

void lcd_feerate   (u8 flg) 
{ /*
  ///< "����", 
    if (flg == 0) 
    {
        return;
    }
    SetOnDevice_PUCK(S_FEI);
    SetOnDevice_PUCK(S_LV);
  */
}

void lcd_thismonth (u8 flg) { ///< ��ʾ"����",
    if (flg == 0) {
        return;
    }
     /*
    SetOnDevice_PUCK(S_BEN);
    SetOnDevice_PUCK(S_YUE);
    */
    SetOnDevice_PUCK(S_DANGQIAN);

}

void lcd_lastmonth (u8 flg) 
{ ///< mode4.bit5 ? "����", "������" : "��1��", "��2��";
    if (flg == 0) 
    {
        return;
    }
    SetOnDevice_PUCK(S_SHANG);
    if (flg > 9) 
    {
        SetOnDevice_PUCK(S_SHIYUE);
    }
    SetOnLED8Device_PUCK(N_LED(1), '0' + (flg % 10));
    SetOnDevice_PUCK(S_YUE);
}


void lcd_assemble (u8 flg) 
{
    static u8 stat;   
    
    if (flg > 0)  //�޹����ģʽ�֣���˸
    {      
    }
    else                  //�й�
    {
      //getdata(DI_CURRENT_QUADRANT, &stat, &stat, sizeof(stat));  //�˷�ʱ��      
      stat=Meter_Run_Status.NegCurr_Qudrant.Byte&0x0f;
      if(stat&0x0f EQ 0)   //1/2/4/8
        return ;
      /*{
        // ��ʱ��
        switch(stat&0x0f)   //�������߳���
        {
          case 1:
            stat=14;
            break;
          case 2:
            stat=7;
            break;
          case 4:
            stat=11;
            break;
          case 8:
            stat=13;
            break;   
        default:
          return;
       }
      }
      else
        return ;*/
    }
    if (stat & 0x01) 
    {
      SetOnDevice_PUCK(S_P_Q);
      SetOnDevice_PUCK(S_XIANGXIAN1);
    }
    if (stat & 0x02) 
    {
      SetOnDevice_PUCK(S_P_Q);
      SetOnDevice_PUCK(S_XIANGXIAN2);
    }
    if (stat & 0x04) 
    {
      SetOnDevice_PUCK(S_P_Q);
      SetOnDevice_PUCK(S_XIANGXIAN3);
    }
    if (stat & 0x08) 
    {
      SetOnDevice_PUCK(S_P_Q);
      SetOnDevice_PUCK(S_XIANGXIAN4);
    }
}

///< ��ʾ"I����",
void lcd_quadrant (u8 flg) 
{ 
    switch (flg) 
    {
        case QUADRANT4 : 
           SetOnDevice_PUCK(S_I1);
           SetOnDevice_PUCK(S_V);
           break;
        case QUADRANT3 : 
           SetOnDevice_PUCK(S_I1);
           SetOnDevice_PUCK(S_I2);
           break;
        case QUADRANT2 : 
           SetOnDevice_PUCK(S_I2);
           break;
        case QUADRANT1 :
           SetOnDevice_PUCK(S_I1);
           break;
    }
}

void lcd_tariff (u8 flg) 
{ ///< ��ʾ"����Tx",
    if (flg == 0) 
    {
        return;
    }
    switch(flg)
    {
      case 1:
        SetOnDevice_PUCK(S_JIAN2);
        break;
      case 2:
        SetOnDevice_PUCK(S_FENG2);
        break;
      case 3:
        SetOnDevice_PUCK(S_PING2);
        break;
      case 4:
        SetOnDevice_PUCK(S_GU2);
        break;
    }
  
}

void lcd_times (u8 flg) 
{ ///< ��ʾ"��XX��",
    if (flg == 0) 
    {
        return;
    }
    SetOnDevice_PUCK(S_SHANG);
    if (flg > 9) 
    {
        SetOnDevice_PUCK(S_SHIYUE);
    }
    SetOnLED8Device_PUCK(N_LED(1), '0' + (flg % 10));
    //SetOnDevice_PUCK(S_CI);
}




// ��ʾ��λ"kMVAWvarHhz",
const char* lcd_units (const char* s) 
{
    const char* p;
    
    p=strstr(s, "|kWh");
    if(p)
    {
      SetOnDevice_PUCK(S_KW);
      SetOnDevice_PUCK(S_H);
      return (--p);
    }
    
    p=strstr(s, "|kW");
    if(p)
    {
      SetOnDevice_PUCK(S_KW);
      return (--p);
    }
    
    
    p=strstr(s, "|kvarh");
    if(p)
    {
      SetOnDevice_PUCK(S_KVAR);
      SetOnDevice_PUCK(S_h);
      return (--p);
    } 
    
    p=strstr(s, "|kvar");
    if(p)
    {
      SetOnDevice_PUCK(S_KVAR);
      return (--p);
    } 
    
        
    p=strstr(s, "|V");
    if(p)
    {
      SetOnDevice_PUCK(S_VOLT_V);
      return (--p);
    }
    
    p=strstr(s, "|A");
    if(p)
    {
      SetOnDevice_PUCK(S_CURR_A);
      return (--p);
    }
    
    p=strstr(s, "|yuan");
    if(p)
    {
      SetOnDevice_PUCK(S_YUAN);
      return (--p);
    }
    
    
    p=strstr(s, "|");
    if(p)
    {
      return (--p);
    }
    
    return s;
       
/*    
    for (p = s + strlen(s); p >= s; --p) {
        switch (*p) 
        {
            case '2': {
                break;
            }
            case 'k': {
                SetOnDevice_PUCK(S_M_55);
                SetOnDevice_PUCK(S_M_56);
                break;
            }
            case 'M': {
                SetOnDevice_PUCK(S_M_55);
                SetOnDevice_PUCK(S_M_57);
                break;
            }
            case 'V': {
                SetOnDevice_PUCK(S_M_58);
                break;
            }
            case 'A': {
                SetOnDevice_PUCK(S_M_61);
                SetOnDevice_PUCK(S_M_62);
                SetOnDevice_PUCK(S_M_63);
                SetOnDevice_PUCK(S_M_64);
                break;
            }
            case 'W': {
                SetOnDevice_PUCK(S_M_58);
                SetOnDevice_PUCK(S_M_59);
                SetOnDevice_PUCK(S_M_60);
                SetOnDevice_PUCK(S_M_61);
                SetOnDevice_PUCK(S_M_62);
                break;
            }
            case 'H': {
                SetOnDevice_PUCK(S_M_67);
                SetOnDevice_PUCK(S_M_68);
                break;
            }
            case 'h': {
                SetOnDevice_PUCK(S_M_67);
                 break;
            }
            case 'z': {
                SetOnDevice_PUCK(S_M_69);
                break;
            }
            case 'v': {
                SetOnDevice_PUCK(S_M_60);
                SetOnDevice_PUCK(S_M_62);
                break;
            }
            case 'a': {
                SetOnDevice_PUCK(S_M_64);
                SetOnDevice_PUCK(S_M_65);
                break;
            }
            case 'r': {
                SetOnDevice_PUCK(S_M_66);
                break;
            }
            case 'o': {
                SetOnDevice_PUCK(S_DU);
                break;
            }
            case '|': {
                return (--p);
            }
        }
    }
 */

}

//#pragma optimize = none
// ������ʾ�ӿڣ������ַ�����ʽ
void lcd_value (const char* s) {
    typedef struct {
        u16 id;
        u16 dp1;
        u16 dp2;
    } addr_t;

    static const addr_t addr[] = {
        {N_LED( 9), D_( 0), D_( 0)}, {N_LED( 8), D_( 9), D_( 0)}, {N_LED( 7), D_( 8), D_( 7)},
        {N_LED( 6), D_( 6), D_( 0)}, {N_LED( 5), D_( 5), D_( 4)}, {N_LED( 4), D_( 0), D_( 0)},
        {N_LED( 3), D_( 2), D_( 0)}, {N_LED( 2), D_( 1), D_( 0)}
    };
    s16 n = 0;
    for (const char* p = lcd_units(s); p >= s   //��ʾ�ָ���|����ĵ�λ������ȡ�ָ��ǰ���λ��--------PUCK
        && (n < sizeof(addr) / sizeof(addr_t)); --p) {
        switch (*p) {
            case '?': {
                break;
            }
            case ' ': {
                n++;
                break;
            }
            case '.': {
                SetOnDevice_D_PUCK(addr[n].dp1);
                break;
            }
            case ':': {
                SetOnDevice_D_PUCK(addr[n].dp1);
                SetOnDevice_D_PUCK(addr[n].dp2);
                break;
            }
            default: 
              {
                if((n EQ  sizeof(addr) / sizeof(addr_t)-1)&&(*p EQ '-'))
                    SetOnDevice_PUCK(S_FUHAO);
                else
                  SetOnLED8Device_PUCK(addr[n++].id, *p);     //�����ַ���������Ӧ��LED---------PUCK
            }
        }
    }
}
//SetOnDevice_PUCK(S_FUHAO);   //������ʾ
/********************************************************************************
PUCK: �����ʾ���������
�������ܣ�������ʾģʽ,��ģʽƫ�ƣ���ȡ�������ʾԪ�ص���Ϣ
��ڣ�
     type-----ģʽ����;offs-----��ģʽ����ʾ����Ŀ˳��
���أ�
********************************************************************************/
void lcd_code (code_t user, code_t code, curs_t curs,u8 SubCurs,u8 changeFlag,code_t changecode) 
{
    typedef struct {
        u16 id;
        u16 dp;
    } addr_t;

    static const addr_t addr[] = {
        {N_LED(99), D_(0)},  //��λ��
        {N_LED(17), D_(0)}, 
        {N_LED(16), D_(0)}, 
        {N_LED(15), D_(12)}, 
        {N_LED(14), D_(0)},
        {N_LED(13), D_(11)}, 
        {N_LED(12), D_(0)}, 
        {N_LED(11), D_(10)}, 
        {N_LED(10), D_(0)}        
    };
    
   char ch = ' ';
    static u8 flag = 0;
    curs_t n = 1;
    
    if(changeFlag)
      code=changecode;
   
    for (; n < sizeof(addr) / sizeof(addr_t); ++n) 
    {
     if(curs==MODE_A_B_BITS)  //����˸
      {
        if(n>MAXBITS)       //A/Bģʽ����ʾ2λ
          break;
        ch = hex2cha[code % 16];
        code /= 16;
      }
      else  //��˸
      {
        if ((n == curs) && (n != 0) && (flag ^= 1)) //�ǹ������λ�ã�����ʾ��������´��ٵ������γ���˸Ч��----------PUCK
        {
            ch = ' ';
            code /= 16;
        } 
        else if (code > 0)              //����ʾ�������----------PUCK
        {
            ch = hex2cha[code % 16];
            code /= 16;
        } else 
        {
            ch = '0';
        }
      }
      SetOnLED8Device_PUCK(addr[n].id, ch);
    }
    /*
    if(Sub_Vlist.exist EQ MULIT_EXSIT && dispmode != modeC)
    {
      SetOnDevice_D_PUCK(D_(20));
      SetOnLED8Device_PUCK(N_LED(21), SubCurs+'0');
    }
    */
    
    //���ݱ�ʶ�����
    SetOnDevice_D_PUCK(D_(10));
    SetOnDevice_D_PUCK(D_(11));
    SetOnDevice_D_PUCK(D_(12));
    
    if(dispmode EQ modeC)       //Cģʽ�£���ʾ������Ϣ
    {       
        if(curs EQ MINBITS)    //��ǰλ������������˸
        {
          if((flag ^= 1) EQ 0) //�ǹ������λ�ã�����ʾ��������´��ٵ������γ���˸Ч��----------PUCK
          {
            SetOnLED8Device_PUCK(N_LED(18), hex2cha[SubCurs / 16]);
            SetOnLED8Device_PUCK(N_LED(19), hex2cha[SubCurs % 16]);
          }
        } 
        else                 //��ǰλ�ò�������������
        {
            SetOnLED8Device_PUCK(N_LED(18), hex2cha[SubCurs / 16]);
            SetOnLED8Device_PUCK(N_LED(19), hex2cha[SubCurs % 16]);
        }
     }
    else      //ABģʽ�£���ʾ����
    {       
        if(curs EQ MINBITS)    //��ǰλ������������˸
        {
          if((flag ^= 1) EQ 0) //�ǹ������λ�ã�����ʾ��������´��ٵ������γ���˸Ч��----------PUCK
          {
            SetOnLED8Device_PUCK(N_LED(18), hex2cha[user / 16]);
            SetOnLED8Device_PUCK(N_LED(19), hex2cha[user % 16]);
          }
        } 
        else                 //��ǰλ�ò�������������
        {
            SetOnLED8Device_PUCK(N_LED(18), hex2cha[user / 16]);
            SetOnLED8Device_PUCK(N_LED(19), hex2cha[user % 16]);
        }
     }    
}

// �����ʾ����������
void lcd_mode (u8 type) 
{
    switch (type) 
    {
        case modeA: 
          {
            //SetOnDevice_PUCK(S_S1_);
            break;
        }
        case modeB: 
          {
            //SetOnDevice_PUCK(S_S2);
            break;
        }
        default : 
          {
            //SetOnDevice_PUCK(S_1C1);
            break;
        }
    }
}

// �����ʾ�¼�״̬
void lcd_events (void) 
{
  static stat_t flag;
  static u8 num=0;
  
  stat_t stat = getstat();
    
  flag.bit1maps &= stat.bit1maps;
  flag.bit2maps &= stat.bit2maps;
  num++;
 
  if(num>=SECOND_2(1))
  {
      num=0;
      flag.bit1maps ^= stat.bit1maps;     //ȡ�����γ���˸Ч��------PUCK
      flag.bit2maps ^= stat.bit2maps;     //ȡ�����γ���˸Ч��------PUCK
  }
  
  //��ѹ�޹�ѹ������״̬(����)
  if(!stat.loss_volt_a &&!stat.cut_volt_a)                       //ûʧѹ������
    SetOnDevice_PUCK(S_Ua);
  if(!stat.cut_volt_a && stat.loss_volt_a && !flag.loss_volt_a)  //�����࣬ʧѹ����˸
    SetOnDevice_PUCK(S_Ua);
  
  if(!stat.loss_volt_b&&!stat.cut_volt_b)                       //ûʧѹ������
    SetOnDevice_PUCK(S_Ub);
  if(!stat.cut_volt_b && stat.loss_volt_b && !flag.loss_volt_b)  //�����࣬ʧѹ����˸
    SetOnDevice_PUCK(S_Ub);
  
  if(!stat.loss_volt_c&&!stat.cut_volt_c)                       //ûʧѹ������
    SetOnDevice_PUCK(S_Uc);
  if(!stat.cut_volt_c && stat.loss_volt_c && !flag.loss_volt_c)  //�����࣬ʧѹ����˸
    SetOnDevice_PUCK(S_Uc);

   //����״̬(����������˸)
  if(!stat.loss_cur_a)//û��ʧ��������
      SetOnDevice_PUCK(S_Ia);
  if(stat.loss_cur_a && !flag.loss_cur_a && !poweroff())//ʧ������˸
      SetOnDevice_PUCK(S_Ia);
  
  if(!stat.loss_cur_b)//û��ʧ��������
      SetOnDevice_PUCK(S_Ib);
  if(stat.loss_cur_b && !flag.loss_cur_b && !poweroff())//ʧ������˸
      SetOnDevice_PUCK(S_Ib);
  
  if(!stat.loss_cur_c)//û��ʧ��������
      SetOnDevice_PUCK(S_Ic);
  if(stat.loss_cur_c && !flag.loss_cur_c && !poweroff())//ʧ������˸
      SetOnDevice_PUCK(S_Ic);
  
   
  //����/��������
  if(stat.loss_cut_a)//������Ϩ��
    ClrOnDevice_PUCK(S_Ia);
  else
  {
    if(stat.cur_rers_a)  //A�෴����,��û��ʧ��
      SetOnDevice_PUCK(S_Ia_);
  }
  
  if(stat.loss_cut_b)//������Ϩ��
    ClrOnDevice_PUCK(S_Ib);
  else
  {
    if(stat.cur_rers_b)  //B�෴����,��û��ʧ��
      SetOnDevice_PUCK(S_Ib_);
  }
  
  if(stat.loss_cut_c)//������Ϩ��
    ClrOnDevice_PUCK(S_Ic);
  else
  {
    if(stat.cur_rers_c)  //C�෴����,��û��ʧ��
      SetOnDevice_PUCK(S_Ic_);
  }    
    

  ///< ��ص�ѹ��(����)
  if (flag.cell_low1) 
  {  //ʱ�ӵ��----��˸
      SetOnDevice_PUCK(S_BAT1);
  }
  if (flag.cell_low2) 
  {  //�͹��ĵ��----��˸
      SetOnDevice_PUCK(S_BAT2);
  }
  if (flag.cell_low3) 
  {
      //SetOnDevice_PUCK(S_BAT3);
  }
  ///< ͨ��״̬(RS1,RS2,����)(����)
  if (stat.stat_communi &(1<<CHANEL_IRDA)) 
  {
      SetOnDevice_PUCK(S_HONGWAI);
  }
  
  if (stat.stat_communi &(1<<CHANEL_485_1)) 
  {
    SetOnDevice_PUCK(S_RS);  
    SetOnDevice_PUCK(S_RS1);
  }
  
  if (stat.stat_communi &(1<<CHANEL_485_2)) 
  {
    SetOnDevice_PUCK(S_RS);
    SetOnDevice_PUCK(S_RS2);
  }
  
#ifdef CHANEL_MOUDEL
  if (stat.stat_communi &(1<<CHANEL_MOUDEL)) 
  {
    /*
      SetOnDevice_PUCK(S_ARROW_LEFT);
      SetOnDevice_PUCK(S_ARROW_RIGHT);
    */
    SetOnDevice_PUCK(S_RS);
  }
#endif
  
  ///< ��ѹ"������"(��˸)
  if (flag.volt_reverse) 
  {
      SetOnDevice_PUCK(S_NIXIANGXU);
  }
  
  ///< ����"������"(��˸)
  if(flag.curr_reverse) 
  {
      SetOnDevice_PUCK(S_NIXIANGXU);
  }
    
  ///< �¼��澯(��˸)
  if (flag.event_warning & 0x01) {
      SetOnDevice_PUCK(S_LIGHT);
  }
  ///< ��̼���(����)
  if (stat.switch_opened & 0x01) 
  {
      SetOnDevice_PUCK(S_BUTTON);
  }    
  //����ģʽ(����)
  if (stat.fac_status & 0x01) {
      SetOnDevice_PUCK(S_HOUSE);
  }
  ///< ������λ(����)
  /*
  if (stat.reset_demand & 0x01) 
  {
    SetOnDevice_PUCK(S_CHENGGONG);
      //SetOnDevice_PUCK(S_KEY);
  }    
  */    
    
  //���߶̽�(��˸)
  if (flag.jumper_short & 0x01) 
  {
      SetOnDevice_PUCK(S_HOUSE);
  }
  ///< �������(����)
  if (stat.meter_locked & 0x01) {
      SetOnDevice_PUCK(S_LOCK);
  }
  ///< ͨѶģ������ָʾ(����)
  if (stat.status_online & 0x01) {
      SetOnDevice_PUCK(S_CIRCLE);
  }
  ///< ͨѶģ���ź�ǿ��ָʾ
  switch (stat.signal_scale) 
  {
    case 0x00 :
          break;
    case 0x01 :
          SetOnDevice_PUCK(S_CSQ1);
          break;
    case 0x02 :
          SetOnDevice_PUCK(S_CSQ2);
          SetOnDevice_PUCK(S_CSQ1);
          break;
    case 0x03 :
          SetOnDevice_PUCK(S_CSQ3);
          SetOnDevice_PUCK(S_CSQ2);
          SetOnDevice_PUCK(S_CSQ1);
          break;      
    default:
          SetOnDevice_PUCK(S_CSQ4);
          SetOnDevice_PUCK(S_CSQ3);
          SetOnDevice_PUCK(S_CSQ2);
          SetOnDevice_PUCK(S_CSQ1);
         break;
  }
  ///< ��ʾ��ǰ���ʣ�"��, ��, ƽ, ��, T5, ...Tx",
  switch (stat.status_tariff) 
  {
      case 0x00 : {
          break;
      }
      case 0x01 : {
          SetOnDevice_PUCK(S_JIAN1);
          break;
      }
      case 0x02 : {
          SetOnDevice_PUCK(S_FENG);
          break;
      }
      case 0x03 : {
          SetOnDevice_PUCK(S_PING);
          break;
      }
      case 0x04 : {
          SetOnDevice_PUCK(S_GU);
          break;
      }
      default : 
      {
        /*
          SetOnDevice_PUCK(S_TT);
          SetOnLED8Device_PUCK(N_LED(13), '0'+stat.status_tariff);
        */
          break;
      }
  }
  
  ///��ʾ����ʱ��1����ʱ�Σ�2����ʱ��",
  if(0==stat.num_tariff)
    SetOnDevice_PUCK(S_S1);
  if(1==stat.num_tariff)
    SetOnDevice_PUCK(S_S2);

  
    
  //���ñ���ַ��ť����ʾ���߿�̽�
  //if(Read_Event_Status(ID_METER_ADDR_EN))
  //  SetOnDevice_PUCK(S_SHOT);
  
  //if (flag.CalMeter & 0x01)   //����δУ������˸С����
  //  SetOnDevice_PUCK(S_CIRCLE);
  
//--------------Ԥ���ѹ���δ�򿪣����²���ʾ����ʾ����-------------------------------------------- 
  //��բ
  if(Get_Switch_Status() EQ SWITCH_OFF) 
    SetOnDevice_PUCK(S_LAZHA);
  
  if(PREPAID_EN EQ 0)  //��Ԥ���ѹ��ܣ���բ����բ LED ָʾ����բ LCDָʾ ����������
    return ;

  //��۷�����1��2
  if(stat.SetpScheme EQ 1)
    SetOnDevice_PUCK(S_1);
  if(stat.SetpScheme EQ 1)
    SetOnDevice_PUCK(S_2);
  
  //��ۣ�1��4 
  if(stat.SetpRate EQ 1)
    SetOnDevice_PUCK(S_S_1);
  if(stat.SetpRate EQ 2)
    SetOnDevice_PUCK(S_S_2);
  if(stat.SetpRate EQ 3)
    SetOnDevice_PUCK(S_S_3);
  if(stat.SetpRate EQ 4)
    SetOnDevice_PUCK(S_S_4);
  

  
  

}

/********************************************************************************
PUCK:��ʾԤ��������
�������ܣ�
��ڣ�
���أ�
********************************************************************************/
void  lcd_Pre_Pay    (u8 shenyu,u8 jine)              ///< ��ʾ"Ԥ��������",
{
  
  if(shenyu)
    SetOnDevice_PUCK(S_SHENGYU);
  
  //if(jine)  //���
  //  SetOnDevice_PUCK(S_JIING_E);  
  
  if(jieti)  //����
    SetOnDevice_PUCK(S_JIETI);   
  
  if(dianjia) //���
  {
    SetOnDevice_PUCK(S_DIAN);  
    SetOnDevice_PUCK(S_JIA);  
  }
}

/********************************************************************************
PUCK:��
�������ܣ�
��ڣ�
���أ�
********************************************************************************/
void dispnext (void) 
{
    if(dispmode!= modeC) //����Cģʽ�����겻��˸--------------PUCK
    {
        dispcursor = MODE_A_B_BITS;
        dispoffset++;
        Refresh_Curr_Offset();
        lcdshow(dispmode, dispoffset);  //A/Bģʽ�£���ȡ��ʾ����------------PUCK        
    } 
    else  //Cģʽ-----------PUCK
    {
        switch (dispcursor) 
        {
            case 0x0 :
                SET_HIGH_CODE_BIT;
                Judge_Modi_Sub_Screen(dispcode.code,PROC_ADD);
                break;                
            case 0x1 :
                ++dispcode.bit0;
                dispcode.bit0 %= 0x10;
                break;
            case 0x2 :
                ++dispcode.bit1;
                dispcode.bit1 %= 0x10;
                break;
            case 0x3 :
                ++dispcode.bit2;
                dispcode.bit2 %= 0x10;
                break;
            case 0x4 :
                ++dispcode.bit3;
                dispcode.bit3 %= 0x10;
                break;
            case 0x5 :
                ++dispcode.bit4;
                dispcode.bit4 %= 0x10;
                break;
            case 0x6 :
                ++dispcode.bit5;
                dispcode.bit5 %= 0x10;
                break;
            case 0x7 :
                ++dispcode.bit6;
                dispcode.bit6 %= 0x10;
                break;
            case 0x8 :
                ++dispcode.bit7;
                dispcode.bit7 %= 0x10;
                break;  
        }
        SET_HIGH_CODE_BIT;
        Judge_Modi_Sub_Screen(dispcode.code,PROC_NONE);        
        display(dispmode, dispcode.code); //Cģʽ�£�������ʾ��������ȡ��ʾԪ��------------PUCK
    }
}

void dispback(void) 
{
    if (dispmode!= modeC) 
    {
        dispcursor = MODE_A_B_BITS;
        dispoffset--;
        Refresh_Curr_Offset();
        lcdshow(dispmode, dispoffset);        
    } 
    else 
    {
        switch (dispcursor)
        {
            case 0x0 :    
                SET_HIGH_CODE_BIT;
                Judge_Modi_Sub_Screen(dispcode.code,PROC_SUB);
                break;
            case 0x1 :
              
                if (--dispcode.bit0 > 0x10) 
                {
                    dispcode.bit0 = 0x0f;
                }
                break;
            case 0x2 :
                if (--dispcode.bit1 > 0x10) 
                {
                    dispcode.bit1 = 0x0f;
                }
                break;
            case 0x3 :
                if (--dispcode.bit2 > 0x10) 
                {
                    dispcode.bit2 = 0x0f;
                }
                break;
            case 0x4 :
                if (--dispcode.bit3 > 0x10) 
                {
                    dispcode.bit3 = 0x0f;
                }
                break;
            case 0x5 :
                if (--dispcode.bit4 > 0x10) 
                {
                    dispcode.bit4 = 0x0f;
                }
                break;
            case 0x6 :
                if (--dispcode.bit5 > 0x10) 
                {
                    dispcode.bit5 = 0x0f;
                }
                break;
            case 0x7 :
                if (--dispcode.bit6 > 0x10)
                {
                    dispcode.bit6 = 0x0f;
                }
                break;
            case 0x8 :
                if (--dispcode.bit7 > 0x10)
                {
                    dispcode.bit7 = 0x0f;
                }
        }
        SET_HIGH_CODE_BIT;
        Judge_Modi_Sub_Screen(dispcode.code,PROC_NONE);        
        display(dispmode, dispcode.code);
    }
}


void Set_C_Mode_DisCode(INT8U dval) 
{
  if(dispmode!=modeC)
    return ;
  
  if (dispcursor == MODE_A_B_BITS) 
  {
        dispcursor = MAXBITS;
  }
  switch (dispcursor) 
  {
      case 0x0 :
          Sub_Vlist.subindex=dval;
          SET_HIGH_CODE_BIT;
          Judge_Modi_Sub_Screen(dispcode.code,PROC_NONE);
          break;
          
      case 0x1 :
          dispcode.bit0 = dval;
          break;
      case 0x2 :
          dispcode.bit1 = dval;
          break;
      case 0x3 :
          dispcode.bit2 = dval;
          break;
      case 0x4 :
          dispcode.bit3 = dval;
          break;
      case 0x5 :
          dispcode.bit4 = dval;
          break;
      case 0x6 :
          dispcode.bit5 = dval;
          break;
      case 0x7 :
          dispcode.bit6 = dval;
          break;
      case 0x8 :
          dispcode.bit7 = dval;
          break;    
    }
    SET_HIGH_CODE_BIT;
    Judge_Modi_Sub_Screen(dispcode.code,PROC_NONE);
    display(dispmode, dispcode.code);
    if (dispcursor > MINBITS)  //������ƣ���1����Ϊ��ʾ�Ǵ��ҵ���-------------PUCK
    {
        --dispcursor;
    } 
    else 
    {
        dispcursor =MAXBITS;
    }    
    screen(dispmode, dispcursor);
}
/**********************************************************************************
�������ܣ���������ʾ
��ڣ�    ��
���ڣ�    ��
**********************************************************************************/
void Code_Dis_Info(char *Str)
{
  INT8U i,len;
  len=strlen(Str);
  len=(len>8)?8:len;

  for(i=0;i<len;i++)
      SetOnLED8Device_PUCK(N_LED(i+14),Str[i]);
}
/**********************************************************************************
�������ܣ���������ʾ
��ڣ�    ��
���ڣ�    ��
**********************************************************************************/
void Main_Dis_Info(char *Str)
{
  INT8U i,len;
  len=strlen(Str);
  len=(len>10)?10:len;

  for(i=2;i<=len+1;i++)
      SetOnLED8Device_PUCK(N_LED(i),Str[i-2]);
 
   UpdataLcdShow();
}
#endif