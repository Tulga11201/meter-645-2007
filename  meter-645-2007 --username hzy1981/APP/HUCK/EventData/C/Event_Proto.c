#define EVENT_PROTO_C
#include "Includes.h"

INT16U Event_Sub_Item_Len0[]={5,2,4,4, 4,4                                                                                                                            };//0--�����͹���   23    
INT16U Event_Sub_Item_Len1[]={5,2,4,4, 4,4                                                                                                                            };//1--����͹���   23
INT16U Event_Sub_Item_Len2[]={6,6                                                                                                                                     };//2--���1��ʧѹ����ʱ���¼  12
INT16U Event_Sub_Item_Len3[]={6,4,4,4, 4,4,4,4   ,4,2,3,3, 3,2,4,4    ,4,4,2,3, 3,3,2,4     ,4,4,4,2, 3,3,3,2    ,4,4,4,4, 6,4,4,4    ,4,4,4,4, 4,4,4,4    ,4,4,4,4,4 };//3--ʧѹ��Ƿѹ����ѹ ���� 195 
INT16U Event_Sub_Item_Len4[]={6,4,4,4, 4,4,4,4   ,4,4,4,4, 4,4,4,4    ,4,6,4,4, 4,4,4,4     ,4,4,4,4, 4,4,4,4    ,4,4 };//4--��ѹ�����򡢵���������     ��������    ����  140
INT16U Event_Sub_Item_Len5[]={6,4,4,4, 4,4,4,4   ,4,4,4,4, 4,4,4,4    ,4,3,6,4, 4,4,4,4     ,4,4,4,4, 4,4,4,4    ,4,4,4                                               };//5��ѹ��ƽ��  143
INT16U Event_Sub_Item_Len6[]={6,4,4,4, 4,4,4,4   ,4,2,3,3, 3,2,4,4    ,4,4,2,3, 3,3,2,4     ,4,4,4,2, 3,3,3,2    ,6,4,4,4, 4,4,4,4    ,4,4,4,4, 4,4,4,4    ,4         };//6��ʧ��������������  179
INT16U Event_Sub_Item_Len7[]={6,4,4,4, 4,4,4,4                                                                                                                        };//7��բ  34
INT16U Event_Sub_Item_Len8[]={6,4,4,4, 4,4,4,4                                                                                                                        };//8��բ   34 
INT16U Event_Sub_Item_Len9[]={6,4,4,4, 4,6,4,4    ,4,4                                                                                                                };//9--  �ܹ������������� 44                             
//����Ϊ�ɵ�645Э�飺      
INT16U Event_Sub_Item_Len10[]={6+3+6                                                               };//10--ȫʧѹ  030500
INT16U Event_Sub_Item_Len11[]={6+6                                                                 };//11--������Դʧ�硢���Ƿѹ  //               0x030600    0X0E1400                                                                                           
INT16U Event_Sub_Item_Len12[]={6+6+3+5};//12--�����й���������//--�����й��������� //��һ�����޹���������//�ڶ������޹���������//���������޹��������� //���������޹���������0x031201 0x031202 0x031204 0x031203 0x031205 0x031206
INT16U Event_Sub_Item_Len13[]={6+4+40                                                              };//13--��̼�¼  0X033000
INT16U Event_Sub_Item_Len14[]={6+4+4+4+ 4+4+4+4   +4+4+4+4+ 4+4+4+4    +4+4+4+4+ 4+4+4+4     +4+4  };//14--����� 0   0x033001
INT16U Event_Sub_Item_Len15[]={8+8+8+8+ 8+8+8+8   +8+8+8+8+ 8+8+8+8    +8+8+8+8+ 8+8+8+8     +8+8  }; //15--������0  0x033002   ǰ������8+8  Ӧ��Ϊ6+4
INT16U Event_Sub_Item_Len16[]={6+4+4                                                               }; //16--�¼���0     0x033003
INT16U Event_Sub_Item_Len17[]={4+6+6                                                               };//17--Уʱ         0x033004
INT16U Event_Sub_Item_Len18[]={6+4+42+42+ 42+42+42+42   +42+42+42+42+ 42+42+42+42    +42+42        };//18--ʱ�α���  0x033005
INT16U Event_Sub_Item_Len19[]={6+4+42+42                                                           }; //19--ʱ������     0x033006            
INT16U Event_Sub_Item_Len20[]={6+4+(MAX_YEAR_HOLIDAYS*4)                                           };//20--�ڼ��ձ��0x033008       
INT16U Event_Sub_Item_Len21[]={6+4+1  };//21--�й���Ϸ�ʽ//--�޹���Ϸ�ʽ1//--�޹���Ϸ�ʽ2//--�����ձ�� //0x033009  0x03300A    0x03300B      0x033007      
INT16U Event_Sub_Item_Len22[]={6+4+2+2+ 2                                                          };//22--�����ձ��   0x03300C                        
INT16U Event_Sub_Item_Len23[]={6+6+4+4+ 4+4+4+4   +4+4+4+4 +4+4                                    };//23--����ǡ�����ť  0x03300D    0x03300E 
INT16U Event_Sub_Item_Len24[]={6+6+3+3                                                             };//24--����������//��һ�� û��������Event_ID_Info  �е���
INT16U Event_Sub_Item_Len25[]={6+3+3                                                               };//25--��������բ  ��һ�� û��������Event_ID_Info  �е���
INT16U Event_Sub_Item_Len26[]={12                                                                  };//26--���� //0x031100
INT16U Event_Sub_Item_Len27[]={6+4+4+4+ 4+4+4+4 +4                                                 };//27--Զ����բ  ��բ//0X0E1D00  0X0E1E00 
INT16U Event_Sub_Item_Len28[]={5+5+1                                                               };//28--�ϵ�ʱ���Һ�����ʱ����  У�� 0X0E1C00      0X0E3010 
INT16U Event_Sub_Item_Len29[]={6                                                                   };//29--��λ    0X0E1800
INT16U Event_Sub_Item_Len30[]={5+1                                                                 };//30�� Eeprom����  0X0E1A00
INT16U Event_Sub_Item_Len31[]={5+36+36+1                                                           }; //31--���ó�ʼ����   0X0E3011
INT16U Event_Sub_Item_Len32[]={6+6+2+4+ 4+4+4+4     +4+4+4+4 +4+4+4+4+     4+4+4                   };//32--������ƽ�� 030A00
INT16U Event_Sub_Item_Len33[]={3+3+3+3+ 3+2+4+2+ 4}; //33���£���ѹ�ϸ���ͳ������031000 A���ѹ�ϸ���ͳ������031001 B���ѹ�ϸ���ͳ������031002 C���ѹ�ϸ���ͳ������031003
INT16U Event_Sub_Item_Len34[]={6+6                                                                 };//34ʱ�ӵ��Ƿѹ  0X0E1500  
INT16U Event_Sub_Item_Len35[]={6+6+3+3                                                             };//35���ر���   0X0E1600 
INT16U Event_Sub_Item_Len36[]={6+3+3                                                               };//36������բ��¼  0X0E1700     
INT16U Event_Sub_Item_Len37[]={5+4*(MAX_RATES+1)+4*(MAX_RATES+1)+4*(MAX_RATES+1)+4*(MAX_RATES+1)+4*(MAX_RATES+1)+4*(MAX_RATES+1)+4*(MAX_RATES+1) +4*(MAX_RATES+1)+ 8*(MAX_RATES+1)+8*(MAX_RATES+1)+12+12 };//26--�������ݡ�ʱ�����л���ʱ�α��л�        ?? 

 //�������ݳ����һ���� ����Ϊ�ϵ�645Э���ж���Ļ��Լ�������¼�
CONST S_Event_PDI_Info_Quck Event_PDI_Info[]=
{                                     
 {0x03320100, &Event_Sub_Item_Len0[0],S_NUM(Event_Sub_Item_Len0)},//0--�����͹���   23
 {0x03330100, &Event_Sub_Item_Len1[0],S_NUM(Event_Sub_Item_Len1)}, //1--����͹���   23
 {0x10000100, &Event_Sub_Item_Len2[0],S_NUM(Event_Sub_Item_Len2)}, //���1��ʧѹ����ʱ���¼ 12
 {0x10010100, &Event_Sub_Item_Len3[0],S_NUM(Event_Sub_Item_Len3)},//a--ʧѹ 195
 {0x10020100, &Event_Sub_Item_Len3[0],S_NUM(Event_Sub_Item_Len3)},//b--ʧѹ 195
 {0x10030100, &Event_Sub_Item_Len3[0],S_NUM(Event_Sub_Item_Len3)},//c--ʧѹ 195
 {0x11010100, &Event_Sub_Item_Len3[0],S_NUM(Event_Sub_Item_Len3)},//a--Ƿѹ�� 195
 {0x11020100, &Event_Sub_Item_Len3[0],S_NUM(Event_Sub_Item_Len3)},//b--Ƿѹ�� 195
 {0x11030100, &Event_Sub_Item_Len3[0],S_NUM(Event_Sub_Item_Len3)}, //c--Ƿѹ�� 195
 {0x12010100, &Event_Sub_Item_Len3[0],S_NUM(Event_Sub_Item_Len3)},//a���ѹ  195
 {0x12020100, &Event_Sub_Item_Len3[0],S_NUM(Event_Sub_Item_Len3)},//b���ѹ  195
 {0x12030100, &Event_Sub_Item_Len3[0],S_NUM(Event_Sub_Item_Len3)},//c���ѹ   195
 {0x13010100, &Event_Sub_Item_Len3[0],S_NUM(Event_Sub_Item_Len3)},//a���� 195
 {0x13020100, &Event_Sub_Item_Len3[0],S_NUM(Event_Sub_Item_Len3)}, //b���� 195
 {0x13030100, &Event_Sub_Item_Len3[0],S_NUM(Event_Sub_Item_Len3)}, //c-���� 195
 {0x14000100, &Event_Sub_Item_Len4[0],S_NUM(Event_Sub_Item_Len4)}, //��ѹ������  140  
 {0x15000100, &Event_Sub_Item_Len4[0],S_NUM(Event_Sub_Item_Len4)}, //����������     140
 {0x1B010100, &Event_Sub_Item_Len4[0],S_NUM(Event_Sub_Item_Len4)}, // a��������      140
 {0x1B020100, &Event_Sub_Item_Len4[0],S_NUM(Event_Sub_Item_Len4)}, // b  ��������   140
 {0x1B030100, &Event_Sub_Item_Len4[0],S_NUM(Event_Sub_Item_Len4)}, //  c��������      140
 {0x1C010100, &Event_Sub_Item_Len4[0],S_NUM(Event_Sub_Item_Len4)}, //a ����  140
 {0x1C020100, &Event_Sub_Item_Len4[0],S_NUM(Event_Sub_Item_Len4)}, //b  ����  140
 {0x1C030100, &Event_Sub_Item_Len4[0],S_NUM(Event_Sub_Item_Len4)}, //c ���� 140  
 {0x16000100, &Event_Sub_Item_Len5[0],S_NUM(Event_Sub_Item_Len5)}, //��ѹ��ƽ�� 142
 {0x17000100, &Event_Sub_Item_Len5[0],S_NUM(Event_Sub_Item_Len5)}, //������ƽ�� 142 
 {0x18010100, &Event_Sub_Item_Len6[0],S_NUM(Event_Sub_Item_Len6)},//aʧ���� 179
 {0x19010100, &Event_Sub_Item_Len6[0],S_NUM(Event_Sub_Item_Len6)},//a������ 179
 {0x1A010100, &Event_Sub_Item_Len6[0],S_NUM(Event_Sub_Item_Len6)},//a����  179
 {0x18020100, &Event_Sub_Item_Len6[0],S_NUM(Event_Sub_Item_Len6)},//bʧ��179
 {0x19020100, &Event_Sub_Item_Len6[0],S_NUM(Event_Sub_Item_Len6)},//b����179
 {0x1A020100, &Event_Sub_Item_Len6[0],S_NUM(Event_Sub_Item_Len6)},//b����  179
 {0x18030100, &Event_Sub_Item_Len6[0],S_NUM(Event_Sub_Item_Len6)},//cʧ����  179
 {0x19030100, &Event_Sub_Item_Len6[0],S_NUM(Event_Sub_Item_Len6)},//c������179
 {0x1A030100, &Event_Sub_Item_Len6[0],S_NUM(Event_Sub_Item_Len6)},//c����  179
 {0x1D000100, &Event_Sub_Item_Len7[0],S_NUM(Event_Sub_Item_Len7)},//��բ 34
 {0x1E000100, &Event_Sub_Item_Len8[0],S_NUM(Event_Sub_Item_Len8)},//��բ 34
 {0x1F000100, &Event_Sub_Item_Len9[0],S_NUM(Event_Sub_Item_Len9)},//�ܹ�������������  44
 //�������ݳ����һ���� ����Ϊ�ϵ�645Э���ж���Ļ��Լ�������¼�
 {0x03050000,&Event_Sub_Item_Len10[0],S_NUM(Event_Sub_Item_Len10)},//1--ȫʧѹ   
 {0x03060000,&Event_Sub_Item_Len11[0],S_NUM(Event_Sub_Item_Len11)},//4--������Դʧ�硢
 {0x0E140000,&Event_Sub_Item_Len11[0],S_NUM(Event_Sub_Item_Len11)},//���Ƿѹ                                                                                                    
 {0x03120100,&Event_Sub_Item_Len12[0],S_NUM(Event_Sub_Item_Len12)},//5--�����й���������  
 {0x03120200,&Event_Sub_Item_Len12[0],S_NUM(Event_Sub_Item_Len12)},//6--�����й���������
 {0x03120300,&Event_Sub_Item_Len12[0],S_NUM(Event_Sub_Item_Len12)},//9--��һ�����޹���������
 {0x03120400,&Event_Sub_Item_Len12[0],S_NUM(Event_Sub_Item_Len12)},///10--�ڶ������޹���������
 {0x03120500,&Event_Sub_Item_Len12[0],S_NUM(Event_Sub_Item_Len12)},//11--���������޹���������
 {0x03120600,&Event_Sub_Item_Len12[0],S_NUM(Event_Sub_Item_Len12)},//8-- ���������޹��������� 
 {0x03300000,&Event_Sub_Item_Len13[0],S_NUM(Event_Sub_Item_Len13)},//12--��̼�¼
 {0x03300100,&Event_Sub_Item_Len14[0],S_NUM(Event_Sub_Item_Len14)},//13--�����0   
 {0x03300200,&Event_Sub_Item_Len15[0],S_NUM(Event_Sub_Item_Len15)}, //14--������0  
 {0x03300300,&Event_Sub_Item_Len16[0],S_NUM(Event_Sub_Item_Len16)}, //15--�¼���0     
 {0x03300400,&Event_Sub_Item_Len17[0],S_NUM(Event_Sub_Item_Len17)},//16--Уʱ         
 {0x03300500,&Event_Sub_Item_Len18[0],S_NUM(Event_Sub_Item_Len18)},//17--ʱ�α���  
 {0x03300600,&Event_Sub_Item_Len19[0],S_NUM(Event_Sub_Item_Len19)}, //18--ʱ������                 
 {0x03300800,&Event_Sub_Item_Len20[0],S_NUM(Event_Sub_Item_Len20)},//20--�ڼ��ձ��
 {0x03300900,&Event_Sub_Item_Len21[0],S_NUM(Event_Sub_Item_Len21)},//21--�й���Ϸ�ʽ
 {0x03300A00,&Event_Sub_Item_Len21[0],S_NUM(Event_Sub_Item_Len21)},//22--�޹���Ϸ�ʽ1
 {0x03300B00,&Event_Sub_Item_Len21[0],S_NUM(Event_Sub_Item_Len21)},//23--�޹���Ϸ�ʽ2
 {0x03300700,&Event_Sub_Item_Len21[0],S_NUM(Event_Sub_Item_Len21)},//19--�����ձ��
 {0x03300C00,&Event_Sub_Item_Len22[0],S_NUM(Event_Sub_Item_Len22)},//24--�����ձ��    
 {0x03300D00,&Event_Sub_Item_Len23[0],S_NUM(Event_Sub_Item_Len23)}, //25--�������
 {0x03300E00,&Event_Sub_Item_Len23[0],S_NUM(Event_Sub_Item_Len23)}, //25--������ť  
 {0x03110000,&Event_Sub_Item_Len26[0],S_NUM(Event_Sub_Item_Len26)},//29--���� //
 {0x0E1D0000,&Event_Sub_Item_Len27[0],S_NUM(Event_Sub_Item_Len27)},//30--Զ����բ  
 {0x0E1E0000,&Event_Sub_Item_Len27[0],S_NUM(Event_Sub_Item_Len27)},//��բ
 {0x0E1C0000,&Event_Sub_Item_Len28[0],S_NUM(Event_Sub_Item_Len28)},//31--�ϵ�ʱ����
 {0x0E301000,&Event_Sub_Item_Len28[0],S_NUM(Event_Sub_Item_Len28)},//У��
 {0x0E180000,&Event_Sub_Item_Len29[0],S_NUM(Event_Sub_Item_Len29)},//32--��λ    
 {0x0E1A0000,&Event_Sub_Item_Len30[0],S_NUM(Event_Sub_Item_Len30)},// Eeprom�����  
 {0x0E301100,&Event_Sub_Item_Len31[0],S_NUM(Event_Sub_Item_Len31)}, //34--���ó�ʼ����   
 {0x030A0000,&Event_Sub_Item_Len32[0],S_NUM(Event_Sub_Item_Len32)},//38--������ƽ�� 
 {0x03100000,&Event_Sub_Item_Len33[0],S_NUM(Event_Sub_Item_Len33)}, //���£���ѹ�ϸ���ͳ������
 {0x03100100,&Event_Sub_Item_Len33[0],S_NUM(Event_Sub_Item_Len33)}, //���£�A���ѹ�ϸ���ͳ������
 {0x03100200,&Event_Sub_Item_Len33[0],S_NUM(Event_Sub_Item_Len33)}, //���£�B���ѹ�ϸ���ͳ������
 {0x03100300,&Event_Sub_Item_Len33[0],S_NUM(Event_Sub_Item_Len33)}, //���£�C���ѹ�ϸ���ͳ������
 {0x0E150000,&Event_Sub_Item_Len34[0],S_NUM(Event_Sub_Item_Len34)},//ʱ�ӵ��Ƿѹ    
 {0x0E160000,&Event_Sub_Item_Len35[0],S_NUM(Event_Sub_Item_Len35)},//���ر���    
 {0x0E170000,&Event_Sub_Item_Len36[0],S_NUM(Event_Sub_Item_Len36)},//������բ��¼   
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
    if((PDI & 0xFFFF0000) EQ (Event_PDI_Info[i].PDI & 0xFFFF0000)) //Э���ʶ���¼�Э���ʶǰ2�ֽ���ͬ
    {
      Index0 = ((Event_PDI_Info[i].PDI >> 8) & 0xFF);
      Index1 = ((PDI >> 8) & 0xFF);
      
      if(Index1 EQ 0xFF) //��Ҫ��ȡ���������¼�������Ŀ
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
    if((PDI & 0xFFFF0000) EQ (Event_PDI_Info[i].PDI & 0xFFFF0000)) //Э���ʶ���¼�Э���ʶǰ2�ֽ���ͬ
    {
      Index0 = ((Event_PDI_Info[i].PDI >> 8) & 0xFF);
      Index1 = ((PDI >> 8) & 0xFF);
      
      if(Index1 EQ 0xFF) //��Ҫ��ȡ���������¼�������Ŀ
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
           
//��ȡ�Ƚϴ���¼����ݣ�������һ֡�ڴ�����ɵĻ�����Ҫ��֡
INT16U Get_Spec_Event_Sparate_Proto_Data(STORA_DI SDI, INT8U *pDst, INT8U *pDst_Start, INT16U DstLen, INT8U *pFlag)
{
  static S_Int16U Off = {CHK_BYTE, 1, CHK_BYTE};//�¼��ĵ�һ���ֽ�Ϊ����������־������Ҫ��ȡ�������ƫ��Ϊ1
  static STORA_DI SDI_Bak;
  INT16U RD_Len, Len;
  
  *pFlag = 0; //��������������
  if((SDI & 0x1FFFFF00) EQ 0x03300500 && (SDI & 0xFF) > 0)
  {
    *pFlag = 1;
    
    Frame_Ack_Info.Follow_Flag = 0;//��ʼ��Ϊû�к�������
    
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
    
    if(Len EQ 0 || Off.Var >= Len)//Off.Var��ʾ����Ӧ�ö�ȡ��ƫ��
      return 0;
    
    if(Off.Var EQ 1)
      RD_Len = 178;
    else
      RD_Len = (Len - Off.Var) < 168? (Len - Off.Var):168;

    mem_cpy(pDst, (INT8U *)Pub_Buf0 + Off.Var, RD_Len, pDst_Start, DstLen);
    Off.Var += RD_Len;
    
    if(Len > Off.Var)
      Frame_Ack_Info.Follow_Flag = 1;//�к�������
    else
      Frame_Ack_Info.Follow_Flag = 0;
      
    return RD_Len;
  }

  return 0;  
}

//��ȡĳ��PDI��Ӧ���¼���Э��ĵ�һ��PDI
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

//��ȡ�¼���¼������
//DI��ʾ�¼���¼�ı�ʶ��
//pDst��ʾĿ�껺����
//pDst_Start��ʾĿ�껺��������ʼ
//DstLen��pDst_Startһ���޶�pDst�ͷ��س���
//pErr��ʾ����Ϊ0ʱ��Ӧ��ԭ�������NO_ERR��ʾ��DI����һ���¼�DI
//����ֵΪ�����ı������ݳ���
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
  
  //����¼��ĵ�һ��DI
  TempPDI = Get_Event_Separate_Start_PDI(PDI);
  
  //if((PDI & 0x0000FF00) > 0) 
    //PDI = ((PDI & 0xFFFF00FF) | 0x00000100); //ת��Ϊ���¼��ĵ�һ��������,�������ֽ����Ϊ0����Ȼ��0�����>1תΪ1
  if(TempPDI != NULL_4BYTES)
    PDI = ((TempPDI & 0xFFFFFF00) | (PDI & 0xFF));
  else
    ASSERT_FAILED();
  
  //��ȡ���ݵ�Index
  i = Get_Event_Separate_Proto_Index(PDI);
  if(NULL_2BYTES EQ i)
  {
    ASSERT_FAILED();
    return 0;
  }
  
  Debug_Print("Get_Event_Proto_Data, Event_ID : %d", Event_Separate_Data_Info[i].Event_ID);
  if((PDI & 0xFFFFFF00) EQ 0x03300000)
  {
    if(Prog_Record.Prog_Flag.All_Flag != 0)//��ǰ����һ�����������,���ڱ��
    {    
      if(PDI EQ 0x03300001)//���һ����̼�¼��Ҫ���⴦����Ϊ��ʱ���ܴ���һ�����������
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
    //��ȡ���һ���¼������¼��ڷ��������ǲ��������¼�������Ҫ����һ���¼��Ļָ�
    if(Event_Separate_Data_Info[i].SDI EQ ES_DI(PDI) && \
       Check_Event_Occuring(Event_Separate_Data_Info[i].Event_ID) && \
       memcmp((Event_Separate_Data_Info[i].pData) -> Diff_Mask, (INT8U *) Zero, sizeof((Event_Separate_Data_Info[i].pData) -> Diff_Mask)) != 0)//��ǰ�¼��ڷ���,��Ҫ����һ���¼�����
    {
      Len = Event_Separate_Proc(Event_Separate_Data_Info[i].Event_ID, EVENT_END, EVENT_VIRTRUAL);
      if(Len > 1)
        Len --;
      mem_cpy(pDst, (INT8U *)Pub_Buf0 + 1, Len, pDst_Start, DstLen);

      return Len;
    }

    //�ȶ������һ���¼��Ĵ洢DI��SDI
    Len = Read_Storage_Data(Event_Separate_Data_Info[i].Last_SDI, &SDI, &SDI, sizeof(SDI));
    if(Len != sizeof(STORA_DI)) //û�ж�ȡ���ϴη����¼��ļ�¼
    {
      ASSERT_FAILED();
      return 0;
    }

    //SDI��Ϊ�����һ�δ洢���ݵ�DI
    if(!(SDI >= Event_Separate_Data_Info[i].SDI && \
  SDI < Event_Separate_Data_Info[i].SDI + Event_Separate_Data_Info[i].Storage_Num))
    {
      if(SDI EQ NULL_EVENT_STORA_DI)//�¼���û�з����򷵻�ȫ0����
      {
        //�п�����Ҫ��֡����
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
    
    PDI = ES_DI(PDI);//Э��DIת��Ϊ�洢DI

    //DIת��������ڼ��ε��¼�����?
    //Proto_DI�����һ�ε�DI
    if(PDI >= Event_Separate_Data_Info[i].SDI && PDI < Event_Separate_Data_Info[i].SDI + Event_Separate_Data_Info[i].Storage_Num)
      PDI = PDI - Event_Separate_Data_Info[i].SDI;
    else
      return 0;

    if((SDI - PDI) < Event_Separate_Data_Info[i].SDI)
      SDI = Event_Separate_Data_Info[i].Storage_Num + SDI - PDI;
    else
      SDI = SDI - PDI;

    //��Ҫ��֡������������Ŀ��������ʱ�α���
    Len = Get_Spec_Event_Sparate_Proto_Data(SDI, pDst, pDst_Start, DstLen, pSpec_Flag);
    if(*pSpec_Flag EQ 1)
      return Len;
    
    //OS_Mutex_Pend(PUB_BUF0_SEM_ID);
    Len = Read_Storage_Data(SDI, pDst, pDst_Start, DstLen);
    if(Len EQ 0)//������ȷ����
      return 0;

    Len --;
    Event_Flag = *pDst;//�¼��������߽�����־
    mem_cpy(pDst, pDst + 1, Len, pDst_Start, DstLen);//ȥ����һ���ֽڵ��¼��������߽�����־

    if(memcmp((Event_Separate_Data_Info[i].pData) -> Diff_Mask, (INT8U *) Zero, sizeof((Event_Separate_Data_Info[i].pData) -> Diff_Mask)) != 0\
       && Event_Flag != EVENT_END)//�����¼�������û�н����¼�,Ӧ�ý�����������0
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
        if(Get_Array_Bit((INT8U *) (Event_Separate_Data_Info[i].pData -> Diff_Mask), j))//��i�������ǲ������ݣ�������֮
          mem_set(pDst + Len, 0, P_Data_Info[Index].Dst_Len, pDst_Start, DstLen); 
        
        Len += P_Data_Info[Index].Dst_Len; 

        if(P_Data_Info[Index].Dst_Len EQ 0)
          ASSERT_FAILED();
      }
    }
  }
  
  //�˴��Ѿ�����������¼������ݣ�����ĺ�����ȡ�¼��ķ�������
  //Len = Get_Event_Separate_Sub_Item_Data(PDI, pDst, Len, pDst, pDst_Start, DstLen);
  return Len;
}

INT16U Get_Event_Separate_Proto_Data(PROTO_DI PDI, INT8U* pDst, INT8U* pDst_Start, INT16U DstLen)
{ 
  INT16U Len;
  INT8U Spec_Flag;
  
  Len = _Get_Event_Separate_Proto_Data(PDI, pDst, pDst_Start, DstLen, &Spec_Flag);
  if(Spec_Flag EQ 0) //Spec_Flag == 1��ʾ����Ҫ��֡�����ݣ���_Get_Event_Separate_Proto_Data�����ڲ�������,����ֱ�ӷ�������
  {
    if(Len > 0)
      Len = Get_Event_Separate_Sub_Item_Data(PDI, pDst, Len, pDst, pDst_Start, DstLen);
  }

  return Len;
}

//��ȡ�¼��ۼƵ�Э������
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
  if(Check_Cumu_Event_Occuring(Event_Cumu_Data_Info[Index].Event_ID))//��ǰ�¼��ڷ���?
  {
    //OS_Mutex_Pend(PUB_BUF0_SEM_ID);
    Len = Event_Cumu_Proc(Event_Cumu_Data_Info[Index].Event_ID, EVENT_END, EVENT_VIRTRUAL);//����һ���¼�����,����ǰ�ۼ����ݴ洢����Pub_Buf0�� 
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

//��ȡ��չ��ͳ�����ݡ�����ʧѹ��ʧ�������򡢶���ȵ��ۼ�����
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
    //ʧѹ
    Len = _Get_Event_Cumu_Proto_Data(EC_DI(0x10000101) + ((PDI - 0x0EA00000) << 16), pDst, pDst_Start, DstLen);
   // break;
  }  
  else if(PDI EQ 0x0EA00100 ||\
     PDI EQ 0x0EA00101 ||\
     PDI EQ 0x0EA00102 ||\
     PDI EQ 0x0EA00103)
  {
    //ʧ��
    Len = _Get_Event_Cumu_Proto_Data(EC_DI(0x18000101) + ((PDI - 0x0EA00100) << 16), pDst, pDst_Start, DstLen);
  }
  else if(PDI EQ 0x0EA00200 ||\
     PDI EQ 0x0EA00201 ||\
     PDI EQ 0x0EA00202 ||\
     PDI EQ 0x0EA00203)
  {
    //����
    Len = _Get_Event_Cumu_Proto_Data(EC_DI(0x1B000101) + ((PDI - 0x0EA00200) << 16), pDst, pDst_Start, DstLen);
  }
  else if(PDI EQ 0x0EA00300 ||\
     PDI EQ 0x0EA00301 ||\
     PDI EQ 0x0EA00302 ||\
     PDI EQ 0x0EA00303)
  {
    //����
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
  
  if(PDI EQ 0x10000001) //��ʧѹ����
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_TOTAL_LOSS_VOL, pDst, pDst, DstLen);
    return 3;
  }
  else if(PDI EQ 0x10000002) //��ʧѹ�ۼ�ʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_TOTAL_LOSS_VOL, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x10010001) //A��ʧѹ����
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_LOSS_VOLT, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x10010002) //A��ʧѹʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_LOSS_VOLT, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x10020001) //B��ʧѹ����
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_LOSS_VOLT, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x10020002) //B��ʧѹʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_LOSS_VOLT, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x10030001) //C��ʧѹ����
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_LOSS_VOLT, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x10030002) //C��ʧѹʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_LOSS_VOLT, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  } 
  else if(PDI EQ 0x11010001) //A��Ƿѹ����
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_VOLT_LESS, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x11010002) //A��Ƿѹʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_VOLT_LESS, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x11020001) //B��Ƿѹ����
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_VOLT_LESS, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x11020002) //B��Ƿѹʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_VOLT_LESS, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x11030001) //C��Ƿѹ����
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_VOLT_LESS, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x11030002) //C��Ƿѹʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_VOLT_LESS, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x12010001) //A���ѹ����
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_VOLT_OVERLOAD, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x12010002) //A���ѹʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_VOLT_OVERLOAD, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x12020001) //B���ѹ����
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_VOLT_OVERLOAD, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x12020002) //B���ѹʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_VOLT_OVERLOAD, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x12030001) //C���ѹ����
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_VOLT_OVERLOAD, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x12030002) //C���ѹʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_VOLT_OVERLOAD, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }    
  else if(PDI EQ 0x13010001) //A��������
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_LOSS_PARSE, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x13010002) //A�����ʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_LOSS_PARSE, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x13020001) //B�������
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_LOSS_PARSE, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x13020002) //B�����ʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_LOSS_PARSE, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x13030001) //C��������
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_LOSS_PARSE, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x13030002) //C�����ʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_LOSS_PARSE, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }   
  else if(PDI EQ 0x14000001) //��ѹ���������
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_VOLT_NEG_SEQ, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x14000002) //��ѹ������ʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_VOLT_NEG_SEQ, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }    
  else if(PDI EQ 0x15000001) //�������������
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_CUR_NEG_SEQ, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x15000002) //����������ʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_CUR_NEG_SEQ, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }   
  else if(PDI EQ 0x16000001) //��ѹ��ƽ�����
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_VOLT_NO_EVEN, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x16000002) //��ѹ��ƽ��ʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_VOLT_NO_EVEN, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }    
  else if(PDI EQ 0x17000001) //������ƽ�����
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_CURR_NO_EVEN, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x17000002) //������ƽ��ʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_CURR_NO_EVEN, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x18010001) //A��ʧ������
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_LOSS_CURR, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x18010002) //A��ʧ��ʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_LOSS_CURR, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x18020001) //B��ʧ������
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_LOSS_CURR, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x18020002) //B��ʧ��ʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_LOSS_CURR, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x18030001) //C��ʧ������
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_LOSS_CURR, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x18030002) //C��ʧ��ʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_LOSS_CURR, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }  
  else if(PDI EQ 0x19010001) //A���������
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_OVER_CURR, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x19010002) //A�����ʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_OVER_CURR, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x19020001) //B���������
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_OVER_CURR, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x19020002) //B�����ʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_OVER_CURR, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x19030001) //C���������
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_OVER_CURR, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x19030002) //C�����ʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_OVER_CURR, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }  
  else if(PDI EQ 0x1A010001) //A���������
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_CUT_CURR, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1A010002) //A�����ʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_CUT_CURR, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1A020001) //B���������
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_CUT_CURR, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1A020002) //B�����ʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_CUT_CURR, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1A030001) //C���������
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_CUT_CURR, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1A030002) //C�����ʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_CUT_CURR, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }      
  else if(PDI EQ 0x1B010001) //A�ೱ���������
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_NEG_CURR, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1B010002) //A�ೱ������ʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_NEG_CURR, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1B020001) //B�ೱ���������
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_NEG_CURR, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1B020002) //B�ೱ������ʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_NEG_CURR, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1B030001) //C�ೱ���������
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_NEG_CURR, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1B030002) //C�ೱ������ʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_NEG_CURR, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }  
  else if(PDI EQ 0x1C010001) //A����ش���
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_POWER_EXCEED, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1C010002) //A�����ʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_POWER_EXCEED, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1C020001) //B����ش���
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_POWER_EXCEED, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1C020002) //B�����ʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_POWER_EXCEED, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1C030001) //C����ش���
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_POWER_EXCEED, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1C030002) //C�����ʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_POWER_EXCEED, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  } 
  else if(PDI EQ 0x1D000001) //��բ����
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_RELAY_OFF, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1E000001) //��բ����
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_RELAY_ON, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1F000001) //�ܹ������س����޴���
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_ALL_FACTOR_LOW, pDst, pDst, DstLen);
    return 3;    
  }
  else if(PDI EQ 0x1F000002) //�ܹ������س�����ʱ��
  {
    Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_ALL_FACTOR_LOW, pDst, pDst, DstLen);
    mem_cpy(pDst, pDst + 3, 3, pDst_Start, DstLen);
    return 3;    
  } 
  
  /*
   if(PDI EQ 0x03010000)//ʧѹ�ۼ� 
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_LOSS_VOLT, pDst, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_LOSS_VOLT, pDst + 6, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_LOSS_VOLT, pDst + 12, pDst_Start, DstLen);
      return 18;
   }
   else if(PDI EQ 0x03030000)//��ѹ�ۼ� 
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_VOLT_OVERLOAD, pDst, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_VOLT_OVERLOAD, pDst + 6, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_VOLT_OVERLOAD, pDst + 12, pDst_Start, DstLen);
      return 18;     
   }
   else if(PDI EQ 0x03040000)//�����ۼ�
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_LOSS_PARSE, pDst, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_LOSS_PARSE, pDst + 6, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_LOSS_PARSE, pDst + 12, pDst_Start, DstLen);
      return 18;  
   }
  */
   else if(PDI EQ 0x03050000) //ȫʧѹ
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_ALL_LOSS_VOLT, pDst, pDst_Start, DstLen);
      return 6; 
   }
  /*
   else if(PDI EQ 0x03070000)//��ѹ������
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_VOLT_NEG_SEQ, pDst, pDst_Start, DstLen);
      return 6;      
   }
   else if(PDI EQ 0x03080000)//����������
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_CUR_NEG_SEQ, pDst, pDst_Start, DstLen);
      return 6;      
   }
   else if(PDI EQ 0x03090000)//��ѹ��ƽ��
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_VOLT_NO_EVEN, pDst, pDst_Start, DstLen);
      return 6;     
   }
   else if(PDI EQ 0x030A0000)   // ������ƽ��
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_VOLT_NO_EVEN, pDst, pDst_Start, DstLen);
      return 6;      
   }
   else if(PDI EQ 0x030B0000) //ʧ��
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_LOSS_CURR, pDst, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_LOSS_CURR, pDst + 6, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_LOSS_CURR, pDst + 12, pDst_Start, DstLen);
      return 18; 
   }
   else if(PDI EQ 0x030C0000) //����
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_OVER_CURR, pDst, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_OVER_CURR, pDst + 6, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_OVER_CURR, pDst + 12, pDst_Start, DstLen);
      return 18; 
   } 
   //���� 0x030D0000����
   else if(PDI EQ 0x030E0000)//��������
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_A_NEG_CURR, pDst, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_B_NEG_CURR, pDst + 6, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_C_NEG_CURR, pDst + 12, pDst_Start, DstLen);
      return 18;  
   }
*/
   else if(PDI EQ 0x03110000)//����
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_POWER_OFF, pDst, pDst_Start, DstLen);
      return 3; 
   }
   else if(PDI EQ 0x03120000) //��������
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_POS_ACT_DEMAND_EXCEED, pDst, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_NEG_ACT_DEMAND_EXCEED, pDst + 3, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_Q1_REAC_DEMAND_EXCEED, pDst + 6, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_Q2_REAC_DEMAND_EXCEED, pDst + 9, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_Q3_REAC_DEMAND_EXCEED, pDst + 12, pDst_Start, DstLen);
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_Q4_REAC_DEMAND_EXCEED, pDst + 15, pDst_Start, DstLen);      
      return 18; 
   }
   else if(PDI EQ 0x03300000) //����ܴ���
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_PROG, pDst, pDst_Start, DstLen);
      return 3;  
   }
   else if(PDI EQ 0x03300100) //�����0
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_CLR_ALL_DATA, pDst, pDst_Start, DstLen);
      return 3;  
   }
   else if(PDI EQ 0x03300200) //������0
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_CLR_DEMAND_COM, pDst, pDst_Start, DstLen);
      return 3;  
   } 
   else if(PDI EQ 0x03300300) //�¼���0
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_CLR_PROCESS, pDst, pDst_Start, DstLen);
      return 3;  
   } 
   else if(PDI EQ 0x03300400) //Уʱ
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_ADJUST_TIME, pDst, pDst_Start, DstLen);
      return 3;     
   }
   else if(PDI EQ 0x03300500) //ʱ�α���
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_DATE, pDst, pDst_Start, DstLen);
      return 3;      
   }
   else if(PDI EQ 0x03300600) //ʱ������
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_YEAR, pDst, pDst_Start, DstLen);
      return 3;      
   }
   else if(PDI EQ 0x03300700) //�����ձ��
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_WEEK, pDst, pDst_Start, DstLen);
      return 3;      
   }
   else if(PDI EQ 0x03300800) //�ڼ��ձ��
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_HOLIDAY, pDst, pDst_Start, DstLen);
      return 3;      
   }
   else if(PDI EQ 0x03300900) //�й���Ϸ�ʽ���
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_ACPWR, pDst, pDst_Start, DstLen);
      return 3;      
   }
   else if(PDI EQ 0x03300A00) //�޹���Ϸ�ʽ1���
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_REACPWR1, pDst, pDst_Start, DstLen);
      return 3;      
   }   
   else if(PDI EQ 0x03300B00)//�޹���Ϸ�ʽ2���
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_REACPWR2, pDst, pDst_Start, DstLen);
      return 3;
   }
   else if(PDI EQ 0x03300C00)//�����ձ��
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_SETTLE_DATE, pDst, pDst_Start, DstLen);
      return 3;
   }
   else if(PDI EQ 0x03300D00)//�����
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_UP_COVER_OPEN, pDst, pDst_Start, DstLen);
      return 3;
   }
   else if(PDI EQ 0x03300E00)//����ť
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_DOWN_COVER_OPEN, pDst, pDst_Start, DstLen);
      return 3; 
   }
   /*else if(PDI EQ 0x03310000)//��բ
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_RELAY_OFF, pDst, pDst_Start, DstLen);
      return 6;      
   }*/
   else if((PDI & 0xFFFF0000) EQ 0x0EA00000) //ʧѹ��ʧ�������ࡢ������ۼ�����
   {
      Len = Get_Ext_Event_Cumu_Proto_Data(PDI, pDst, pDst_Start, DstLen);
      return Len;
   }
   else if(PDI EQ 0x03410000) //�͹��ĵ��Ƿѹ
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_LOWPWR_BAT_LOW, pDst, pDst_Start, DstLen);
      return 3; 
   }
   else if(PDI EQ 0x03410100) //ʱ�ӵ��Ƿѹ
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_RTC_BAT_LOW, pDst, pDst_Start, DstLen);
      return 3; 
   }  
   else if(PDI EQ 0x03420000) //���ر���
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_DEMAND_ALARM, pDst, pDst_Start, DstLen);
      return 6; 
   }
   else if(PDI EQ 0x03420100) //������բ
   {
      //Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_DEMAND_SWITCH, pDst, pDst_Start, DstLen);
      //return 3; 
     return 0;
   }    
   else if(PDI EQ 0x0E180000) //��λ
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_RESET, pDst, pDst_Start, DstLen);
      return 3; 
   }    
   else if(PDI EQ 0x0E190000) //����ʱ����
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_RTCERR_RUN, pDst, pDst_Start, DstLen);
      return 3; 
   }
   else if(PDI EQ 0x0E1C0000) //�ϵ�ʱ����
   {
      Get_Event_Cumu_BCD_Counts_Mins(ID_EVENT_RTCERR_PWRON, pDst, pDst_Start, DstLen);
      return 3; 
   }   
   else if(PDI  EQ 0x0E301100) //���ó�ʼ����
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
  
  //���ѹͳ����������Ҫ���⴦��
  if((PDI & 0xFFFF0000) EQ 0x03100000 && ((PDI >> 8) & 0xFF) <= 3)
  {
    return Clear_Proto_Phase_VolStat_Data(PDI);
  }
  //�����ʧѹ�ۼ�����
  if(PDI EQ 0x100000FF)
  {
    Clear_One_Event_Cumu_Data(ID_EVENT_TOTAL_LOSS_VOL);
    return 1;
  }
  
  //ǰһ��ʧѹ�����ͽ���ʱ�����
  if(PDI EQ 0x100001FF || PDI EQ 0x100002FF)
  {
    Write_Storage_Data(SDI_LAST_LOSS_VOL_OCCUR_TIME, (INT8U *)Zero, 6);  
    Write_Storage_Data(SDI_LAST_LOSS_VOL_END_TIME, (INT8U *)Zero, 6);
    return 1;
  }
  
  PDI = Get_Event_Separate_Start_PDI(PDI);
  PDI = ((PDI & 0xFFFFFF00) | 0x01);
  Index = Get_Event_Separate_Proto_Index(PDI); //���¼��ڷִ��¼������е�����
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


