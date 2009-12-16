#define EVENT_PROTO_C
#include "Includes.h"

INT16U Event_Sub_Item_Len0[]={5,2,4,4, 4,4                                                                                                                            };//0--电量型购电   23    
INT16U Event_Sub_Item_Len1[]={5,2,4,4, 4,4                                                                                                                            };//1--电费型购电   23
INT16U Event_Sub_Item_Len2[]={6,6                                                                                                                                     };//2--最近1次失压发生时间记录  12
INT16U Event_Sub_Item_Len3[]={6,4,4,4, 4,4,4,4   ,4,2,3,3, 3,2,4,4    ,4,4,2,3, 3,3,2,4     ,4,4,4,2, 3,3,3,2    ,4,4,4,4, 6,4,4,4    ,4,4,4,4, 4,4,4,4    ,4,4,4,4,4 };//3--失压、欠压、过压 断相 195 
INT16U Event_Sub_Item_Len4[]={6,4,4,4, 4,4,4,4   ,4,4,4,4, 4,4,4,4    ,4,6,4,4, 4,4,4,4     ,4,4,4,4, 4,4,4,4    ,4,4 };//4--电压逆相序、电流逆相序     潮流反向    过载  140
INT16U Event_Sub_Item_Len5[]={6,4,4,4, 4,4,4,4   ,4,4,4,4, 4,4,4,4    ,4,3,6,4, 4,4,4,4     ,4,4,4,4, 4,4,4,4    ,4,4,4                                               };//5电压不平衡  143
INT16U Event_Sub_Item_Len6[]={6,4,4,4, 4,4,4,4   ,4,2,3,3, 3,2,4,4    ,4,4,2,3, 3,3,2,4     ,4,4,4,2, 3,3,3,2    ,6,4,4,4, 4,4,4,4    ,4,4,4,4, 4,4,4,4    ,4         };//6相失流、过流、断流  179
INT16U Event_Sub_Item_Len7[]={6,4,4,4, 4,4,4,4                                                                                                                        };//7跳闸  34
INT16U Event_Sub_Item_Len8[]={6,4,4,4, 4,4,4,4                                                                                                                        };//8合闸   34 
INT16U Event_Sub_Item_Len9[]={6,4,4,4, 4,6,4,4    ,4,4                                                                                                                };//9--  总功率因数超下限 44                             
//以下为旧的645协议：      
INT16U Event_Sub_Item_Len10[]={6+3+6                                                               };//10--全失压  030500
INT16U Event_Sub_Item_Len11[]={6+6                                                                 };//11--辅助电源失电、电池欠压  //               0x030600    0X0E1400                                                                                           
INT16U Event_Sub_Item_Len12[]={6+6+3+5};//12--正向有功需量超限//--反向有功需量超限 //第一象限无功需量超限//第二象限无功需量超限//第三象限无功需量超限 //第四象限无功需量超限0x031201 0x031202 0x031204 0x031203 0x031205 0x031206
INT16U Event_Sub_Item_Len13[]={6+4+40                                                              };//13--编程记录  0X033000
INT16U Event_Sub_Item_Len14[]={6+4+4+4+ 4+4+4+4   +4+4+4+4+ 4+4+4+4    +4+4+4+4+ 4+4+4+4     +4+4  };//14--电表清 0   0x033001
INT16U Event_Sub_Item_Len15[]={8+8+8+8+ 8+8+8+8   +8+8+8+8+ 8+8+8+8    +8+8+8+8+ 8+8+8+8     +8+8  }; //15--需量清0  0x033002   前面两个8+8  应改为6+4
INT16U Event_Sub_Item_Len16[]={6+4+4                                                               }; //16--事件清0     0x033003
INT16U Event_Sub_Item_Len17[]={4+6+6                                                               };//17--校时         0x033004
INT16U Event_Sub_Item_Len18[]={6+4+42+42+ 42+42+42+42   +42+42+42+42+ 42+42+42+42    +42+42        };//18--时段表编程  0x033005
INT16U Event_Sub_Item_Len19[]={6+4+42+42                                                           }; //19--时区表编程     0x033006            
INT16U Event_Sub_Item_Len20[]={6+4+(MAX_YEAR_HOLIDAYS*4)                                           };//20--节假日编程0x033008       
INT16U Event_Sub_Item_Len21[]={6+4+1  };//21--有功组合方式//--无功组合方式1//--无功组合方式2//--周休日编程 //0x033009  0x03300A    0x03300B      0x033007      
INT16U Event_Sub_Item_Len22[]={6+4+2+2+ 2                                                          };//22--结算日编程   0x03300C                        
INT16U Event_Sub_Item_Len23[]={6+6+4+4+ 4+4+4+4   +4+4+4+4 +4+4                                    };//23--开表盖、开端钮  0x03300D    0x03300E 
INT16U Event_Sub_Item_Len24[]={6+6+3+3                                                             };//24--超需量报警//这一项 没有在数组Event_ID_Info  中调用
INT16U Event_Sub_Item_Len25[]={6+3+3                                                               };//25--超需量跳闸  这一项 没有在数组Event_ID_Info  中调用
INT16U Event_Sub_Item_Len26[]={12                                                                  };//26--掉电 //0x031100
INT16U Event_Sub_Item_Len27[]={6+4+4+4+ 4+4+4+4 +4                                                 };//27--远程拉闸  合闸//0X0E1D00  0X0E1E00 
INT16U Event_Sub_Item_Len28[]={5+5+1                                                               };//28--上电时钟乱和运行时钟乱  校表 0X0E1C00      0X0E3010 
INT16U Event_Sub_Item_Len29[]={6                                                                   };//29--复位    0X0E1800
INT16U Event_Sub_Item_Len30[]={5+1                                                                 };//30错 Eeprom次数  0X0E1A00
INT16U Event_Sub_Item_Len31[]={5+36+36+1                                                           }; //31--设置初始电量   0X0E3011
INT16U Event_Sub_Item_Len32[]={6+6+2+4+ 4+4+4+4     +4+4+4+4 +4+4+4+4+     4+4+4                   };//32--电流不平衡 030A00
INT16U Event_Sub_Item_Len33[]={3+3+3+3+ 3+2+4+2+ 4}; //33本月）电压合格率统计数据031000 A相电压合格率统计数据031001 B相电压合格率统计数据031002 C相电压合格率统计数据031003
INT16U Event_Sub_Item_Len34[]={6+6                                                                 };//34时钟电池欠压  0X0E1500  
INT16U Event_Sub_Item_Len35[]={6+6+3+3                                                             };//35负控报警   0X0E1600 
INT16U Event_Sub_Item_Len36[]={6+3+3                                                               };//36负控跳闸记录  0X0E1700     
INT16U Event_Sub_Item_Len37[]={5+4*(MAX_RATES+1)+4*(MAX_RATES+1)+4*(MAX_RATES+1)+4*(MAX_RATES+1)+4*(MAX_RATES+1)+4*(MAX_RATES+1)+4*(MAX_RATES+1) +4*(MAX_RATES+1)+ 8*(MAX_RATES+1)+8*(MAX_RATES+1)+12+12 };//26--冻结数据、时区表切换、时段表切换        ?? 

 //以下内容除最后一个外 其余为老的645协议中定义的或自己定义的事件
CONST S_Event_PDI_Info_Quck Event_PDI_Info[]=
{                                     
 {0x03320100, &Event_Sub_Item_Len0[0],S_NUM(Event_Sub_Item_Len0)},//0--电量型购电   23
 {0x03330100, &Event_Sub_Item_Len1[0],S_NUM(Event_Sub_Item_Len1)}, //1--电费型购电   23
 {0x10000100, &Event_Sub_Item_Len2[0],S_NUM(Event_Sub_Item_Len2)}, //最近1次失压发生时间记录 12
 {0x10010100, &Event_Sub_Item_Len3[0],S_NUM(Event_Sub_Item_Len3)},//a--失压 195
 {0x10020100, &Event_Sub_Item_Len3[0],S_NUM(Event_Sub_Item_Len3)},//b--失压 195
 {0x10030100, &Event_Sub_Item_Len3[0],S_NUM(Event_Sub_Item_Len3)},//c--失压 195
 {0x11010100, &Event_Sub_Item_Len3[0],S_NUM(Event_Sub_Item_Len3)},//a--欠压、 195
 {0x11020100, &Event_Sub_Item_Len3[0],S_NUM(Event_Sub_Item_Len3)},//b--欠压、 195
 {0x11030100, &Event_Sub_Item_Len3[0],S_NUM(Event_Sub_Item_Len3)}, //c--欠压、 195
 {0x12010100, &Event_Sub_Item_Len3[0],S_NUM(Event_Sub_Item_Len3)},//a相过压  195
 {0x12020100, &Event_Sub_Item_Len3[0],S_NUM(Event_Sub_Item_Len3)},//b相过压  195
 {0x12030100, &Event_Sub_Item_Len3[0],S_NUM(Event_Sub_Item_Len3)},//c相过压   195
 {0x13010100, &Event_Sub_Item_Len3[0],S_NUM(Event_Sub_Item_Len3)},//a断相 195
 {0x13020100, &Event_Sub_Item_Len3[0],S_NUM(Event_Sub_Item_Len3)}, //b断相 195
 {0x13030100, &Event_Sub_Item_Len3[0],S_NUM(Event_Sub_Item_Len3)}, //c-断相 195
 {0x14000100, &Event_Sub_Item_Len4[0],S_NUM(Event_Sub_Item_Len4)}, //电压逆相序、  140  
 {0x15000100, &Event_Sub_Item_Len4[0],S_NUM(Event_Sub_Item_Len4)}, //电流逆相序     140
 {0x1B010100, &Event_Sub_Item_Len4[0],S_NUM(Event_Sub_Item_Len4)}, // a潮流反向      140
 {0x1B020100, &Event_Sub_Item_Len4[0],S_NUM(Event_Sub_Item_Len4)}, // b  潮流反向   140
 {0x1B030100, &Event_Sub_Item_Len4[0],S_NUM(Event_Sub_Item_Len4)}, //  c潮流反向      140
 {0x1C010100, &Event_Sub_Item_Len4[0],S_NUM(Event_Sub_Item_Len4)}, //a 过载  140
 {0x1C020100, &Event_Sub_Item_Len4[0],S_NUM(Event_Sub_Item_Len4)}, //b  过载  140
 {0x1C030100, &Event_Sub_Item_Len4[0],S_NUM(Event_Sub_Item_Len4)}, //c 过载 140  
 {0x16000100, &Event_Sub_Item_Len5[0],S_NUM(Event_Sub_Item_Len5)}, //电压不平衡 142
 {0x17000100, &Event_Sub_Item_Len5[0],S_NUM(Event_Sub_Item_Len5)}, //电流不平衡 142 
 {0x18010100, &Event_Sub_Item_Len6[0],S_NUM(Event_Sub_Item_Len6)},//a失流、 179
 {0x19010100, &Event_Sub_Item_Len6[0],S_NUM(Event_Sub_Item_Len6)},//a过流、 179
 {0x1A010100, &Event_Sub_Item_Len6[0],S_NUM(Event_Sub_Item_Len6)},//a断流  179
 {0x18020100, &Event_Sub_Item_Len6[0],S_NUM(Event_Sub_Item_Len6)},//b失流179
 {0x19020100, &Event_Sub_Item_Len6[0],S_NUM(Event_Sub_Item_Len6)},//b过流179
 {0x1A020100, &Event_Sub_Item_Len6[0],S_NUM(Event_Sub_Item_Len6)},//b断流  179
 {0x18030100, &Event_Sub_Item_Len6[0],S_NUM(Event_Sub_Item_Len6)},//c失流、  179
 {0x19030100, &Event_Sub_Item_Len6[0],S_NUM(Event_Sub_Item_Len6)},//c过流、179
 {0x1A030100, &Event_Sub_Item_Len6[0],S_NUM(Event_Sub_Item_Len6)},//c断流  179
 {0x1D000100, &Event_Sub_Item_Len7[0],S_NUM(Event_Sub_Item_Len7)},//跳闸 34
 {0x1E000100, &Event_Sub_Item_Len8[0],S_NUM(Event_Sub_Item_Len8)},//合闸 34
 {0x1F000100, &Event_Sub_Item_Len9[0],S_NUM(Event_Sub_Item_Len9)},//总功率因数超下限  44
 //以下内容除最后一个外 其余为老的645协议中定义的或自己定义的事件
 {0x03050000,&Event_Sub_Item_Len10[0],S_NUM(Event_Sub_Item_Len10)},//1--全失压   
 {0x03060000,&Event_Sub_Item_Len11[0],S_NUM(Event_Sub_Item_Len11)},//4--辅助电源失电、
 {0x0E140000,&Event_Sub_Item_Len11[0],S_NUM(Event_Sub_Item_Len11)},//电池欠压                                                                                                    
 {0x03120100,&Event_Sub_Item_Len12[0],S_NUM(Event_Sub_Item_Len12)},//5--正向有功需量超限  
 {0x03120200,&Event_Sub_Item_Len12[0],S_NUM(Event_Sub_Item_Len12)},//6--反向有功需量超限
 {0x03120300,&Event_Sub_Item_Len12[0],S_NUM(Event_Sub_Item_Len12)},//9--第一象限无功需量超限
 {0x03120400,&Event_Sub_Item_Len12[0],S_NUM(Event_Sub_Item_Len12)},///10--第二象限无功需量超限
 {0x03120500,&Event_Sub_Item_Len12[0],S_NUM(Event_Sub_Item_Len12)},//11--第三象限无功需量超限
 {0x03120600,&Event_Sub_Item_Len12[0],S_NUM(Event_Sub_Item_Len12)},//8-- 第四象限无功需量超限 
 {0x03300000,&Event_Sub_Item_Len13[0],S_NUM(Event_Sub_Item_Len13)},//12--编程记录
 {0x03300100,&Event_Sub_Item_Len14[0],S_NUM(Event_Sub_Item_Len14)},//13--电表清0   
 {0x03300200,&Event_Sub_Item_Len15[0],S_NUM(Event_Sub_Item_Len15)}, //14--需量清0  
 {0x03300300,&Event_Sub_Item_Len16[0],S_NUM(Event_Sub_Item_Len16)}, //15--事件清0     
 {0x03300400,&Event_Sub_Item_Len17[0],S_NUM(Event_Sub_Item_Len17)},//16--校时         
 {0x03300500,&Event_Sub_Item_Len18[0],S_NUM(Event_Sub_Item_Len18)},//17--时段表编程  
 {0x03300600,&Event_Sub_Item_Len19[0],S_NUM(Event_Sub_Item_Len19)}, //18--时区表编程                 
 {0x03300800,&Event_Sub_Item_Len20[0],S_NUM(Event_Sub_Item_Len20)},//20--节假日编程
 {0x03300900,&Event_Sub_Item_Len21[0],S_NUM(Event_Sub_Item_Len21)},//21--有功组合方式
 {0x03300A00,&Event_Sub_Item_Len21[0],S_NUM(Event_Sub_Item_Len21)},//22--无功组合方式1
 {0x03300B00,&Event_Sub_Item_Len21[0],S_NUM(Event_Sub_Item_Len21)},//23--无功组合方式2
 {0x03300700,&Event_Sub_Item_Len21[0],S_NUM(Event_Sub_Item_Len21)},//19--周休日编程
 {0x03300C00,&Event_Sub_Item_Len22[0],S_NUM(Event_Sub_Item_Len22)},//24--结算日编程    
 {0x03300D00,&Event_Sub_Item_Len23[0],S_NUM(Event_Sub_Item_Len23)}, //25--、开表盖
 {0x03300E00,&Event_Sub_Item_Len23[0],S_NUM(Event_Sub_Item_Len23)}, //25--、开端钮  
 {0x03110000,&Event_Sub_Item_Len26[0],S_NUM(Event_Sub_Item_Len26)},//29--掉电 //
 {0x0E1D0000,&Event_Sub_Item_Len27[0],S_NUM(Event_Sub_Item_Len27)},//30--远程拉闸  
 {0x0E1E0000,&Event_Sub_Item_Len27[0],S_NUM(Event_Sub_Item_Len27)},//合闸
 {0x0E1C0000,&Event_Sub_Item_Len28[0],S_NUM(Event_Sub_Item_Len28)},//31--上电时钟乱
 {0x0E301000,&Event_Sub_Item_Len28[0],S_NUM(Event_Sub_Item_Len28)},//校表
 {0x0E180000,&Event_Sub_Item_Len29[0],S_NUM(Event_Sub_Item_Len29)},//32--复位    
 {0x0E1A0000,&Event_Sub_Item_Len30[0],S_NUM(Event_Sub_Item_Len30)},// Eeprom错次数  
 {0x0E301100,&Event_Sub_Item_Len31[0],S_NUM(Event_Sub_Item_Len31)}, //34--设置初始电量   
 {0x030A0000,&Event_Sub_Item_Len32[0],S_NUM(Event_Sub_Item_Len32)},//38--电流不平衡 
 {0x03100000,&Event_Sub_Item_Len33[0],S_NUM(Event_Sub_Item_Len33)}, //本月）电压合格率统计数据
 {0x03100100,&Event_Sub_Item_Len33[0],S_NUM(Event_Sub_Item_Len33)}, //本月）A相电压合格率统计数据
 {0x03100200,&Event_Sub_Item_Len33[0],S_NUM(Event_Sub_Item_Len33)}, //本月）B相电压合格率统计数据
 {0x03100300,&Event_Sub_Item_Len33[0],S_NUM(Event_Sub_Item_Len33)}, //本月）C相电压合格率统计数据
 {0x0E150000,&Event_Sub_Item_Len34[0],S_NUM(Event_Sub_Item_Len34)},//时钟电池欠压    
 {0x0E160000,&Event_Sub_Item_Len35[0],S_NUM(Event_Sub_Item_Len35)},//负控报警    
 {0x0E170000,&Event_Sub_Item_Len36[0],S_NUM(Event_Sub_Item_Len36)},//负控跳闸记录   
 //{0x05000000,&Event_Sub_Item_Len37[0],S_NUM(Event_Sub_Item_Len37)}
 {(0x05000000) | ((PROTO_DI)PERIOD_FREEZE_TYPE << 16), (INT16U *)Zero, 0x11},
 {(0x05000000) | ((PROTO_DI)INSTANT_FREEZE_TYPE << 16), (INT16U *)Zero, 0x11},
 {(0x05000000) | ((PROTO_DI)YEAR_SWITCH_FREEZE_TYPE << 16), (INT16U *)Zero, 0x11},
 {(0x05000000) | ((PROTO_DI)DATE_SWITCH_FREEZE_TYPE << 16), (INT16U *)Zero, 0x11},
 {(0x05000000) | ((PROTO_DI)HOUR_FREEZE_TYPE << 16), (INT16U *)Zero, 0x11},
 {(0x05000000) | ((PROTO_DI)RATE_SWITCH_FREEZE_TYPE << 16), (INT16U *)Zero,0x11},
 {(0x05000000) | ((PROTO_DI)DATE_FREEZE_TYPE << 16), (INT16U *)Zero,0x11},
 {(0x05000000) | ((PROTO_DI)STEP_SWITCH_FREEZE_TYPE << 16), (INT16U *)Zero,0x11}, 
 //{(0x05000000) | ((PROTO_DI)ENG_OVERTURN_FREEZE_TYPE << 16), Zero, ENG_OVERTURN_FREEZE_NUM}, 
 
};


INT16U Get_Event_Items_Len(CONST INT16U *pSub_Len, INT8U Num)
{
  INT8U i;
  INT16U Len = 0;
  
  for(i = 0; i < Num; i ++)
  {
    Len += *(pSub_Len + i);    
  }
  
  return Len;
}
/*
PROTO_DI Get_Event_Separate_DI(PROTO_DI PDI)
{
  for(i = 0; i <S_NUM(Event_PDI_Info); i ++)
  {
    if((PDI & 0xFFFF0000) EQ (Event_PDI_Info[i].PDI & 0xFFFF0000)) //协议标识和事件协议标识前2字节相同
    {
      Index0 = ((Event_PDI_Info[i].PDI >> 8) & 0xFF);
      Index1 = ((PDI >> 8) & 0xFF);
      
      if(Index1 EQ 0xFF) //需要读取的是整个事件数据项目
      {
        //mem_cpy(pDst, pSrc, SrcLen, pDst_Start, DstLen);
        return Event_PDI_Info[i].PDI;        
      }
      
      if(Index1 >= Index0 && Index1 < Index0 + (Event_PDI_Info[i].Num))
      {
        return Event_PDI_Info[i].PDI;
      }
    }
  }
  
  return NULL_4BYTES;
}
*/

INT16U Get_Event_Separate_Sub_Item_Data(PROTO_DI PDI, INT8U *pSrc, INT16U SrcLen, INT8U *pDst, INT8U *pDst_Start, INT16U DstLen)
{
  INT16U i, j, Len;
  INT16U Off;
  INT8U Index0;
  INT8U Index1;
  
  Off = 0;
  for(i = 0; i <S_NUM(Event_PDI_Info); i ++)
  {
    if((PDI & 0xFFFF0000) EQ (Event_PDI_Info[i].PDI & 0xFFFF0000)) //协议标识和事件协议标识前2字节相同
    {
      Index0 = ((Event_PDI_Info[i].PDI >> 8) & 0xFF);
      Index1 = ((PDI >> 8) & 0xFF);
      
      if(Index1 EQ 0xFF) //需要读取的是整个事件数据项目
      {
        mem_cpy(pDst, pSrc, SrcLen, pDst_Start, DstLen);
        return SrcLen;        
      }
      
      if(Index1 >= Index0 && Index1 < Index0 + (Event_PDI_Info[i].Num))
      {
        Len = Get_Event_Items_Len(Event_PDI_Info[i].pSub_Len, Event_PDI_Info[i].Num);
        if(Len != SrcLen)
        {
          ASSERT_FAILED();
          Debug_Print("Event_Sub_Lens error, PDI EQ %lx", PDI);
        }
        
        for(j = Index0; j < Index1; j ++)
          Off += *(Event_PDI_Info[i].pSub_Len + j - Index0);

        mem_cpy(pDst, pSrc + Off, *(Event_PDI_Info[i].pSub_Len + Index1 - Index0), pDst_Start, DstLen);
        return *(Event_PDI_Info[i].pSub_Len + Index1 - Index0);
      }
    }
  }
  
  ASSERT_FAILED();
  return 0;  
}
           
//读取比较大的事件数据，不能再一帧内传送完成的话，需要拆帧
INT16U Get_Spec_Event_Sparate_Proto_Data(STORA_DI SDI, INT8U *pDst, INT8U *pDst_Start, INT16U DstLen, INT8U *pFlag)
{
  static S_Int16U Off = {CHK_BYTE, 1, CHK_BYTE};//事件的第一个字节为发生结束标志，不需要读取，因此首偏移为1
  static STORA_DI SDI_Bak;
  INT16U RD_Len, Len;
  
  *pFlag = 0; //不是特殊数据项
  if((SDI & 0x1FFFFF00) EQ 0x03300500 && (SDI & 0xFF) > 0)
  {
    *pFlag = 1;
    
    Frame_Ack_Info.Follow_Flag = 0;//初始化为没有后续数据
    
    if(Frame_Ack_Info.Read_Follow_Flag EQ 0)
    {
      Off.Var = 1;
      SDI_Bak = SDI;
    }
    else
    {
      if(SDI_Bak != SDI)
        return 0;
    }
    
    OS_Mutex_Pend(PUB_BUF0_SEM_ID);
    Len = Read_Storage_Data(SDI, (INT8U *)Pub_Buf0, (INT8U *)Pub_Buf0, sizeof(Pub_Buf0));
    OS_Mutex_Post(PUB_BUF0_SEM_ID);
    
    if(Len EQ 0 || Off.Var >= Len)//Off.Var表示当次应该读取的偏移
      return 0;
    
    if(Off.Var EQ 1)
      RD_Len = 178;
    else
      RD_Len = (Len - Off.Var) < 168? (Len - Off.Var):168;

    mem_cpy(pDst, (INT8U *)Pub_Buf0 + Off.Var, RD_Len, pDst_Start, DstLen);
    Off.Var += RD_Len;
    
    if(Len > Off.Var)
      Frame_Ack_Info.Follow_Flag = 1;//有后续数据
    else
      Frame_Ack_Info.Follow_Flag = 0;
      
    return RD_Len;
  }

  return 0;  
}

//获取某个PDI对应的事件的协议的第一个PDI
PROTO_DI Get_Event_Separate_Start_PDI(PROTO_DI PDI)
{
  INT16U i;
  
  for(i = 0; i < S_NUM(Event_PDI_Info); i ++)
  {
    if((PDI & 0xFFFF0000) EQ (Event_PDI_Info[i].PDI & 0xFFFF0000) &&\
       (PDI & 0x0000FF00) >= (Event_PDI_Info[i].PDI & 0x0000FF00) &&\
       (((PDI & 0x0000FF00) < (Event_PDI_Info[i].PDI & 0x0000FF00) + ((INT32U)Event_PDI_Info[i].Num << 8)) ||\
        ((PDI & 0x0000FF00) EQ 0x0000FF00)))
      return Event_PDI_Info[i].PDI;
  }  
  
  return NULL_4BYTES;
}

//读取事件记录数据项
//DI表示事件记录的标识码
//pDst表示目标缓冲区
//pDst_Start表示目标缓冲区的起始
//DstLen和pDst_Start一起限定pDst和返回长度
//pErr表示返回为0时对应的原因，如果是NO_ERR表示该DI不是一个事件DI
//返回值为读到的报警数据长度
INT16U _Get_Event_Separate_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen, INT8U *pSpec_Flag)
{
  //INT8U Spec_Flag;
  INT16U i, Len;
  STORA_DI SDI;
  PROTO_DI TempPDI;
  INT8U Event_Flag, j;
  INT16U Index;

  TRACE();
  
  *pSpec_Flag = 0;
  
  if(!(pDst >= pDst_Start && pDst < pDst_Start + DstLen))
  {
    ASSERT_FAILED();
    return 0;
  }
  
  //获得事件的第一个DI
  TempPDI = Get_Event_Separate_Start_PDI(PDI);
  
  //if((PDI & 0x0000FF00) > 0) 
    //PDI = ((PDI & 0xFFFF00FF) | 0x00000100); //转化为该事件的第一个数据项,第三个字节如果为0，仍然是0，如果>1转为1
  if(TempPDI != NULL_4BYTES)
    PDI = ((TempPDI & 0xFFFFFF00) | (PDI & 0xFF));
  else
    ASSERT_FAILED();
  
  //获取数据的Index
  i = Get_Event_Separate_Proto_Index(PDI);
  if(NULL_2BYTES EQ i)
  {
    ASSERT_FAILED();
    return 0;
  }
  
  Debug_Print("Get_Event_Proto_Data, Event_ID : %d", Event_Separate_Data_Info[i].Event_ID);
  if((PDI & 0xFFFFFF00) EQ 0x03300000)
  {
    if(Prog_Record.Prog_Flag.All_Flag != 0)//当前处于一个编程周期内,正在编程
    {    
      if(PDI EQ 0x03300001)//最近一条编程记录需要特殊处理，因为此时可能处于一个编程周期中
      {
         mem_cpy(pDst, (INT8U *)Prog_Record.Time, 6, pDst_Start, DstLen);
         mem_cpy(pDst + 6, (INT8U *)Prog_Record.Op_ID, 4, pDst_Start, DstLen);
         mem_cpy(pDst + 10,(INT8U *) Prog_Record.PDI, 40, pDst_Start, DstLen);
         return 50;
      }
      else
      {
        PDI = PDI - 0x01;        
      }
    }
  }

  if(Event_Separate_Data_Info[i].Storage_Num EQ 0)//ONE_RECORD_EVENT)
  {
    return 0;  
  }
  
  if(Event_Separate_Data_Info[i].Storage_Num EQ 1)//ONE_RECORD_EVENT)
  {
    return Read_Storage_Data(Event_Separate_Data_Info[i].SDI, pDst, pDst_Start, DstLen);
  }
  else
  {
    //读取最后一条事件，且事件在发生，且是差量类型事件，则需要虚拟一次事件的恢复
    if(Event_Separate_Data_Info[i].SDI EQ ES_DI(PDI) && \
       Check_Event_Occuring(Event_Separate_Data_Info[i].Event_ID) && \
       memcmp((Event_Separate_Data_Info[i].pData) -> Diff_Mask, (INT8U *) Zero, sizeof((Event_Separate_Data_Info[i].pData) -> Diff_Mask)) != 0)//当前事件在发生,需要虚拟一次事件结束
    {
      Len = Event_Separate_Proc(Event_Separate_Data_Info[i].Event_ID, EVENT_END, EVENT_VIRTRUAL);
      if(Len > 1)
        Len --;
      mem_cpy(pDst, (INT8U *)Pub_Buf0 + 1, Len, pDst_Start, DstLen);

      return Len;
    }

    //先读出最近一次事件的存储DI到SDI
    Len = Read_Storage_Data(Event_Separate_Data_Info[i].Last_SDI, &SDI, &SDI, sizeof(SDI));
    if(Len != sizeof(STORA_DI)) //没有读取到上次发生事件的记录
    {
      ASSERT_FAILED();
      return 0;
    }

    //SDI认为是最后一次存储数据的DI
    if(!(SDI >= Event_Separate_Data_Info[i].SDI && \
  SDI < Event_Separate_Data_Info[i].SDI + Event_Separate_Data_Info[i].Storage_Num))
    {
      if(SDI EQ NULL_EVENT_STORA_DI)//事件还没有发生则返回全0数据
      {
        //有可能需要拆帧处理
        Len = Get_Spec_Event_Sparate_Proto_Data(Event_Separate_Data_Info[i].SDI, pDst, pDst_Start, DstLen, pSpec_Flag);
        if(*pSpec_Flag EQ 1)
          return Len;
    
        Len = Get_Storage_Data_Len(Event_Separate_Data_Info[i].SDI);
        if(Len > 1) 
          Len --;
        mem_set(pDst, 0, Len, pDst_Start, DstLen);
        return Len;
      }
      else
        return 0;
    }
    
    PDI = ES_DI(PDI);//协议DI转化为存储DI

    //DI转换成最近第几次的事件数据?
    //Proto_DI是最近一次的DI
    if(PDI >= Event_Separate_Data_Info[i].SDI && PDI < Event_Separate_Data_Info[i].SDI + Event_Separate_Data_Info[i].Storage_Num)
      PDI = PDI - Event_Separate_Data_Info[i].SDI;
    else
      return 0;

    if((SDI - PDI) < Event_Separate_Data_Info[i].SDI)
      SDI = Event_Separate_Data_Info[i].Storage_Num + SDI - PDI;
    else
      SDI = SDI - PDI;

    //需要拆帧的特殊数据项目，例如日时段表编程
    Len = Get_Spec_Event_Sparate_Proto_Data(SDI, pDst, pDst_Start, DstLen, pSpec_Flag);
    if(*pSpec_Flag EQ 1)
      return Len;
    
    //OS_Mutex_Pend(PUB_BUF0_SEM_ID);
    Len = Read_Storage_Data(SDI, pDst, pDst_Start, DstLen);
    if(Len EQ 0)//读出正确数据
      return 0;

    Len --;
    Event_Flag = *pDst;//事件发生或者结束标志
    mem_cpy(pDst, pDst + 1, Len, pDst_Start, DstLen);//去掉第一个字节的事件发生或者结束标志

    if(memcmp((Event_Separate_Data_Info[i].pData) -> Diff_Mask, (INT8U *) Zero, sizeof((Event_Separate_Data_Info[i].pData) -> Diff_Mask)) != 0\
       && Event_Flag != EVENT_END)//差量事件，但是没有结束事件,应该将差量数据清0
    {
      Debug_Print("Read Event Data, Event_Flag=0x%x!=EVENT_END", Event_Flag);
      ASSERT_FAILED();
      Len = 0;
      for(j = 0; j < Event_Separate_Data_Info[i].pData -> Data_Num; j ++)
      {
        Index = Get_P_Data_Index(Event_Separate_Data_Info[i].pData -> PDI[j]);
        if(Index EQ NULL_2BYTES)
        {
          ASSERT_FAILED();
          return 0;
        }
        //Debug_Print("Event %d, DataLen=%d", i, P_Data_Info[Index].Dst_Len);
        if(Get_Array_Bit((INT8U *) (Event_Separate_Data_Info[i].pData -> Diff_Mask), j))//第i个数据是差量数据，则清零之
          mem_set(pDst + Len, 0, P_Data_Info[Index].Dst_Len, pDst_Start, DstLen); 
        
        Len += P_Data_Info[Index].Dst_Len; 

        if(P_Data_Info[Index].Dst_Len EQ 0)
          ASSERT_FAILED();
      }
    }
  }
  
  //此处已经获得了整个事件的数据，下面的函数截取事件的分项数据
  //Len = Get_Event_Separate_Sub_Item_Data(PDI, pDst, Len, pDst, pDst_Start, DstLen);
  return Len;
}

INT16U Get_Event_Separate_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{ 
  INT16U Len;
  INT8U Spec_Flag;
  
  Len = _Get_Event_Separate_Proto_Data(PDI, pDst, pDst_Start, DstLen, &Spec_Flag);
  if(Spec_Flag EQ 0) //Spec_Flag == 1表示是需要拆帧的数据，在_Get_Event_Separate_Proto_Data函数内部处理了,可以直接返回数据
  {
    if(Len > 0)
      Len = Get_Event_Separate_Sub_Item_Data(PDI, pDst, Len, pDst, pDst_Start, DstLen);
  }

  return Len;
}

//获取事件累计的协议数据
INT16U _Get_Event_Cumu_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  INT16U Index, Len;
  INT32U Counts, Mins;

  TRACE();
  if(!(pDst >= pDst_Start && pDst <= pDst_Start + DstLen))
  {
    ASSERT_FAILED();
    return 0;
  }

  Index = Get_Event_Cumu_Proto_Index(PDI);
  if(Index EQ NULL_2BYTES)
  {
    ASSERT_FAILED();
    return 0;
  }

  Len = 0;
  if(Check_Cumu_Event_Occuring(Event_Cumu_Data_Info[Index].Event_ID))//当前事件在发生?
  {
    //OS_Mutex_Pend(PUB_BUF0_SEM_ID);
    Len = Event_Cumu_Proc(Event_Cumu_Data_Info[Index].Event_ID, EVENT_END, EVENT_VIRTRUAL);//虚拟一次事件结束,将当前累加数据存储到了Pub_Buf0中 
  }
  else
  {
    OS_Mutex_Pend(PUB_BUF0_SEM_ID);    
    Len = Read_Storage_Data(Event_Cumu_Data_Info[Index].Total_Stora_DI, (INT8U *)Pub_Buf0, (INT8U *)Pub_Buf0, sizeof(Pub_Buf0) / 2);
    OS_Mutex_Post(PUB_BUF0_SEM_ID);
  }
  
  if(Len > 0)
  {
    OS_Mutex_Pend(PUB_BUF0_SEM_ID);
    Len = 0;

    Counts = 0;
    Mins = 0;
    mem_cpy(&Counts, (INT8U *)Pub_Buf0 + 5, 4, &Counts, sizeof(Counts));
    mem_cpy(&Mins, (INT8U *)Pub_Buf0 + 9, 4, &Mins, sizeof(Mins));

    Hex2Bcd(Counts, pDst, 3, pDst_Start, DstLen);
    Hex2Bcd(Mins, pDst + 3, 4, pDst_Start, DstLen);
    Len += 7;

    Len += Convert_Src_2_Proto_Data(Event_Cumu_Data_Info[Index].pDI_Array->PDI, Event_Cumu_Data_Info[Index].pDI_Array->DI_Num, (INT8U *)Pub_Buf0 + 13, pDst + Len, pDst_Start, DstLen);
    
    OS_Mutex_Post(PUB_BUF0_SEM_ID);
  }
  
  return Len;
}

//获取扩展的统计数据、包括失压、失流、反向、断相等的累计数据
INT16U Get_Ext_Event_Cumu_Proto_Data(PROTO_DI PDI, INT8U *pDst, INT8U *pDst_Start, INT16U DstLen)
{
  //PROTO_DI E_PDI;
  INT16U Len;
/*
  if((PDI & 0xFFFF0000) != 0x0EA00000)
  {
    ASSERT_FAILED();
    return 0;
  }
*/
  TRACE();
  
  if(PDI EQ 0x0EA00000 ||\
     PDI EQ 0x0EA00001 ||\
     PDI EQ 0x0EA00002 ||\
     PDI EQ 0x0EA00003)
  {
    //失压
    Len = _Get_Event_Cumu_Proto_Data(EC_DI(0x10000101) + ((PDI - 0x0EA00000) << 16), pDst, pDst_Start, DstLen);
   // break;
  }  
  else if(PDI EQ 0x0EA00100 ||\
     PDI EQ 0x0EA00101 ||\
     PDI EQ 0x0EA00102 ||\
     PDI EQ 0x0EA00103)
  {
    //失流
    Len = _Get_Event_Cumu_Proto_Data(EC_DI(0x18000101) + ((PDI - 0x0EA00100) << 16), pDst, pDst_Start, DstLen);
  }
  else if(PDI EQ 0x0EA00200 ||\
     PDI EQ 0x0EA00201 ||\
     PDI EQ 0x0EA00202 ||\
     PDI EQ 0x0EA00203)
  {
    //反向
    Len = _Get_Event_Cumu_Proto_Data(EC_DI(0x1B000101) + ((PDI - 0x0EA00200) << 16), pDst, pDst_Start, DstLen);
  }
  else if(PDI EQ 0x0EA00300 ||\
     PDI EQ 0x0EA00301 ||\
     PDI EQ 0x0EA00302 ||\
     PDI EQ 0x0EA00303)
  {
    //断相
    Len = _Get_Event_Cumu_Proto_Data(EC_DI(0x13000101) + ((PDI - 0x0EA00300) << 16), pDst, pDst_Start, DstLen);
  } 
  else
  {
    Len = 0;
    ASSERT_FAILED();
  }
  
  return Len;
}

INT16U Get_Event_Cumu_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{
  INT16U Len;
  
  if(PDI EQ 0x10000001) //总失压次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_TOTAL_LOSS_VOL, pDst, pDst, DstLen);
    return 3;
  }
  else if(PDI EQ 0x10000002) //总失压累计时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_TOTAL_LOSS_VOL, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x10010001) //A相失压次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_LOSS_VOLT, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x10010002) //A相失压时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_LOSS_VOLT, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x10020001) //B相失压次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_LOSS_VOLT, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x10020002) //B相失压时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_LOSS_VOLT, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x10030001) //C相失压次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_LOSS_VOLT, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x10030002) //C相失压时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_LOSS_VOLT, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  } 
  else if(PDI EQ 0x11010001) //A相欠压次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_VOLT_LESS, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x11010002) //A相欠压时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_VOLT_LESS, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x11020001) //B相欠压次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_VOLT_LESS, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x11020002) //B相欠压时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_VOLT_LESS, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x11030001) //C相欠压次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_VOLT_LESS, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x11030002) //C相欠压时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_VOLT_LESS, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x12010001) //A相过压次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_VOLT_OVERLOAD, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x12010002) //A相过压时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_VOLT_OVERLOAD, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x12020001) //B相过压次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_VOLT_OVERLOAD, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x12020002) //B相过压时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_VOLT_OVERLOAD, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x12030001) //C相过压次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_VOLT_OVERLOAD, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x12030002) //C相过压时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_VOLT_OVERLOAD, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }    
  else if(PDI EQ 0x13010001) //A相断相次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_LOSS_PARSE, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x13010002) //A相断相时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_LOSS_PARSE, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x13020001) //B相相次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_LOSS_PARSE, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x13020002) //B相断相时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_LOSS_PARSE, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x13030001) //C相断相次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_LOSS_PARSE, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x13030002) //C相断相时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_LOSS_PARSE, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }   
  else if(PDI EQ 0x14000001) //电压逆相序次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_VOLT_NEG_SEQ, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x14000002) //电压逆相序时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_VOLT_NEG_SEQ, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }    
  else if(PDI EQ 0x15000001) //电流逆相序次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_CUR_NEG_SEQ, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x15000002) //电流逆相序时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_CUR_NEG_SEQ, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }   
  else if(PDI EQ 0x16000001) //电压不平衡次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_VOLT_NO_EVEN, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x16000002) //电压不平衡时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_VOLT_NO_EVEN, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }    
  else if(PDI EQ 0x17000001) //电流不平衡次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_CURR_NO_EVEN, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x17000002) //电流不平衡时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_CURR_NO_EVEN, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x18010001) //A相失流次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_LOSS_CURR, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x18010002) //A相失流时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_LOSS_CURR, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x18020001) //B相失流次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_LOSS_CURR, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x18020002) //B相失流时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_LOSS_CURR, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x18030001) //C相失流次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_LOSS_CURR, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x18030002) //C相失流时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_LOSS_CURR, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }  
  else if(PDI EQ 0x19010001) //A相过流次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_OVER_CURR, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x19010002) //A相过流时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_OVER_CURR, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x19020001) //B相过流次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_OVER_CURR, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x19020002) //B相过流时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_OVER_CURR, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x19030001) //C相过流次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_OVER_CURR, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x19030002) //C相过流时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_OVER_CURR, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }  
  else if(PDI EQ 0x1A010001) //A相断流次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_CUT_CURR, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1A010002) //A相断流时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_CUT_CURR, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1A020001) //B相断流次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_CUT_CURR, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1A020002) //B相断流时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_CUT_CURR, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1A030001) //C相断流次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_CUT_CURR, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1A030002) //C相断流时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_CUT_CURR, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }      
  else if(PDI EQ 0x1B010001) //A相潮流反向次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_NEG_CURR, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1B010002) //A相潮流反向时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_NEG_CURR, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1B020001) //B相潮流反向次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_NEG_CURR, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1B020002) //B相潮流反向时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_NEG_CURR, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1B030001) //C相潮流反向次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_NEG_CURR, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1B030002) //C相潮流反向时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_NEG_CURR, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }  
  else if(PDI EQ 0x1C010001) //A相过载次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_POWER_EXCEED, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1C010002) //A相过载时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_POWER_EXCEED, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1C020001) //B相过载次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_POWER_EXCEED, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1C020002) //B相过载时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_POWER_EXCEED, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1C030001) //C相过载次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_POWER_EXCEED, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1C030002) //C相过载时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_POWER_EXCEED, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  } 
  else if(PDI EQ 0x1D000001) //跳闸次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_RELAY_OFF, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1E000001) //合闸次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_RELAY_ON, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1F000001) //总功率因素超下限次数
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_ALL_FACTOR_LOW, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1F000002) //总功率因素超下限时间
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_ALL_FACTOR_LOW, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  } 
  
  /*
   if(PDI EQ 0x03010000)//失压累计 
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_LOSS_VOLT, pDst, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_LOSS_VOLT, pDst + 6, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_LOSS_VOLT, pDst + 12, pDst_Start, DstLen);
      return 18;
   }
   else if(PDI EQ 0x03030000)//过压累计 
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_VOLT_OVERLOAD, pDst, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_VOLT_OVERLOAD, pDst + 6, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_VOLT_OVERLOAD, pDst + 12, pDst_Start, DstLen);
      return 18;     
   }
   else if(PDI EQ 0x03040000)//断相累计
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_LOSS_PARSE, pDst, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_LOSS_PARSE, pDst + 6, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_LOSS_PARSE, pDst + 12, pDst_Start, DstLen);
      return 18;  
   }
  */
   else if(PDI EQ 0x03050000) //全失压
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_ALL_LOSS_VOLT, pDst, pDst_Start, DstLen);
      return 6; 
   }
  /*
   else if(PDI EQ 0x03070000)//电压逆相序
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_VOLT_NEG_SEQ, pDst, pDst_Start, DstLen);
      return 6;      
   }
   else if(PDI EQ 0x03080000)//电流逆相序
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_CUR_NEG_SEQ, pDst, pDst_Start, DstLen);
      return 6;      
   }
   else if(PDI EQ 0x03090000)//电压不平衡
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_VOLT_NO_EVEN, pDst, pDst_Start, DstLen);
      return 6;     
   }
   else if(PDI EQ 0x030A0000)   // 电流不平衡
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_VOLT_NO_EVEN, pDst, pDst_Start, DstLen);
      return 6;      
   }
   else if(PDI EQ 0x030B0000) //失流
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_LOSS_CURR, pDst, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_LOSS_CURR, pDst + 6, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_LOSS_CURR, pDst + 12, pDst_Start, DstLen);
      return 18; 
   }
   else if(PDI EQ 0x030C0000) //过流
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_OVER_CURR, pDst, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_OVER_CURR, pDst + 6, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_OVER_CURR, pDst + 12, pDst_Start, DstLen);
      return 18; 
   } 
   //断流 0x030D0000暂无
   else if(PDI EQ 0x030E0000)//潮流反向
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_NEG_CURR, pDst, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_NEG_CURR, pDst + 6, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_NEG_CURR, pDst + 12, pDst_Start, DstLen);
      return 18;  
   }
*/
   else if(PDI EQ 0x03110000)//掉电
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_POWER_OFF, pDst, pDst_Start, DstLen);
      return 3; 
   }
   else if(PDI EQ 0x03120000) //需量超限
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_POS_ACT_DEMAND_EXCEED, pDst, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_NEG_ACT_DEMAND_EXCEED, pDst + 3, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_Q1_REAC_DEMAND_EXCEED, pDst + 6, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_Q2_REAC_DEMAND_EXCEED, pDst + 9, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_Q3_REAC_DEMAND_EXCEED, pDst + 12, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_Q4_REAC_DEMAND_EXCEED, pDst + 15, pDst_Start, DstLen);      
      return 18; 
   }
   else if(PDI EQ 0x03300000) //编程总次数
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_PROG, pDst, pDst_Start, DstLen);
      return 3;  
   }
   else if(PDI EQ 0x03300100) //电表清0
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_CLR_ALL_DATA, pDst, pDst_Start, DstLen);
      return 3;  
   }
   else if(PDI EQ 0x03300200) //需量清0
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_CLR_DEMAND_COM, pDst, pDst_Start, DstLen);
      return 3;  
   } 
   else if(PDI EQ 0x03300300) //事件清0
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_CLR_PROCESS, pDst, pDst_Start, DstLen);
      return 3;  
   } 
   else if(PDI EQ 0x03300400) //校时
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_ADJUST_TIME, pDst, pDst_Start, DstLen);
      return 3;     
   }
   else if(PDI EQ 0x03300500) //时段表编程
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_DATE, pDst, pDst_Start, DstLen);
      return 3;      
   }
   else if(PDI EQ 0x03300600) //时区表编程
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_YEAR, pDst, pDst_Start, DstLen);
      return 3;      
   }
   else if(PDI EQ 0x03300700) //周休日编程
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_WEEK, pDst, pDst_Start, DstLen);
      return 3;      
   }
   else if(PDI EQ 0x03300800) //节假日编程
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_HOLIDAY, pDst, pDst_Start, DstLen);
      return 3;      
   }
   else if(PDI EQ 0x03300900) //有功组合方式编程
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_ACPWR, pDst, pDst_Start, DstLen);
      return 3;      
   }
   else if(PDI EQ 0x03300A00) //无功组合方式1编程
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_REACPWR1, pDst, pDst_Start, DstLen);
      return 3;      
   }   
   else if(PDI EQ 0x03300B00)//无功组合方式2编程
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_REACPWR2, pDst, pDst_Start, DstLen);
      return 3;
   }
   else if(PDI EQ 0x03300C00)//结算日编程
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_SETTLE_DATE, pDst, pDst_Start, DstLen);
      return 3;
   }
   else if(PDI EQ 0x03300D00)//开表盖
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_UP_COVER_OPEN, pDst, pDst_Start, DstLen);
      return 3;
   }
   else if(PDI EQ 0x03300E00)//开端钮
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_DOWN_COVER_OPEN, pDst, pDst_Start, DstLen);
      return 3; 
   }
   /*else if(PDI EQ 0x03310000)//拉闸
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_RELAY_OFF, pDst, pDst_Start, DstLen);
      return 6;      
   }*/
   else if((PDI & 0xFFFF0000) EQ 0x0EA00000) //失压、失流、断相、反向的累加数据
   {
      Len = Get_Ext_Event_Cumu_Proto_Data(PDI, pDst, pDst_Start, DstLen);
      return Len;
   }
   else if(PDI EQ 0x03410000) //低功耗电池欠压
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_LOWPWR_BAT_LOW, pDst, pDst_Start, DstLen);
      return 3; 
   }
   else if(PDI EQ 0x03410100) //时钟电池欠压
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_RTC_BAT_LOW, pDst, pDst_Start, DstLen);
      return 3; 
   }  
   else if(PDI EQ 0x03420000) //负控报警
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_DEMAND_ALARM, pDst, pDst_Start, DstLen);
      return 6; 
   }
   else if(PDI EQ 0x03420100) //负控跳闸
   {
      //Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_DEMAND_SWITCH, pDst, pDst_Start, DstLen);
      //return 3; 
     return 0;
   }    
   else if(PDI EQ 0x0E180000) //复位
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_RESET, pDst, pDst_Start, DstLen);
      return 3; 
   }    
   else if(PDI EQ 0x0E190000) //运行时钟乱
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_RTCERR_RUN, pDst, pDst_Start, DstLen);
      return 3; 
   }
   else if(PDI EQ 0x0E1C0000) //上电时钟乱
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_RTCERR_PWRON, pDst, pDst_Start, DstLen);
      return 3; 
   }   
   else if(PDI  EQ 0x0E301100) //设置初始电量
   {
     Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_SET_ENERG, pDst, pDst_Start, DstLen);
     return 3;
   }
   return 0;
}

INT8U Clear_One_Event_Data(PROTO_DI PDI)
{
  INT8U Event_ID;
  INT16U Index;
  
  //清电压统计类数据需要特殊处理
  if((PDI & 0xFFFF0000) EQ 0x03100000 && ((PDI >> 8) & 0xFF) <= 3)
  {
    return Clear_Proto_Phase_VolStat_Data(PDI);
  }
  //清除总失压累计数据
  if(PDI EQ 0x100000FF)
  {
    Clear_One_Event_Cumu_Data(ID_EVENT_TOTAL_LOSS_VOL);
    return 1;
  }
  
  //前一次失压发生和结束时间清除
  if(PDI EQ 0x100001FF || PDI EQ 0x100002FF)
  {
    Write_Storage_Data(SDI_LAST_LOSS_VOL_OCCUR_TIME, (INT8U *)Zero, 6);  
    Write_Storage_Data(SDI_LAST_LOSS_VOL_END_TIME, (INT8U *)Zero, 6);
    return 1;
  }
  
  PDI = Get_Event_Separate_Start_PDI(PDI);
  PDI = ((PDI & 0xFFFFFF00) | 0x01);
  Index = Get_Event_Separate_Proto_Index(PDI); //该事件在分次事件数据中的索引
  if(Index EQ NULL_2BYTES)
    return 0;
  
  Event_ID = Event_Separate_Data_Info[Index].Event_ID;
  
  if(Clear_One_Event_Separate_Data(Event_ID) > 0)
  {
    Clear_One_Event_Cumu_Data(Event_ID);
    return 1;
  }  
  
  return 0;  
}

#undef EVENT_PROTO_C


