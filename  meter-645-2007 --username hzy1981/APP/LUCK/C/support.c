
/**
 * @file support.c
 *     { comment block }
 * @brief
 *     { brief description @ref support.cpp }
 * @author li.yao (nardoo@sohu.com)
 * @version v1.00
 * @date 05/29/2008 08:41
 * @note
 *     { paragraph where a note can be entered. }
 */

#include "Pub_PUCK.h"
#include "config.h"


typedef struct
{
  u8  bytes:3;  //单屏显示字节数：<=5,用于计算偏移
  u8  frmt:5;   //格式宏
}DIS_FORMAT;

#define MAX_SUB_SCREEN_NUM  32
//多屏显示元素属性表
typedef struct{
  item_t      di;
  u8          subnums;       //子元素显示个数
  DIS_FORMAT  fomat[MAX_SUB_SCREEN_NUM];     //最大的子屏数目
}DIS_MULT_SCREEN;           //多屏显示项目属性配置表

DIS_MULT_SCREEN const Con_Dis_Muit_Screen[]=
{
  {0x00000000,0,{{0,0}}},
  {0x01000000,3,{{3,1},{3,18},{2,19}}},
  /*
  {0x03010000,6,{{3,10},{3,10},{3,10},{3,10},{3,10},{3,10}}},
  {0x03020000,6,{{3,10},{3,10},{3,10},{3,10},{3,10},{3,10}}},
  {0x03030000,6,{{3,10},{3,10},{3,10},{3,10},{3,10},{3,10}}},
  {0x03040000,6,{{3,10},{3,10},{3,10},{3,10},{3,10},{3,10}}},
  {0x03050000,2,{{3,10},{3,10}}},
  {0x03060000,2,{{3,10},{3,10}}},
  {0x03070000,2,{{3,10},{3,10}}},
  {0x03080000,2,{{3,10},{3,10}}},
  {0x03090000,2,{{3,10},{3,10}}},
  {0x030A0000,2,{{3,10},{3,10}}},
  {0x030B0000,6,{{3,10},{3,10},{3,10},{3,10},{3,10},{3,10}}},
  {0x030C0000,6,{{3,10},{3,10},{3,10},{3,10},{3,10},{3,10}}},
  {0x030D0000,6,{{3,10},{3,10},{3,10},{3,10},{3,10},{3,10}}},
  {0x030E0000,6,{{3,10},{3,10},{3,10},{3,10},{3,10},{3,10}}},
  {0x030F0000,6,{{3,10},{3,10},{3,10},{3,10},{3,10},{3,10}}},
  
  {0x03110001,4,{{3,4},{3,5},{3,4},{3,5}}},
  {0x03110002,4,{{3,4},{3,5},{3,4},{3,5}}},
  {0x03110003,4,{{3,4},{3,5},{3,4},{3,5}}},
  {0x03110004,4,{{3,4},{3,5},{3,4},{3,5}}},
  {0x03110005,4,{{3,4},{3,5},{3,4},{3,5}}},
  {0x03110006,4,{{3,4},{3,5},{3,4},{3,5}}},
  {0x03110007,4,{{3,4},{3,5},{3,4},{3,5}}},
  {0x03110008,4,{{3,4},{3,5},{3,4},{3,5}}},
  {0x03110009,4,{{3,4},{3,5},{3,4},{3,5}}},
  {0x0311000A,4,{{3,4},{3,5},{3,4},{3,5}}},
  */
  {0x03300001,3,{{3,4},{3,5},{4,9}}},
  
  {0x04010000,14,{
                  {3,15},{3,15},{3,15},{3,15},{3,15},{3,15},{3,15},
                  {3,15},{3,15},{3,15},{3,15},{3,15},{3,15},{3,15}}
                 },
  {0x04010001,14,{
                  {3,16},{3,16},{3,16},{3,16},{3,16},{3,16},{3,16},
                  {3,16},{3,16},{3,16},{3,16},{3,16},{3,16},{3,16}}
                 },
                 
  {0x04000106,2,{{3,18},{2,19}}},  //年月日 时分
  {0x04000107,2,{{3,18},{2,19}}},  //年月日 时分
  {0x04000108,2,{{3,18},{2,19}}},  //年月日 时分
  {0x04000109,2,{{3,18},{2,19}}},  //年月日 时分
   
   
  {0x04020000,14,{
                  {3,15},{3,15},{3,15},{3,15},{3,15},{3,15},{3,15},
                  {3,15},{3,15},{3,15},{3,15},{3,15},{3,15},{3,15}}
                 },
  {0x04020001,14,{
                  {3,16},{3,16},{3,16},{3,16},{3,16},{3,16},{3,16},
                  {3,16},{3,16},{3,16},{3,16},{3,16},{3,16},{3,16}}
                 },
                 
  {0x04030001,14,{
                  {3,9},{3,9},{3,9},{3,9},{3,9},{3,9},{3,9},
                  {3,9},{3,9},{3,9},{3,9},{3,9},{3,9},{3,9}}
                 },   
    
  {0x04000401,2,{{2,20},{4,9}}},   
  {0x04000402,2,{{2,20},{4,9}}}, 
  {0x04000403,8,{{4,9},{4,6},{4,6},{4,6},{4,6},{4,6},{4,6},{4,9}}},
  
  {0x10000101,2,{{3,18},{2,21}}},   //年月日 时分秒
  {0x10000201,2,{{3,18},{2,21}}},   //年月日 时分秒
  
  /*
  {0x0400040B,2,{{4,6},{4,6}}},
  {0x0400040C,2,{{4,6},{4,6}}},
  {0x0400040D,2,{{4,6},{4,6}}},
  
  {0x04800001,8,{{4,6},{4,6},{4,6},{4,6},{4,6},{4,6},{4,6},{4,6}}},
  {0x04800002,8,{{4,6},{4,6},{4,6},{4,6},{4,6},{4,6},{4,6},{4,6}}},
  {0x04800003,8,{{4,6},{4,6},{4,6},{4,6},{4,6},{4,6},{4,6},{4,6}}},
  
    
  {DI_LOSS_VOLT_DATA, 22,{{3,10},{4,13},                              //0x0EAO0000---总失压期间累计数据
                        {4,12},{4,12},{4,12},{4,12},
                        {4,12},{4,12},{4,12},{4,12},
                        {4,12},{4,12},{4,12},{4,12},
                        {4,12},{4,12},{4,12},{4,12},
                        {4,14},{4,14},{4,14},{4,14}}},
                        
  {DI_LOSS_VOLT_DATA_A,22,{{3,10},{4,13},                            //0x0EAO0001---A相失压期间累计数据
                        {4,12},{4,12},{4,12},{4,12},
                        {4,12},{4,12},{4,12},{4,12},
                        {4,12},{4,12},{4,12},{4,12},
                        {4,12},{4,12},{4,12},{4,12},
                        {4,14},{4,14},{4,14},{4,14}}},
                        
  {DI_LOSS_VOLT_DATA_B,22,{{3,10},{4,13},                           //0x0EAO0002---B相失压期间累计数据
                        {4,12},{4,12},{4,12},{4,12},
                        {4,12},{4,12},{4,12},{4,12},
                        {4,12},{4,12},{4,12},{4,12},
                        {4,12},{4,12},{4,12},{4,12},
                        {4,14},{4,14},{4,14},{4,14}}},
                        
  {DI_LOSS_VOLT_DATA_C,22,{{3,10},{4,13},                           //0x0EAO0003---C相失压期间累计数据
                        {4,12},{4,12},{4,12},{4,12},
                        {4,12},{4,12},{4,12},{4,12},
                        {4,12},{4,12},{4,12},{4,12},
                        {4,12},{4,12},{4,12},{4,12},
                        {4,14},{4,14},{4,14},{4,14}}},
                        
                        
  {DI_LOSS_VOLT_START,2,{{3,4},{3,5}}},                         //0x0EAO0000---最近一次失压起始日期时间
  {DI_LOSS_VOLT_END,  2,{{3,4},{3,5}}},                          //0x0EAO0000---最近一次失压结束日期时间
*/
};

#define MAX_SUB_NUM (sizeof(Con_Dis_Muit_Screen)/sizeof(DIS_MULT_SCREEN))




// screen model words.
typedef struct {    
    code_t code;     //C模式下的显示代码-----PUCK，DI    
    code_t user;     //A/B模式下的显示代码-----PUCK,右下脚
    u8     dlen;
    u8     ChangeFlag;  //扩展数据标志
    code_t ChangeCode;  //扩展虚拟ID    
} list_t;

// 显示屏缓冲
list_t vlist;


INT8U Get_Code (scrn_t *temp,PROTO_DI di,const scrn_t *p)
{
  INT8U tempdata,i;
  INT8U ByteFlag;  //0～3表示不同的byte部分
  
  tempdata=0;
  ByteFlag=0;
  
  if((GROUP_NO EQ temp->GroupType[0].GroupFlag) &&(GROUP_NO EQ temp->GroupType[1].GroupFlag))
    return 0;
    
  if(di != temp->item)
  {
    for(i=2; i<=2; i--)  //设置byte相异标志,从高到低位搜索
    {
      if((BYTE(di,i)!=BYTE(temp->item,i)))  //本字节不等
      {
        if((GROUP_NO!=temp->GroupType[0].GroupFlag)||(GROUP_NO!=temp->GroupType[1].GroupFlag)) //本字节确实是异类
        {
          if((i==temp->GroupType[0].BytePos)||(i==temp->GroupType[1].BytePos))  //获取异类位置
          {
            tempdata++;
            if(tempdata>2)   //不可能有2个以上的DI相异
              return  0;
            SET_BIT(ByteFlag,i);
          }
          else   //错位：不是本ID
           return  0;
        }
         else   //本字节不等，但描述不是此位置
           return  0;        
      }    
    }
  }
  else
    return 1;
  
  *temp=*p;
  //修改显示元素
  for(i=0;i<2;i++)   
  {
    switch(temp->GroupType[i].GroupFlag)  //相异的标志类型
    {
      case GROUP_TARIFF:   //费率
        if(BYTE(di,temp->GroupType[i].BytePos)>MAX_TARIFF)
          return 0;
        
        if(GET_BIT(ByteFlag,temp->GroupType[i].BytePos))  //此字节不同，需要修改显示元素
        {
          temp->elem.feerate=1;           //显示 "费率"
          temp->elem.tariff=BYTE(di,temp->GroupType[i].BytePos);         //显示 "Txx"
          temp->elem.total=0;
        }
        else
          temp->elem.total=1;      
      break;
      
      case GROUP_SETTLE:  //结算日
        if(BYTE(di,temp->GroupType[i].BytePos)>MAX_SETTLE)
          return 0;
        
        if(GET_BIT(ByteFlag,temp->GroupType[i].BytePos))  //此字节不同，需要修改显示元素
        {
          temp->elem.lastmonth=1;                                    //显示 "上月"
          temp->elem.times=BYTE(di,temp->GroupType[i].BytePos);     //显示 "xx"
          temp->elem.thismonth=0; 
        }
        else
          temp->elem.thismonth=1;                                       //显示当前或者当月
      break; 
      
      case GROUP_PHASE:  //A/B/C/N  相    
        if(BYTE(di,temp->GroupType[i].BytePos)>MAX_PHASE)
          return 0;
        
        if(GET_BIT(ByteFlag,temp->GroupType[i].BytePos))  //此字节不同，需要修改显示元素
        {
          temp->elem.phase=BYTE(di,temp->GroupType[i].BytePos);         //显示 A/B/C/N 相
          temp->elem.total=0;
        }
        else
          temp->elem.total=1;                                           //显示总
      break;
      
      case GROUP_HARMO:     // 谐波次数
        if(BYTE(di,temp->GroupType[i].BytePos)>MAX_HARMO)
          return 0;
      break;
      
      case GROUP_TIMES:    // 密码等级
        if(BYTE(di,temp->GroupType[i].BytePos)>MAX_PASSW)
          return 0;
        
        if(GET_BIT(ByteFlag,temp->GroupType[i].BytePos))  //此字节不同，需要修改显示元素
        {
          temp->elem.lasttime=1;  //显示"上次"
          temp->elem.times=BYTE(di,temp->GroupType[i].BytePos);     //显示 "xx"
        }
      break;
    }
  }
  //修改 di
  temp->item=di;
  return 1;
}


u8 Is_Multi_Screen(item_t item)
{
  u16 i;
  
  if(DI_IS_DEMAND(item)) //需量
     return 1;
   
  for(i=0;i<MAX_SUB_NUM && i<0xff;i++) //不可能支持对于 256个
  {
    if(item EQ Con_Dis_Muit_Screen[i].di)
    {
     return i;    //返回位置  
    }    
  }  
  
  return 0;  //不是多屏显示
}

/***********************************************************************
函数功能：获取需量分页的显示单位
入口：1------------强行清除事件瞬态字，和事件发生结果状态字sram；0-------根据CS值来清除
出口：无
***********************************************************************/
u8 Get_Demand_Unit_Frmt(u8 byte,u8 index)
{
  if(index >2)
    ASSERT_FAILED();

  if(index EQ 1) //需量时间:年月日
    return 18;
  
  if(index EQ 2) //需量时间:时分
    return 19;
  
   if(byte >=0x09 && byte <=0x0A)  //视在总最大需量
    return 8;
  
  if(byte >=0x03 && byte <=0x08)  //总无功需量
    return 7;
  
  //总有功需量
  return 1;
  
}



// 搜索该 item是否是多屏显示，是的话返回非0；并修改相应子屏信息
u8 Judge_Modi_Sub_Screen(item_t item,u8 proc) 
{
  //搜索 item对应的显示项目，是否是多屏显示，不是多屏显示，不做任何改动,仅 vlist.SubCurs=0
  //表格要求： ID 最大的子元素个数，偏移，每个子元素的数据格式描述，

  u8 pos,flag;
  u16 i;  
    
  pos=Is_Multi_Screen(item);
 
  if(pos EQ 0)  //不存在
  {
    Sub_Vlist.exist=0;
    Sub_Vlist.subindex=0;
    Sub_Vlist.fmtindex=0; 
    Sub_Vlist.offset=0; 
    return PROC_SWITCH;
  }
  
  //多屏显示的  
  if(Sub_Vlist.subindex>=Con_Dis_Muit_Screen[pos].subnums  \
                          || Sub_Vlist.subindex>=MAX_SUB_SCREEN_NUM || pos>=MAX_SUB_NUM)
  {
    Sub_Vlist.subindex=0;
    ASSERT_FAILED();
  }
  
  //添加 item不相等，初始化 Sub_Vlist
  flag=PROC_NONE;
  if(item!= vlist.code)
  {    
     if(proc EQ PROC_ADD)  //+
     {
        Sub_Vlist.subindex=0;
     }
     if(proc EQ PROC_SUB)  //-           
     {
        Sub_Vlist.subindex=Con_Dis_Muit_Screen[pos].subnums-1;
     }
  }
  else  
  {
    switch(proc)
    {
     case PROC_ADD:
      Sub_Vlist.subindex++;
      if(Sub_Vlist.subindex>=Con_Dis_Muit_Screen[pos].subnums-1)
        flag=PROC_ADD;
      break;
     case PROC_SUB:
       Sub_Vlist.subindex--;
       if(Sub_Vlist.subindex >=Con_Dis_Muit_Screen[pos].subnums)
         Sub_Vlist.subindex=Con_Dis_Muit_Screen[pos].subnums-1;
       
       if(Sub_Vlist.subindex EQ 0 || Sub_Vlist.subindex>=Con_Dis_Muit_Screen[pos].subnums-1)
        flag=PROC_SUB;
      break; 
    }
  }
  
  Sub_Vlist.subindex=Sub_Vlist.subindex%Con_Dis_Muit_Screen[pos].subnums;
  
  Sub_Vlist.exist=MULIT_EXSIT;
  
  if(DI_IS_DEMAND(item))  //需量：做表的话，较多，在这里死判
  {
    Sub_Vlist.fmtindex=Get_Demand_Unit_Frmt(BYTE(item,2),Sub_Vlist.subindex);    
  }
  else
    Sub_Vlist.fmtindex=Con_Dis_Muit_Screen[pos].fomat[Sub_Vlist.subindex].frmt;
  
  Sub_Vlist.offset=0;
  Sub_Vlist.len=Con_Dis_Muit_Screen[pos].fomat[Sub_Vlist.subindex].bytes;
  for(i=0;i<Sub_Vlist.subindex;i++)
  {
     Sub_Vlist.offset+=Con_Dis_Muit_Screen[pos].fomat[i].bytes;       
  }
  return flag;
}

// 搜索该 item是否是多屏显示，是的话返回非0；并修改相应子屏信息
void Get_Sub_Screen_Info(item_t item,u8 subindex) 
{
  //搜索 item对应的显示项目，是否是多屏显示，不是多屏显示，不做任何改动,仅 vlist.SubCurs=0
  //表格要求： ID 最大的子元素个数，偏移，每个子元素的数据格式描述，

  u8 pos;
  u16 i;  
    
  pos=Is_Multi_Screen(item);
 
  if(pos EQ 0)  //不存在
  {
    Sub_Vlist.exist=0;
    Sub_Vlist.subindex=0;
    Sub_Vlist.fmtindex=0; 
    Sub_Vlist.offset=0; 
    return ;
  }
  
  Sub_Vlist.exist=MULIT_EXSIT;
  Sub_Vlist.subindex=subindex%Con_Dis_Muit_Screen[pos].subnums;  
  //多屏显示的  
  if(Sub_Vlist.subindex>=Con_Dis_Muit_Screen[pos].subnums  \
                          || Sub_Vlist.subindex>=MAX_SUB_SCREEN_NUM || pos>=MAX_SUB_NUM)
  {
    Sub_Vlist.subindex=0;
    ASSERT_FAILED();
  }
  
  if(DI_IS_DEMAND(item))  //需量：做表的话，较多，在这里死判
  {
    Sub_Vlist.fmtindex=Get_Demand_Unit_Frmt(BYTE(item,2),Sub_Vlist.subindex);    
  }
  else
    Sub_Vlist.fmtindex=Con_Dis_Muit_Screen[pos].fomat[Sub_Vlist.subindex].frmt;
  
  Sub_Vlist.offset=0;
  Sub_Vlist.len=Con_Dis_Muit_Screen[pos].fomat[Sub_Vlist.subindex].bytes;
  for(i=0;i<Sub_Vlist.subindex;i++)
  {
     Sub_Vlist.offset+=Con_Dis_Muit_Screen[pos].fomat[i].bytes;       
  }
}

//C模式下，获取子显示屏号,修改按钮主屏偏移
void Judge_Modi_C_Offset(u8 pos,u8 proc) 
{
  //搜索 item对应的显示项目，是否是多屏显示，不是多屏显示，不做任何改动,仅 vlist.SubCurs=0
  //表格要求： ID 最大的子元素个数，偏移，每个子元素的数据格式描述，
  if(pos EQ 0)
    return ; 
  
  //其他多屏显示的  
  if(Sub_Vlist.subindex>=Con_Dis_Muit_Screen[pos].subnums  || Sub_Vlist.subindex>=MAX_SUB_SCREEN_NUM || pos>=MAX_SUB_NUM)
  {
    Sub_Vlist.subindex=0;
    ASSERT_FAILED();
  }
  
  if(proc EQ PROC_ADD)  //+
  {
    Sub_Vlist.subindex++;
    if(Sub_Vlist.subindex>=Con_Dis_Muit_Screen[pos].subnums)  //翻转
    {
      Sub_Vlist.subindex=0;  //切换至最小屏号
    }
    return ;
  }
  if(proc EQ PROC_SUB)  //+
  {
    Sub_Vlist.subindex--;
    if(Sub_Vlist.subindex==0 || Sub_Vlist.subindex>=Con_Dis_Muit_Screen[pos].subnums)   //翻转
    {
      Sub_Vlist.subindex=Con_Dis_Muit_Screen[pos].subnums-1;
    }
    return ;
  }  
  if(proc EQ PROC_NONE)  //
  {
    if(Sub_Vlist.subindex EQ 0)
      Sub_Vlist.subindex=0;
  }  
}
/********************************************************************************
PUCK:
函数功能：获取对应模式（A或者B）下的具体显示项目
入口：
     item-----显示项目，同645标识;offs-----该项目下的后续项目，及偏移
返回：
********************************************************************************/
/********************************************************************************
void getlist (item_t item, offs_t offs, u8 proc) 
{
  INT16U Len;
  list_t list = {0, 0, 0}; //初始化为0，对未设置屏内容的，将显示总电量 
  u8 flag;
  offs_t offtemp;
  
  if(((INT32U)(item&0xFFFF00FF))!=0x04040001)  //取的是非法数据
  {
    ASSERT_FAILED(); 
    return ;
  }
  
  if(Sub_Vlist.lastproc!=proc && proc!=PROC_NONE)
  {
    if(proc EQ PROC_ADD)  //上次是－
    {
      dispoffset+=2;
       if(Sub_Vlist.exist EQ MULIT_EXSIT)
        dispoffset--;
      Refresh_Curr_Offset();
      
    }
    if(proc EQ PROC_SUB) //上次是＋，本次是减
    {
      if(dispoffset EQ 0)
      {
        if(Sub_Vlist.exist EQ MULIT_EXSIT)
          dispoffset=(dispmode EQ modeA)?(MODE_A_NUM-1):(MODE_B_NUM-1);
        else
          dispoffset=(dispmode EQ modeA)?(MODE_A_NUM-2):(MODE_B_NUM-2);
      }
      else
      {
        dispoffset-=2;
        if(Sub_Vlist.exist EQ MULIT_EXSIT)
          dispoffset++;
      }
      Refresh_Curr_Offset();      
    }
    Sub_Vlist.lastproc=proc;    
  }
  
  offtemp=dispoffset;
  Len=Read_Storage_Data(item+offtemp,&list,&list,sizeof(list));  //修改偏移，获取最新的ID
  if(0==Len)
    ASSERT_FAILED();
  
  flag=Judge_Modi_Sub_Screen(list.code,proc);
  if(flag EQ PROC_SUB ||flag EQ PROC_ADD) //多屏切换
  {
    Modi_AB_Offset(flag);    
  }
  
  
  //offs++;  //偏移0干掉
  list.user=((offtemp+1)/10)*16+((offtemp+1)%10);         //显示代码用偏移替代:BCD
  list.code=Modi_Item(list.code);  //修改不兼容的ID，用于显示
  
  vlist=list;
  vlist.dlen = 2;
  
  if(flag EQ PROC_SWITCH)  ///单屏切换
  {
    switch(proc)
    {
      case PROC_ADD:
        dispoffset++;
        break;
      case PROC_SUB:
        dispoffset--;
        break;
    }    
  } 
  
  Refresh_Curr_Offset();
  
}
********************************************************************************/


/********************************************************************************
PUCK:
函数功能：获取对应模式（A或者B）下的具体显示项目
入口：
     item-----显示项目，同645标识;offs-----该项目下的后续项目，及偏移
返回：
********************************************************************************/

list_t getlist (item_t item, offs_t offs) 
{
  INT16U Len;
  list_t list = {0, 0, 0, 0, 0}; //初始化为0，对未设置屏内容的，将显示总电量 
  u8 temp[5];
  u8 subindex;


  if(((INT32U)(item&0xFFFF00FF))!=0x04040001)  //取的是非法数据
  {
    ASSERT_FAILED(); 
    return list;
  }
  
  Len=Read_Storage_Data(item+offs,temp,temp,sizeof(temp));  //修改偏移，获取最新的ID  
  if(0==Len)
    ASSERT_FAILED();  
  
#ifdef  DIS_ITEM_BYTE_4  
  mem_cpy((void *)(&list.code),temp,sizeof(list.code),(void *)(&list.code),sizeof(list.code));
  subindex=BYTE(list.code,0)&0x0f;
  list.code=list.code>>0x04;
#else  
  mem_cpy((void *)(&list.code),temp+1,sizeof(list.code),(void *)(&list.code),sizeof(list.code));
  subindex=temp[0]&0xff;  //多读出的1个字节
#endif
 

  
  Get_Sub_Screen_Info(list.code,subindex);  
  
  //list.user=((offs+1)/10)*16+((offs+1)%10);         //显示代码用偏移替代:BCD
  list.user=subindex;
  list.ChangeCode=list.code;
  list.ChangeFlag=Modi_Item(list.code,&list.code);  //修改不兼容的ID，用于显示
  return list;
}

/********************************************************************************
PUCK:
函数功能：获取对应模式（A或者B）下的具体显示项目
入口：
     item-----显示项目，同645标识;offs-----该项目下的后续项目，及偏移
返回：
********************************************************************************/
void Init_DisItem (void) 
{
  vlist.code=DI_DATE_WEEK;
  vlist.user=0x01;         //显示代码用偏移替代:BCD
  vlist.ChangeFlag=0;
  vlist.dlen=2;
}
/********************************************************************************
PUCK:
函数功能：根据修改的DI值，设置C模式下的显示code
入口：
返回：
********************************************************************************
PROTO_DI Set_ParaModi_Proc(PROTO_DI ModiDI) 
{
  const scrn_t* p;
  
  PROTO_DI DisCode=0;
  
   for(p=&table[0];p!= &table[MAXCOUNT];++p) 
   {
     if (ModiDI==p->item)
     {
       DisCode=p->code;
       break;
      }
   }
   return DisCode;
}
********************************************************************************/

/********************************************************************************
PUCK:
函数功能：按位置显示内容：实际只适用A/B模式
入口：
     type-----模式参数;offs-----该模式下显示的项目顺序
返回：
********************************************************************************/
void lcdshow (u8 type, offs_t offs) 
{
    switch (type) 
    {
        case modeA: //A模式下，根据645标识及其偏移获取显示元素-----------PUCK
        {
            vlist=getlist(ITEMMODEA, offs % MODE_A_NUM);
            vlist.dlen = 2;
            break;
        }
        case modeB: //B模式下，根据645标识及其偏移获取显示元素-----------PUCK
        {
            vlist=getlist(ITEMMODEB, offs % MODE_B_NUM);
            vlist.dlen = 2;
            break;
        }
        default :   //C模式下，根据表的偏移获取显示元素-----------PUCK
        {
            vlist.user = table[offs % MAXCOUNT].item; 
            vlist.dlen = MAXBITS;
            break;
        }
    }
}
/********************************************************************************
PUCK:
函数功能：根据模式参宿,显示编码，获取显示信息。
入口：
     type-----模式参数;code-----该模式下显示的项目顺序
返回：
********************************************************************************/
u8 Ser_Support_Code(item_t code)
{
#ifdef DIS_PARA_JUMP_EN
  const scrn_t* p;
  for(p=&table[0];p!=&table[MAXCOUNT];++p) 
  {
    if (code==p->item) 
    {
      return 1;
    }
  }
#endif
 return 0;
}
/********************************************************************************
PUCK:
函数功能：按编码显示内容：实际C模式显示
入口：
     type-----模式参数;code-----该模式下显示的项目顺序
返回：
********************************************************************************/
void display(u8 type, code_t code) 
{
    vlist.user = code;
    vlist.ChangeCode = code;
    vlist.code=code;
    vlist.ChangeFlag=Modi_Item(vlist.code,&vlist.code);  //修改不兼容的ID，用于显示
    vlist.dlen = MAXBITS+1;
}
/********************************************************************************
PUCK:
函数功能：修改需量显示元素
入口：
返回：
********************************************************************************/
void Modi_Demand_DIs_Item(scrn_t *scrn) 
{
    if((Sub_Vlist.subindex-1)%3 EQ 0  || (Sub_Vlist.subindex-2)%3 EQ 0) //需量时间
        scrn->elem.time=1;
    else
        scrn->elem.time=0;
    
    switch(Sub_Vlist.subindex)
    {
      case 3:
      case 4:  
      case 5:
        scrn->elem.total=0;
        scrn->elem.tariff=1;
        break;
       
      case 6:
      case 7:  
      case 8:
        scrn->elem.total=0;
        scrn->elem.tariff=2;
        break;
        
      case 9:
      case 10:  
      case 11:
        scrn->elem.total=0;
        scrn->elem.tariff=3;
        break;
        
      case 12:
      case 13:  
      case 14:
        scrn->elem.total=0;
        scrn->elem.tariff=4;
        break;
    }
}
/********************************************************************************
PUCK:
函数功能：获取屏幕显示信息，并显示
入口：
     type-----模式参数;curs-----光标位置
返回：
********************************************************************************/
void screen (u8 type, curs_t curs) 
{
      const scrn_t* p;
  //在此前，vlist的信息已经更新-----PUCK
    static scrn_t scrn={0xffffffff,{{GROUP_NO,0},{GROUP_NO,0}},"",{0}};   //不为0，保证第一次就能更新，因为0x000000有可能第一次就是0---PUCK
    if (scrn.item != vlist.code)     //按照命令代码检索：A/B模式下为协议DI代码，C模式下还是显示代码
    {
        for (p=&table[0];p!=&table[MAXCOUNT];++p) 
        {
            scrn=*p;        
            {
              if(scrn.item EQ vlist.code) //就是此ID
               break;
              
              if(BYTE(scrn.item,3)==BYTE(vlist.code,3))  //不是此ID，但最高字节必须相等，才能在此组中查找！
              {
                if(Get_Code(&scrn,vlist.code,p))  //按照命令代码检索,修改其scrn的值
                  break;
              }
            }
        }
    }
    if(Sub_Vlist.exist EQ MULIT_EXSIT && DI_IS_DEMAND(scrn.item)) //需量显示：时间，显示单位再想办法
    {
      if((Sub_Vlist.subindex-1)%3 EQ 0  || (Sub_Vlist.subindex-2)%3 EQ 0) //需量时间
        scrn.elem.time=1;
      else
        scrn.elem.time=0;
    }
    
    if(p==&table[MAXCOUNT]) //找不到显示的代码,只显示代码，事件，其他不显示-------PUCK
    {
      //lcd_value("rEAd bAd|");
      //lcd_value("GET NodATA|");
      lcd_code    (vlist.user, vlist.code, curs, Sub_Vlist.subindex,vlist.ChangeFlag,vlist.ChangeCode);
      lcd_events  ();
      lcd_update  ();  
      return ;
    }
    
    curs %= vlist.dlen;
    lcd_data     (scrn.item, scrn.frmt, Sub_Vlist);   //18ms
    lcd_code     (vlist.user, vlist.code, curs, Sub_Vlist.subindex,vlist.ChangeFlag,vlist.ChangeCode);       //26ms
    lcd_mode     (type);                ///A/B/C 3种模式
    lcd_total    (scrn.elem.total    ); ///< "总",
    lcd_phase    (scrn.elem.phase    ); ///< "A/B/C相",
    lcd_voltage  (scrn.elem.voltage  ); ///< "电压",
    lcd_current  (scrn.elem.current  ); ///< "电流",
    lcd_positive (scrn.elem.positive ); ///< mode4.bit4 ? "输入" : "正向";
    lcd_negative (scrn.elem.negative ); ///< mode4.bit4 ? "输出" : "反向";
    lcd_reactive (scrn.elem.reactive ); ///< "无功",
    lcd_active   (scrn.elem.active   ); ///< "有功",
    lcd_power    (scrn.elem.power    ); ///< "功率",
    lcd_factor   (scrn.elem.factor   ); ///< "因数",
    lcd_angle    (scrn.elem.angle    ); ///< "相角",
    lcd_energy   (scrn.elem.energy   ); ///< "电量",
    lcd_demand   (scrn.elem.demand   ); ///< "需量",
    lcd_time     (scrn.elem.time     ); ///< "时间",
    lcd_charge   (scrn.elem.charge   ); ///< "电费",
    lcd_lostvolt (scrn.elem.lostvolt ); ///< "失压",
    lcd_lostcurt (scrn.elem.lostcurt ); ///< "失流",
    lcd_periods  (scrn.elem.periods  ); ///< "时段",
    lcd_feerate  (scrn.elem.feerate  ); ///< "费率",    
    lcd_thismonth(scrn.elem.thismonth); ///< "本月",
    lcd_lastmonth(scrn.elem.lastmonth); ///< mode4.bit5 ? "上月", "上上月" : "上1月", "上2月";
    lcd_lasttime (scrn.elem.lasttime); ///< 上xx次
    lcd_times    (scrn.elem.times); ///< 上xx
    
    
    lcd_assemble (scrn.elem.assemble ); ///< "无功组合方式1 or 2", mode4.bit7 ? "逆时针" : "顺时针";
    lcd_quadrant (scrn.elem.quadrant ); ///< "XX象限",
    lcd_tariff   (scrn.elem.tariff   ); ///< 显示"费率Tx",
    lcd_times    (scrn.elem.times    ); ///< 显示"上XX次",
    
#if LCD_PROPERTY==LCD_SD_ZXW  ||  LCD_PROPERTY==LCD_GW_ZXW 
    lcd_jieti    (scrn.elem.jieti    ); ///< 阶梯
    lcd_dianjia  (scrn.elem.dianjia  ); ///电价
    lcd_Pre_Pay    (scrn.elem.shenyu,scrn.elem.jine);              ///< 显示"预付费类容",
#endif 
    
    //if(Get_Main_Init_Flag() !=  MAIN_INITING) //主任务初始化完成
    lcd_events   ();    //8ms
    
    lcd_update   ();
}
