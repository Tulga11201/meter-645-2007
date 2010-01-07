
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
  u8  bytes:3;  //������ʾ�ֽ�����<=5,���ڼ���ƫ��
  u8  frmt:5;   //��ʽ��
}DIS_FORMAT;

#define MAX_SUB_SCREEN_NUM  32
//������ʾԪ�����Ա�
typedef struct{
  item_t      di;
  u8          subnums;       //��Ԫ����ʾ����
  DIS_FORMAT  fomat[MAX_SUB_SCREEN_NUM];     //����������Ŀ
}DIS_MULT_SCREEN;           //������ʾ��Ŀ�������ñ�

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
                 
  {0x04000106,2,{{3,18},{2,19}}},  //������ ʱ��
  {0x04000107,2,{{3,18},{2,19}}},  //������ ʱ��
  {0x04000108,2,{{3,18},{2,19}}},  //������ ʱ��
  {0x04000109,2,{{3,18},{2,19}}},  //������ ʱ��
   
   
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
  
  {0x10000101,2,{{3,18},{2,21}}},   //������ ʱ����
  {0x10000201,2,{{3,18},{2,21}}},   //������ ʱ����
  
  /*
  {0x0400040B,2,{{4,6},{4,6}}},
  {0x0400040C,2,{{4,6},{4,6}}},
  {0x0400040D,2,{{4,6},{4,6}}},
  
  {0x04800001,8,{{4,6},{4,6},{4,6},{4,6},{4,6},{4,6},{4,6},{4,6}}},
  {0x04800002,8,{{4,6},{4,6},{4,6},{4,6},{4,6},{4,6},{4,6},{4,6}}},
  {0x04800003,8,{{4,6},{4,6},{4,6},{4,6},{4,6},{4,6},{4,6},{4,6}}},
  
    
  {DI_LOSS_VOLT_DATA, 22,{{3,10},{4,13},                              //0x0EAO0000---��ʧѹ�ڼ��ۼ�����
                        {4,12},{4,12},{4,12},{4,12},
                        {4,12},{4,12},{4,12},{4,12},
                        {4,12},{4,12},{4,12},{4,12},
                        {4,12},{4,12},{4,12},{4,12},
                        {4,14},{4,14},{4,14},{4,14}}},
                        
  {DI_LOSS_VOLT_DATA_A,22,{{3,10},{4,13},                            //0x0EAO0001---A��ʧѹ�ڼ��ۼ�����
                        {4,12},{4,12},{4,12},{4,12},
                        {4,12},{4,12},{4,12},{4,12},
                        {4,12},{4,12},{4,12},{4,12},
                        {4,12},{4,12},{4,12},{4,12},
                        {4,14},{4,14},{4,14},{4,14}}},
                        
  {DI_LOSS_VOLT_DATA_B,22,{{3,10},{4,13},                           //0x0EAO0002---B��ʧѹ�ڼ��ۼ�����
                        {4,12},{4,12},{4,12},{4,12},
                        {4,12},{4,12},{4,12},{4,12},
                        {4,12},{4,12},{4,12},{4,12},
                        {4,12},{4,12},{4,12},{4,12},
                        {4,14},{4,14},{4,14},{4,14}}},
                        
  {DI_LOSS_VOLT_DATA_C,22,{{3,10},{4,13},                           //0x0EAO0003---C��ʧѹ�ڼ��ۼ�����
                        {4,12},{4,12},{4,12},{4,12},
                        {4,12},{4,12},{4,12},{4,12},
                        {4,12},{4,12},{4,12},{4,12},
                        {4,12},{4,12},{4,12},{4,12},
                        {4,14},{4,14},{4,14},{4,14}}},
                        
                        
  {DI_LOSS_VOLT_START,2,{{3,4},{3,5}}},                         //0x0EAO0000---���һ��ʧѹ��ʼ����ʱ��
  {DI_LOSS_VOLT_END,  2,{{3,4},{3,5}}},                          //0x0EAO0000---���һ��ʧѹ��������ʱ��
*/
};

#define MAX_SUB_NUM (sizeof(Con_Dis_Muit_Screen)/sizeof(DIS_MULT_SCREEN))




// screen model words.
typedef struct {    
    code_t code;     //Cģʽ�µ���ʾ����-----PUCK��DI    
    code_t user;     //A/Bģʽ�µ���ʾ����-----PUCK,���½�
    u8     dlen;
    u8     ChangeFlag;  //��չ���ݱ�־
    code_t ChangeCode;  //��չ����ID    
} list_t;

// ��ʾ������
list_t vlist;


INT8U Get_Code (scrn_t *temp,PROTO_DI di,const scrn_t *p)
{
  INT8U tempdata,i;
  INT8U ByteFlag;  //0��3��ʾ��ͬ��byte����
  
  tempdata=0;
  ByteFlag=0;
  
  if((GROUP_NO EQ temp->GroupType[0].GroupFlag) &&(GROUP_NO EQ temp->GroupType[1].GroupFlag))
    return 0;
    
  if(di != temp->item)
  {
    for(i=2; i<=2; i--)  //����byte�����־,�Ӹߵ���λ����
    {
      if((BYTE(di,i)!=BYTE(temp->item,i)))  //���ֽڲ���
      {
        if((GROUP_NO!=temp->GroupType[0].GroupFlag)||(GROUP_NO!=temp->GroupType[1].GroupFlag)) //���ֽ�ȷʵ������
        {
          if((i==temp->GroupType[0].BytePos)||(i==temp->GroupType[1].BytePos))  //��ȡ����λ��
          {
            tempdata++;
            if(tempdata>2)   //��������2�����ϵ�DI����
              return  0;
            SET_BIT(ByteFlag,i);
          }
          else   //��λ�����Ǳ�ID
           return  0;
        }
         else   //���ֽڲ��ȣ����������Ǵ�λ��
           return  0;        
      }    
    }
  }
  else
    return 1;
  
  *temp=*p;
  //�޸���ʾԪ��
  for(i=0;i<2;i++)   
  {
    switch(temp->GroupType[i].GroupFlag)  //����ı�־����
    {
      case GROUP_TARIFF:   //����
        if(BYTE(di,temp->GroupType[i].BytePos)>MAX_TARIFF)
          return 0;
        
        if(GET_BIT(ByteFlag,temp->GroupType[i].BytePos))  //���ֽڲ�ͬ����Ҫ�޸���ʾԪ��
        {
          temp->elem.feerate=1;           //��ʾ "����"
          temp->elem.tariff=BYTE(di,temp->GroupType[i].BytePos);         //��ʾ "Txx"
          temp->elem.total=0;
        }
        else
          temp->elem.total=1;      
      break;
      
      case GROUP_SETTLE:  //������
        if(BYTE(di,temp->GroupType[i].BytePos)>MAX_SETTLE)
          return 0;
        
        if(GET_BIT(ByteFlag,temp->GroupType[i].BytePos))  //���ֽڲ�ͬ����Ҫ�޸���ʾԪ��
        {
          temp->elem.lastmonth=1;                                    //��ʾ "����"
          temp->elem.times=BYTE(di,temp->GroupType[i].BytePos);     //��ʾ "xx"
          temp->elem.thismonth=0; 
        }
        else
          temp->elem.thismonth=1;                                       //��ʾ��ǰ���ߵ���
      break; 
      
      case GROUP_PHASE:  //A/B/C/N  ��    
        if(BYTE(di,temp->GroupType[i].BytePos)>MAX_PHASE)
          return 0;
        
        if(GET_BIT(ByteFlag,temp->GroupType[i].BytePos))  //���ֽڲ�ͬ����Ҫ�޸���ʾԪ��
        {
          temp->elem.phase=BYTE(di,temp->GroupType[i].BytePos);         //��ʾ A/B/C/N ��
          temp->elem.total=0;
        }
        else
          temp->elem.total=1;                                           //��ʾ��
      break;
      
      case GROUP_HARMO:     // г������
        if(BYTE(di,temp->GroupType[i].BytePos)>MAX_HARMO)
          return 0;
      break;
      
      case GROUP_TIMES:    // ����ȼ�
        if(BYTE(di,temp->GroupType[i].BytePos)>MAX_PASSW)
          return 0;
        
        if(GET_BIT(ByteFlag,temp->GroupType[i].BytePos))  //���ֽڲ�ͬ����Ҫ�޸���ʾԪ��
        {
          temp->elem.lasttime=1;  //��ʾ"�ϴ�"
          temp->elem.times=BYTE(di,temp->GroupType[i].BytePos);     //��ʾ "xx"
        }
      break;
    }
  }
  //�޸� di
  temp->item=di;
  return 1;
}


u8 Is_Multi_Screen(item_t item)
{
  u16 i;
  
  if(DI_IS_DEMAND(item)) //����
     return 1;
   
  for(i=0;i<MAX_SUB_NUM && i<0xff;i++) //������֧�ֶ��� 256��
  {
    if(item EQ Con_Dis_Muit_Screen[i].di)
    {
     return i;    //����λ��  
    }    
  }  
  
  return 0;  //���Ƕ�����ʾ
}

/***********************************************************************
�������ܣ���ȡ������ҳ����ʾ��λ
��ڣ�1------------ǿ������¼�˲̬�֣����¼��������״̬��sram��0-------����CSֵ�����
���ڣ���
***********************************************************************/
u8 Get_Demand_Unit_Frmt(u8 byte,u8 index)
{
  if(index >2)
    ASSERT_FAILED();

  if(index EQ 1) //����ʱ��:������
    return 18;
  
  if(index EQ 2) //����ʱ��:ʱ��
    return 19;
  
   if(byte >=0x09 && byte <=0x0A)  //�������������
    return 8;
  
  if(byte >=0x03 && byte <=0x08)  //���޹�����
    return 7;
  
  //���й�����
  return 1;
  
}



// ������ item�Ƿ��Ƕ�����ʾ���ǵĻ����ط�0�����޸���Ӧ������Ϣ
u8 Judge_Modi_Sub_Screen(item_t item,u8 proc) 
{
  //���� item��Ӧ����ʾ��Ŀ���Ƿ��Ƕ�����ʾ�����Ƕ�����ʾ�������κθĶ�,�� vlist.SubCurs=0
  //���Ҫ�� ID ������Ԫ�ظ�����ƫ�ƣ�ÿ����Ԫ�ص����ݸ�ʽ������

  u8 pos,flag;
  u16 i;  
    
  pos=Is_Multi_Screen(item);
 
  if(pos EQ 0)  //������
  {
    Sub_Vlist.exist=0;
    Sub_Vlist.subindex=0;
    Sub_Vlist.fmtindex=0; 
    Sub_Vlist.offset=0; 
    return PROC_SWITCH;
  }
  
  //������ʾ��  
  if(Sub_Vlist.subindex>=Con_Dis_Muit_Screen[pos].subnums  \
                          || Sub_Vlist.subindex>=MAX_SUB_SCREEN_NUM || pos>=MAX_SUB_NUM)
  {
    Sub_Vlist.subindex=0;
    ASSERT_FAILED();
  }
  
  //��� item����ȣ���ʼ�� Sub_Vlist
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
  
  if(DI_IS_DEMAND(item))  //����������Ļ����϶࣬����������
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

// ������ item�Ƿ��Ƕ�����ʾ���ǵĻ����ط�0�����޸���Ӧ������Ϣ
void Get_Sub_Screen_Info(item_t item,u8 subindex) 
{
  //���� item��Ӧ����ʾ��Ŀ���Ƿ��Ƕ�����ʾ�����Ƕ�����ʾ�������κθĶ�,�� vlist.SubCurs=0
  //���Ҫ�� ID ������Ԫ�ظ�����ƫ�ƣ�ÿ����Ԫ�ص����ݸ�ʽ������

  u8 pos;
  u16 i;  
    
  pos=Is_Multi_Screen(item);
 
  if(pos EQ 0)  //������
  {
    Sub_Vlist.exist=0;
    Sub_Vlist.subindex=0;
    Sub_Vlist.fmtindex=0; 
    Sub_Vlist.offset=0; 
    return ;
  }
  
  Sub_Vlist.exist=MULIT_EXSIT;
  Sub_Vlist.subindex=subindex%Con_Dis_Muit_Screen[pos].subnums;  
  //������ʾ��  
  if(Sub_Vlist.subindex>=Con_Dis_Muit_Screen[pos].subnums  \
                          || Sub_Vlist.subindex>=MAX_SUB_SCREEN_NUM || pos>=MAX_SUB_NUM)
  {
    Sub_Vlist.subindex=0;
    ASSERT_FAILED();
  }
  
  if(DI_IS_DEMAND(item))  //����������Ļ����϶࣬����������
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

//Cģʽ�£���ȡ����ʾ����,�޸İ�ť����ƫ��
void Judge_Modi_C_Offset(u8 pos,u8 proc) 
{
  //���� item��Ӧ����ʾ��Ŀ���Ƿ��Ƕ�����ʾ�����Ƕ�����ʾ�������κθĶ�,�� vlist.SubCurs=0
  //���Ҫ�� ID ������Ԫ�ظ�����ƫ�ƣ�ÿ����Ԫ�ص����ݸ�ʽ������
  if(pos EQ 0)
    return ; 
  
  //����������ʾ��  
  if(Sub_Vlist.subindex>=Con_Dis_Muit_Screen[pos].subnums  || Sub_Vlist.subindex>=MAX_SUB_SCREEN_NUM || pos>=MAX_SUB_NUM)
  {
    Sub_Vlist.subindex=0;
    ASSERT_FAILED();
  }
  
  if(proc EQ PROC_ADD)  //+
  {
    Sub_Vlist.subindex++;
    if(Sub_Vlist.subindex>=Con_Dis_Muit_Screen[pos].subnums)  //��ת
    {
      Sub_Vlist.subindex=0;  //�л�����С����
    }
    return ;
  }
  if(proc EQ PROC_SUB)  //+
  {
    Sub_Vlist.subindex--;
    if(Sub_Vlist.subindex==0 || Sub_Vlist.subindex>=Con_Dis_Muit_Screen[pos].subnums)   //��ת
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
�������ܣ���ȡ��Ӧģʽ��A����B���µľ�����ʾ��Ŀ
��ڣ�
     item-----��ʾ��Ŀ��ͬ645��ʶ;offs-----����Ŀ�µĺ�����Ŀ����ƫ��
���أ�
********************************************************************************/
/********************************************************************************
void getlist (item_t item, offs_t offs, u8 proc) 
{
  INT16U Len;
  list_t list = {0, 0, 0}; //��ʼ��Ϊ0����δ���������ݵģ�����ʾ�ܵ��� 
  u8 flag;
  offs_t offtemp;
  
  if(((INT32U)(item&0xFFFF00FF))!=0x04040001)  //ȡ���ǷǷ�����
  {
    ASSERT_FAILED(); 
    return ;
  }
  
  if(Sub_Vlist.lastproc!=proc && proc!=PROC_NONE)
  {
    if(proc EQ PROC_ADD)  //�ϴ��ǣ�
    {
      dispoffset+=2;
       if(Sub_Vlist.exist EQ MULIT_EXSIT)
        dispoffset--;
      Refresh_Curr_Offset();
      
    }
    if(proc EQ PROC_SUB) //�ϴ��ǣ��������Ǽ�
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
  Len=Read_Storage_Data(item+offtemp,&list,&list,sizeof(list));  //�޸�ƫ�ƣ���ȡ���µ�ID
  if(0==Len)
    ASSERT_FAILED();
  
  flag=Judge_Modi_Sub_Screen(list.code,proc);
  if(flag EQ PROC_SUB ||flag EQ PROC_ADD) //�����л�
  {
    Modi_AB_Offset(flag);    
  }
  
  
  //offs++;  //ƫ��0�ɵ�
  list.user=((offtemp+1)/10)*16+((offtemp+1)%10);         //��ʾ������ƫ�����:BCD
  list.code=Modi_Item(list.code);  //�޸Ĳ����ݵ�ID��������ʾ
  
  vlist=list;
  vlist.dlen = 2;
  
  if(flag EQ PROC_SWITCH)  ///�����л�
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
�������ܣ���ȡ��Ӧģʽ��A����B���µľ�����ʾ��Ŀ
��ڣ�
     item-----��ʾ��Ŀ��ͬ645��ʶ;offs-----����Ŀ�µĺ�����Ŀ����ƫ��
���أ�
********************************************************************************/

list_t getlist (item_t item, offs_t offs) 
{
  INT16U Len;
  list_t list = {0, 0, 0, 0, 0}; //��ʼ��Ϊ0����δ���������ݵģ�����ʾ�ܵ��� 
  u8 temp[5];
  u8 subindex;


  if(((INT32U)(item&0xFFFF00FF))!=0x04040001)  //ȡ���ǷǷ�����
  {
    ASSERT_FAILED(); 
    return list;
  }
  
  Len=Read_Storage_Data(item+offs,temp,temp,sizeof(temp));  //�޸�ƫ�ƣ���ȡ���µ�ID  
  if(0==Len)
    ASSERT_FAILED();  
  
#ifdef  DIS_ITEM_BYTE_4  
  mem_cpy((void *)(&list.code),temp,sizeof(list.code),(void *)(&list.code),sizeof(list.code));
  subindex=BYTE(list.code,0)&0x0f;
  list.code=list.code>>0x04;
#else  
  mem_cpy((void *)(&list.code),temp+1,sizeof(list.code),(void *)(&list.code),sizeof(list.code));
  subindex=temp[0]&0xff;  //�������1���ֽ�
#endif
 

  
  Get_Sub_Screen_Info(list.code,subindex);  
  
  //list.user=((offs+1)/10)*16+((offs+1)%10);         //��ʾ������ƫ�����:BCD
  list.user=subindex;
  list.ChangeCode=list.code;
  list.ChangeFlag=Modi_Item(list.code,&list.code);  //�޸Ĳ����ݵ�ID��������ʾ
  return list;
}

/********************************************************************************
PUCK:
�������ܣ���ȡ��Ӧģʽ��A����B���µľ�����ʾ��Ŀ
��ڣ�
     item-----��ʾ��Ŀ��ͬ645��ʶ;offs-----����Ŀ�µĺ�����Ŀ����ƫ��
���أ�
********************************************************************************/
void Init_DisItem (void) 
{
  vlist.code=DI_DATE_WEEK;
  vlist.user=0x01;         //��ʾ������ƫ�����:BCD
  vlist.ChangeFlag=0;
  vlist.dlen=2;
}
/********************************************************************************
PUCK:
�������ܣ������޸ĵ�DIֵ������Cģʽ�µ���ʾcode
��ڣ�
���أ�
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
�������ܣ���λ����ʾ���ݣ�ʵ��ֻ����A/Bģʽ
��ڣ�
     type-----ģʽ����;offs-----��ģʽ����ʾ����Ŀ˳��
���أ�
********************************************************************************/
void lcdshow (u8 type, offs_t offs) 
{
    switch (type) 
    {
        case modeA: //Aģʽ�£�����645��ʶ����ƫ�ƻ�ȡ��ʾԪ��-----------PUCK
        {
            vlist=getlist(ITEMMODEA, offs % MODE_A_NUM);
            vlist.dlen = 2;
            break;
        }
        case modeB: //Bģʽ�£�����645��ʶ����ƫ�ƻ�ȡ��ʾԪ��-----------PUCK
        {
            vlist=getlist(ITEMMODEB, offs % MODE_B_NUM);
            vlist.dlen = 2;
            break;
        }
        default :   //Cģʽ�£����ݱ��ƫ�ƻ�ȡ��ʾԪ��-----------PUCK
        {
            vlist.user = table[offs % MAXCOUNT].item; 
            vlist.dlen = MAXBITS;
            break;
        }
    }
}
/********************************************************************************
PUCK:
�������ܣ�����ģʽ����,��ʾ���룬��ȡ��ʾ��Ϣ��
��ڣ�
     type-----ģʽ����;code-----��ģʽ����ʾ����Ŀ˳��
���أ�
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
�������ܣ���������ʾ���ݣ�ʵ��Cģʽ��ʾ
��ڣ�
     type-----ģʽ����;code-----��ģʽ����ʾ����Ŀ˳��
���أ�
********************************************************************************/
void display(u8 type, code_t code) 
{
    vlist.user = code;
    vlist.ChangeCode = code;
    vlist.code=code;
    vlist.ChangeFlag=Modi_Item(vlist.code,&vlist.code);  //�޸Ĳ����ݵ�ID��������ʾ
    vlist.dlen = MAXBITS+1;
}
/********************************************************************************
PUCK:
�������ܣ��޸�������ʾԪ��
��ڣ�
���أ�
********************************************************************************/
void Modi_Demand_DIs_Item(scrn_t *scrn) 
{
    if((Sub_Vlist.subindex-1)%3 EQ 0  || (Sub_Vlist.subindex-2)%3 EQ 0) //����ʱ��
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
�������ܣ���ȡ��Ļ��ʾ��Ϣ������ʾ
��ڣ�
     type-----ģʽ����;curs-----���λ��
���أ�
********************************************************************************/
void screen (u8 type, curs_t curs) 
{
      const scrn_t* p;
  //�ڴ�ǰ��vlist����Ϣ�Ѿ�����-----PUCK
    static scrn_t scrn={0xffffffff,{{GROUP_NO,0},{GROUP_NO,0}},"",{0}};   //��Ϊ0����֤��һ�ξ��ܸ��£���Ϊ0x000000�п��ܵ�һ�ξ���0---PUCK
    if (scrn.item != vlist.code)     //����������������A/Bģʽ��ΪЭ��DI���룬Cģʽ�»�����ʾ����
    {
        for (p=&table[0];p!=&table[MAXCOUNT];++p) 
        {
            scrn=*p;        
            {
              if(scrn.item EQ vlist.code) //���Ǵ�ID
               break;
              
              if(BYTE(scrn.item,3)==BYTE(vlist.code,3))  //���Ǵ�ID��������ֽڱ�����ȣ������ڴ����в��ң�
              {
                if(Get_Code(&scrn,vlist.code,p))  //��������������,�޸���scrn��ֵ
                  break;
              }
            }
        }
    }
    if(Sub_Vlist.exist EQ MULIT_EXSIT && DI_IS_DEMAND(scrn.item)) //������ʾ��ʱ�䣬��ʾ��λ����취
    {
      if((Sub_Vlist.subindex-1)%3 EQ 0  || (Sub_Vlist.subindex-2)%3 EQ 0) //����ʱ��
        scrn.elem.time=1;
      else
        scrn.elem.time=0;
    }
    
    if(p==&table[MAXCOUNT]) //�Ҳ�����ʾ�Ĵ���,ֻ��ʾ���룬�¼�����������ʾ-------PUCK
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
    lcd_mode     (type);                ///A/B/C 3��ģʽ
    lcd_total    (scrn.elem.total    ); ///< "��",
    lcd_phase    (scrn.elem.phase    ); ///< "A/B/C��",
    lcd_voltage  (scrn.elem.voltage  ); ///< "��ѹ",
    lcd_current  (scrn.elem.current  ); ///< "����",
    lcd_positive (scrn.elem.positive ); ///< mode4.bit4 ? "����" : "����";
    lcd_negative (scrn.elem.negative ); ///< mode4.bit4 ? "���" : "����";
    lcd_reactive (scrn.elem.reactive ); ///< "�޹�",
    lcd_active   (scrn.elem.active   ); ///< "�й�",
    lcd_power    (scrn.elem.power    ); ///< "����",
    lcd_factor   (scrn.elem.factor   ); ///< "����",
    lcd_angle    (scrn.elem.angle    ); ///< "���",
    lcd_energy   (scrn.elem.energy   ); ///< "����",
    lcd_demand   (scrn.elem.demand   ); ///< "����",
    lcd_time     (scrn.elem.time     ); ///< "ʱ��",
    lcd_charge   (scrn.elem.charge   ); ///< "���",
    lcd_lostvolt (scrn.elem.lostvolt ); ///< "ʧѹ",
    lcd_lostcurt (scrn.elem.lostcurt ); ///< "ʧ��",
    lcd_periods  (scrn.elem.periods  ); ///< "ʱ��",
    lcd_feerate  (scrn.elem.feerate  ); ///< "����",    
    lcd_thismonth(scrn.elem.thismonth); ///< "����",
    lcd_lastmonth(scrn.elem.lastmonth); ///< mode4.bit5 ? "����", "������" : "��1��", "��2��";
    lcd_lasttime (scrn.elem.lasttime); ///< ��xx��
    lcd_times    (scrn.elem.times); ///< ��xx
    
    
    lcd_assemble (scrn.elem.assemble ); ///< "�޹���Ϸ�ʽ1 or 2", mode4.bit7 ? "��ʱ��" : "˳ʱ��";
    lcd_quadrant (scrn.elem.quadrant ); ///< "XX����",
    lcd_tariff   (scrn.elem.tariff   ); ///< ��ʾ"����Tx",
    lcd_times    (scrn.elem.times    ); ///< ��ʾ"��XX��",
    
#if LCD_PROPERTY==LCD_SD_ZXW  ||  LCD_PROPERTY==LCD_GW_ZXW 
    lcd_jieti    (scrn.elem.jieti    ); ///< ����
    lcd_dianjia  (scrn.elem.dianjia  ); ///���
    lcd_Pre_Pay    (scrn.elem.shenyu,scrn.elem.jine);              ///< ��ʾ"Ԥ��������",
#endif 
    
    //if(Get_Main_Init_Flag() !=  MAIN_INITING) //�������ʼ�����
    lcd_events   ();    //8ms
    
    lcd_update   ();
}
