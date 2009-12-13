
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

#if LCD_PROPERTY==LCD_GW_ZXW

// 十六进制转字符串
static const char hex2cha[] = {
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', 'A', 'b', 'C', 'd', 'E', 'F',
};



// 常量显示元素，仅仅显示，不需要闪烁。
void lcd_total (u8 flg) 
{ ///< 显示"总",
    if (flg == 0) 
    {
        return;
    }
    SetOnDevice_PUCK(S_ZONG);

}

void lcd_phase (u8 flg) 
{ ///< 显示"A/B/C/N相",
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
{ ///< 显示"电压",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_DIAN);
    SetOnDevice_PUCK(S_YA);

}

void lcd_current (u8 flg) 
{ ///< 显示"电流",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_DIAN);
    SetOnDevice_PUCK(S_LIU);

}

void lcd_positive (u8 flg) 
{ ///< 显示"正向",
    if (flg == 0) 
    {
        return;
    }
    
    SetOnDevice_PUCK(S_ZHENG);
    SetOnDevice_PUCK(S_XIANG);
}

void lcd_negative (u8 flg) 
{ ///< 显示"反向",
    if (flg == 0) {
        return;
    }

    SetOnDevice_PUCK(S_FAN);
    SetOnDevice_PUCK(S_XIANG);


}

void lcd_reactive (u8 flg) 
{ ///< 显示"无功",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_WU);
    SetOnDevice_PUCK(S_GONG);

}

void lcd_active (u8 flg) 
{ ///< 显示"有功",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_YOU);
    SetOnDevice_PUCK(S_GONG);

}

void lcd_power (u8 flg) { ///< 显示"功率",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_GONGLV);

}

void lcd_factor (u8 flg) { ///< 显示"因数",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_COS);
    SetOnDevice_PUCK(S_FAI);

}

void lcd_angle (u8 flg) { ///< "相角",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_FAI);
}

void lcd_energy (u8 flg) { ///< 显示"电量",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_DIAN);
    SetOnDevice_PUCK(S_LIANG);

}

void lcd_demand (u8 flg) { ///< 显示"需量",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_XU);
    SetOnDevice_PUCK(S_LIANG);

}

void lcd_time (u8 flg) { ///< 显示"时间",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_SHI);
    SetOnDevice_PUCK(S_JIAN);

}

void lcd_charge (u8 flg) { ///< 显示"电费",
    if (flg == 0) {
        return;
    }
    /*
    SetOnDevice_PUCK(S_DIAN);
    SetOnDevice_PUCK(S_FEI);
    */
}

void lcd_lostvolt  (u8 flg) { ///< "失压",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_SHI1);
    SetOnDevice_PUCK(S_YA);
}

void lcd_lostcurt  (u8 flg) { ///< "失流",
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_SHI1);
    SetOnDevice_PUCK(S_LIU);
}

void lcd_periods   (u8 flg) { ///< "时段"
    if (flg == 0) {
        return;
    }
    SetOnDevice_PUCK(S_SHI);
    SetOnDevice_PUCK(S_DUAN);
}

void lcd_feerate   (u8 flg) 
{ /*
  ///< "费率", 
    if (flg == 0) 
    {
        return;
    }
    SetOnDevice_PUCK(S_FEI);
    SetOnDevice_PUCK(S_LV);
  */
}

void lcd_thismonth (u8 flg) { ///< 显示"本月",
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
{ ///< mode4.bit5 ? "上月", "上上月" : "上1月", "上2月";
    if (flg == 0) 
    {
        return;
    }
    SetOnDevice_PUCK(S_SHANG);
    SetOnDevice_PUCK(S_YUE);
}

void lcd_lasttime (u8 flg) 
{ ///< mode4.bit5 ? "上月", "上上月" : "上1月", "上2月";
    if (flg == 0) 
    {
        return;
    }
    SetOnDevice_PUCK(S_SHANG);   
}

void lcd_times (u8 flg) 
{   
  if(flg == 0) 
    {
        return;
    }
  
  if (flg > 9) 
  {
      SetOnDevice_PUCK(S_SHIYUE);
  }
  SetOnLED8Device_PUCK(N_LED(1), '0' + (flg % 10));
}

void lcd_assemble (u8 flg) 
{
    static u8 stat;   
    
    if (flg > 0)  //无功组合模式字，闪烁
    {      
    }
    else                  //有功
    {
      //getdata(DI_CURRENT_QUADRANT, &stat, &stat, sizeof(stat));  //浪费时间      
      stat=Meter_Run_Status.NegCurr_Qudrant.Byte&0x0f;
      if(stat&0x0f EQ 0)   //1/2/4/8
        return ;
      /*{
        // 逆时针
        switch(stat&0x0f)   //长亮或者常灭
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

///< 显示"I象限",
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
{ ///< 显示"费率Tx",
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


void lcd_jieti(u8 flg)
{
  if (flg == 0) 
  {
      return;
  }
  
  SetOnDevice_PUCK(S_JIETI);
}

void lcd_dianjia(u8 flg)
{
  if (flg == 0) 
  {
      return;
  }  
  SetOnDevice_PUCK(S_DIAN);
  SetOnDevice_PUCK(S_JIA);
}

// 显示单位"kMVAWvarHhz",
const char* lcd_units (const char* s) 
{
    const char* p;
    
    p=strstr(s, "|kWh");
    if(p)
    {
      SetOnDevice_PUCK(S_KV);
      SetOnDevice_PUCK(S_VOLT_V);      
      SetOnDevice_PUCK(S_H);
      return (--p);
    }
    
    p=strstr(s, "|kW");
    if(p)
    {
      SetOnDevice_PUCK(S_KV);
      SetOnDevice_PUCK(S_VOLT_V);   
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
// 数据显示接口，采用字符串格式
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
    for (const char* p = lcd_units(s); p >= s   //显示分隔符|后面的单位。并获取分割符前面的位置--------PUCK
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
                  SetOnLED8Device_PUCK(addr[n++].id, *p);     //根据字符，点亮相应的LED---------PUCK
            }
        }
    }
}
//SetOnDevice_PUCK(S_FUHAO);   //复数显示
/********************************************************************************
PUCK: 输出显示代码的内容
函数功能：根据显示模式,及模式偏移，获取具体的显示元素等信息
入口：
     type-----模式参数;offs-----该模式下显示的项目顺序
返回：
********************************************************************************/
void lcd_code (code_t user, code_t code, curs_t curs,u8 SubCurs,u8 changeFlag,code_t changecode) 
{
    typedef struct {
        u16 id;
        u16 dp;
    } addr_t;

    static const addr_t addr[] = {
        {N_LED(99), D_(0)},  //空位：
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
     if(curs==MODE_A_B_BITS)  //不闪烁
      {
        if(n>MAXBITS)       //A/B模式，显示2位
          break;
        ch = hex2cha[code % 16];
        code /= 16;
      }
      else  //闪烁
      {
        if ((n == curs) && (n != 0) && (flag ^= 1)) //是光标所在位置，将显示代码点灭，下次再点亮，形成闪烁效果----------PUCK
        {
            ch = ' ';
            code /= 16;
        } 
        else if (code > 0)              //将显示代码点亮----------PUCK
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
    
    //数据标识间隔符
    SetOnDevice_D_PUCK(D_(10));
    SetOnDevice_D_PUCK(D_(11));
    SetOnDevice_D_PUCK(D_(12));
    
    if(dispmode EQ modeC)       //C模式下，显示子屏信息
    {       
        if(curs EQ MINBITS)    //当前位置是子屏，闪烁
        {
          if((flag ^= 1) EQ 0) //是光标所在位置，将显示代码点灭，下次再点亮，形成闪烁效果----------PUCK
          {
            SetOnLED8Device_PUCK(N_LED(18), hex2cha[SubCurs / 16]);
            SetOnLED8Device_PUCK(N_LED(19), hex2cha[SubCurs % 16]);
          }
        } 
        else                 //当前位置不是子屏，长亮
        {
            SetOnLED8Device_PUCK(N_LED(18), hex2cha[SubCurs / 16]);
            SetOnLED8Device_PUCK(N_LED(19), hex2cha[SubCurs % 16]);
        }
     }
    else      //AB模式下，显示屏号
    {       
        if(curs EQ MINBITS)    //当前位置是子屏，闪烁
        {
          if((flag ^= 1) EQ 0) //是光标所在位置，将显示代码点灭，下次再点亮，形成闪烁效果----------PUCK
          {
            SetOnLED8Device_PUCK(N_LED(18), hex2cha[user / 16]);
            SetOnLED8Device_PUCK(N_LED(19), hex2cha[user % 16]);
          }
        } 
        else                 //当前位置不是子屏，长亮
        {
            SetOnLED8Device_PUCK(N_LED(18), hex2cha[user / 16]);
            SetOnLED8Device_PUCK(N_LED(19), hex2cha[user % 16]);
        }
     }    
}

// 输出显示方案的内容
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

// 输出显示事件状态
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
      flag.bit1maps ^= stat.bit1maps;     //取反，形成闪烁效果------PUCK
      flag.bit2maps ^= stat.bit2maps;     //取反，形成闪烁效果------PUCK
  }
  
  //
  //电压无过压：正常状态(常亮)
  if(!stat.loss_volt_a &&!stat.cut_volt_a)                       //没失压，常亮
    SetOnDevice_PUCK(S_Ua);
  if(!stat.cut_volt_a && stat.loss_volt_a && !flag.loss_volt_a)  //不断相，失压，闪烁
    SetOnDevice_PUCK(S_Ua);
  
  if(!stat.loss_volt_b&&!stat.cut_volt_b)                       //没失压，常亮
    SetOnDevice_PUCK(S_Ub);
  if(!stat.cut_volt_b && stat.loss_volt_b && !flag.loss_volt_b)  //不断相，失压，闪烁
    SetOnDevice_PUCK(S_Ub);
  
  if(!stat.loss_volt_c&&!stat.cut_volt_c)                       //没失压，常亮
    SetOnDevice_PUCK(S_Uc);
  if(!stat.cut_volt_c && stat.loss_volt_c && !flag.loss_volt_c)  //不断相，失压，闪烁
    SetOnDevice_PUCK(S_Uc);

   //电流状态(常亮或者闪烁)
  if(!stat.loss_cur_a)//没有失流，常亮
      SetOnDevice_PUCK(S_Ia);
  if(stat.loss_cur_a && !flag.loss_cur_a && !poweroff())//失流，闪烁
      SetOnDevice_PUCK(S_Ia);
  
  if(!stat.loss_cur_b)//没有失流，常亮
      SetOnDevice_PUCK(S_Ib);
  if(stat.loss_cur_b && !flag.loss_cur_b && !poweroff())//失流，闪烁
      SetOnDevice_PUCK(S_Ib);
  
  if(!stat.loss_cur_c)//没有失流，常亮
      SetOnDevice_PUCK(S_Ic);
  if(stat.loss_cur_c && !flag.loss_cur_c && !poweroff())//失流，闪烁
      SetOnDevice_PUCK(S_Ic);
  
   
  //断流/电流反相
  if(stat.loss_cut_a)//断流，熄灭
    ClrOnDevice_PUCK(S_Ia);
  else
  {
    if(stat.cur_rers_a)  //A相反极性,且没有失流
      SetOnDevice_PUCK(S_Ia_);
  }
  
  if(stat.loss_cut_b)//断流，熄灭
    ClrOnDevice_PUCK(S_Ib);
  else
  {
    if(stat.cur_rers_b)  //B相反极性,且没有失流
      SetOnDevice_PUCK(S_Ib_);
  }
  
  if(stat.loss_cut_c)//断流，熄灭
    ClrOnDevice_PUCK(S_Ic);
  else
  {
    if(stat.cur_rers_c)  //C相反极性,且没有失流
      SetOnDevice_PUCK(S_Ic_);
  }    
    

  ///< 电池电压低(常亮)
  if (flag.cell_low1) 
  {  //时钟电池----闪烁
      SetOnDevice_PUCK(S_BAT1);
  }
  if (flag.cell_low2) 
  {  //低功耗电池----闪烁
      SetOnDevice_PUCK(S_BAT2);
  }
  if (flag.cell_low3) 
  {
      //SetOnDevice_PUCK(S_BAT3);
  }
  ///< 通信状态(RS1,RS2,红外)(常亮)
  if (stat.stat_communi &(1<<CHANEL_IRDA)) 
  {
      SetOnDevice_PUCK(S_HONGWAI);
  }
  
  if (stat.stat_communi &(1<<CHANEL_485_1)) 
  {
    SetOnDevice_PUCK(S_HONGWAI);  
    SetOnDevice_PUCK(S_RS1);
  }
  
  if (stat.stat_communi &(1<<CHANEL_485_2)) 
  {
    SetOnDevice_PUCK(S_HONGWAI);
    SetOnDevice_PUCK(S_RS2);
  }
  
#ifdef CHANEL_MOUDEL
  if (stat.stat_communi &(1<<CHANEL_MOUDEL)) 
  {
    /*
      SetOnDevice_PUCK(S_ARROW_LEFT);
      SetOnDevice_PUCK(S_ARROW_RIGHT);
    */
    SetOnDevice_PUCK(S_ZAIBO);
  }
#endif
  
  ///< 电压"逆相序"(闪烁)
  if (flag.volt_reverse) 
  {
      SetOnDevice_PUCK(S_NIXIANGXU);
  }
  
  ///< 电流"逆相序"(闪烁)
  if(flag.curr_reverse) 
  {
      SetOnDevice_PUCK(S_NIXIANGXU);
  }
    
  ///< 事件告警(闪烁)
  if (flag.event_warning & 0x01) {
      SetOnDevice_PUCK(S_LIGHT);
  }
  ///< 编程键打开(常亮)
  if (stat.switch_opened & 0x01) 
  {
      SetOnDevice_PUCK(S_BUTTON);
  }    
  //工厂模式(常亮)
  if (stat.fac_status & 0x01) {
      SetOnDevice_PUCK(S_HOUSE);
  }
  ///< 需量复位(常亮)
  /*
  if (stat.reset_demand & 0x01) 
  {
    SetOnDevice_PUCK(S_CHENGGONG);
      //SetOnDevice_PUCK(S_KEY);
  }    
  */  
  //跳线短接(闪烁)
  if (flag.jumper_short & 0x01) 
  {
      SetOnDevice_PUCK(S_HOUSE);
  }
  ///< 电表上锁(常亮)
  if (stat.meter_locked & 0x01) {
      SetOnDevice_PUCK(S_LOCK);
  }
  ///< 通讯模块在线指示(常亮)
  if (stat.status_online & 0x01) {
      SetOnDevice_PUCK(S_CIRCLE);
  }
  ///< 通讯模块信号强度指示
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


  
  ///< 显示当前费率，"尖, 峰, 平, 谷, T5, ...Tx",
  if(PREPAID_MONEY_MODE EQ PREPAID_RATE)    //0表示分时计费，1表示阶梯计费
  {
    switch (stat.status_tariff) 
    {
        case 0x01 : 
            SetOnDevice_PUCK(S_JIAN1);
            break;
    
        case 0x02 : 
            SetOnDevice_PUCK(S_FENG);
            break;
  
        case 0x03 : 
            SetOnDevice_PUCK(S_PING);
            break;
  
        case 0x04 : 
            SetOnDevice_PUCK(S_GU);
            break;
    }
    //显示主副时段1：主时段；2：副时段",
    if(0==stat.num_tariff)
      SetOnDevice_PUCK(S_S1);
    if(1==stat.num_tariff)
      SetOnDevice_PUCK(S_S2);  
  }
  
//--------------预付费功能未打开，以下不显示：显示保护-------------------------------------------- 
  if(PREPAID_EN EQ 0)  //无预付费功能，跳闸、跳闸 LED 指示、跳闸 LCD指示 均不点亮。
    return ;
  
  //拉闸
  if(stat.RelayOff)
    SetOnDevice_PUCK(S_LAZHA);
  
  
  if(PREPAID_MONEY_MODE EQ PREPAID_STEP)    //0表示分时计费，1表示阶梯计费
  {
    //指示当前使用第1、2套阶梯电价方案：1～2，对应 显示主副时段1：主时段；2：副时段",
    if(stat.SetpScheme EQ 1)
      SetOnDevice_PUCK(S_1);
    if(stat.SetpScheme EQ 1)
      SetOnDevice_PUCK(S_2);
    
    //指示当前运行第"1、2、3、4"阶梯电价 
    if(stat.SetpRate EQ 1)
      SetOnDevice_PUCK(S_S_1);
    if(stat.SetpRate EQ 2)
      SetOnDevice_PUCK(S_S_2);
    if(stat.SetpRate EQ 3)
      SetOnDevice_PUCK(S_S_3);
    if(stat.SetpRate EQ 4)
      SetOnDevice_PUCK(S_S_4);
  }
  
    if(flag.BuyFee)  //闪烁-------请购电 //本地费控，才显示与电费相关信息
      SetOnDevice_PUCK(S_QGD);
    
    if(stat.TouZhi)  //常亮---------透支
      SetOnDevice_PUCK(S_TOUZHI);  
}

/********************************************************************************
PUCK:显示预付费内容
函数功能：
入口：
返回：
********************************************************************************/
void  lcd_Pre_Pay    (u8 shenyu,u8 jine)              ///< 显示"预付费类容",
{
  
  if(shenyu)
    SetOnDevice_PUCK(S_SHENGYU);
  
  
  if(jine)
  {
    SetOnDevice_PUCK(S_DIAN);
    SetOnDevice_PUCK(S_FEI);
  }
}

/********************************************************************************
PUCK:后翻
函数功能：
入口：
返回：
********************************************************************************/
void dispnext (void) 
{
    if(dispmode!= modeC) //不是C模式，则光标不闪烁--------------PUCK
    {
      dispcursor = MODE_A_B_BITS;
      if(dispmode != modeB)
      {
        dispoffset=0;
        dispmode = modeB;   //键显模式
      }
      else
        dispoffset++;
      
      Refresh_Curr_Offset();
      lcdshow(dispmode, dispoffset);  //A/B模式下，获取显示代码------------PUCK        
    } 
    else  //C模式-----------PUCK
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
        display(dispmode, dispcode.code); //C模式下，根据显示代码来获取显示元素------------PUCK
    }
}

void dispback(void) 
{
    if (dispmode!= modeC) 
    {
      dispcursor = MODE_A_B_BITS;
      if(dispmode != modeB)
      {
        dispoffset=0;
        dispmode = modeB;   //键显模式
      }
      else
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
    if (dispcursor > MINBITS)  //光标右移，减1，因为显示是从右到左-------------PUCK
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
函数功能：主窗口显示
入口：    无
出口：    无
**********************************************************************************/
void Code_Dis_Info(char *Str)
{
  INT8U i,len;
  len=strlen(Str);
  len=(len>8)?8:len;

  for(i=0;i<len;i++)
      SetOnLED8Device_PUCK(N_LED(i+10),Str[i]);
}
/**********************************************************************************
函数功能：主窗口显示
入口：    无
出口：    无
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