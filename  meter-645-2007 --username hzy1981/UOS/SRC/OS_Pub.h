#ifndef OS_PUB_H
#define OS_PUB_H

#undef OS_EXT
#ifndef OS_PUB_C
#define OS_EXT extern
#else
#define OS_EXT
#endif

#define CHK_CS_BYTES 0xAAAAAAAA//��������У���������
#define CHK_BYTE 0x55

#define OS_PRINT_NULL  0//����ӡ
#define OS_PRINT_STDIO 1//��׼IO
#define OS_PRINT_COMM  2//ͨ�ſڴ�ӡ

#define CS_SUM         0//�򵥺�У��
#define CS_CRC16_0     1//CRC16�㷨0
#define CS_CRC16_1     2//CRC16�㷨1

#define EQ ==

#define SET_BIT(x,y) ((x)|=0x01<<(y))
#define CLR_BIT(x,y) ((x)&=~(0x01<<(y)))
#define GET_BIT(x,y) (((x)>>(y))&0x01)

#if OS_TRACE_EN>0
#define OS_TRACE() OS_Trace(__FILE__,__FUNCTION__,(OS_INT16U)__LINE__)
#define OS_TRACE_CTRL(x) OS_Trace_Ctrl(x)
#else
#define OS_TRACE()
#define OS_TRACE_CTRL(x)
#endif

//�������,���ʹ�ã���������
#if OS_ASSERT_EN>0
#define OS_ASSERT(x) OS_Assert((OS_BOOL)(x),__FILE__,__FUNCTION__,(OS_INT16U)__LINE__)
#define OS_ASSERT_FAILED() OS_Assert_Failed(__FILE__,__FUNCTION__,(OS_INT16U)__LINE__)
#else
#define OS_ASSERT(x)
#define OS_ASSERT_FAILED()
#endif

#define OS_Waitfor OS_Core_Wait
#define OS_Waitfor_Ms OS_Core_Wait_Ms
#define OS_Waitfor_Sec OS_Core_Wait_Sec
#define OS_Waitfor_Min OS_Core_Wait_Min
#define OS_Waitfor_Hou OS_Core_Wait_Hou

//�ṹ��У��͵ļ�������У��꣬�ȵ�����ʹ�÷���
#define OS_CHECK_STRUCT_SUM(Var) OS_Check_STRUCT_Sum((void *)&(Var),sizeof(Var),(OS_INT8U *)((Var).CS),sizeof((Var).CS))
#define OS_SET_STRUCT_SUM(Var) OS_Set_STRUCT_Sum((void *)&(Var),sizeof(Var),(OS_INT8U *)((Var).CS),sizeof((Var).CS))
//��Դ��±����ָ��Ľṹ���У������
#define OS_SET_PSTRUCT_SUM(Var,Var_Addr,Var_Len) do{if((INT8U *)((Var).CS)>=(INT8U *)(Var_Addr) &&\
                                                      (INT8U *)((Var).CS)+sizeof((Var).CS)<=(INT8U *)(Var_Addr)+(Var_Len))\
                                                       SET_STRUCT_SUM(Var);\
                                                    else\
                                                       OS_ASSERT_FAILED();\
                                                   }while(0)
//��������ĳ�������ĺ귽��
#define OS_SET_VAR(X,Y,X_Addr,X_Len) do{if(((INT8U *)&(X))>=(INT8U *)(X_Addr) && ((INT8U *)&(X))<(INT8U *)(X_Addr)+(X_Len))\
										   X=Y;\
										 else\
										   OS_ASSERT_FAILED();\
										}while(0)

//�������x=y/z,���ڲ��ж�Z!=0
#define OS_DIV(x,y,z) do{if(z!=0) x=y/z; else OS_ASSERT_FAILED();}while(0)

//Buf�����Ͷ���,�����ڹ���buf�Ķ���
#define DECLARE_HT_BUF_TYPE(Type,Len,Name) typedef struct{\
                                          OS_INT8U Head;\
                                          Type Buf[Len];\
                                          OS_INT8U Tail;\
                                          }Name

//���õ����������Ͷ���,�����ھ�̬�ֲ������Ķ��壬���߲��Ǻ���Ҫ��ȫ�ֱ���
#define DECLARE_HT_VAR_TYPE(Type,Name) typedef struct{\
                                      OS_INT8U Head;\
                                      Type Var;\
                                      OS_INT8U Tail;\
                                      }Name;
//����һ����ͷβ�ĵ��������ͱ���
#define DECLARE_HT_VAR(Ext,Type,Name)  typedef struct{\
                                      OS_INT8U Head;\
                                      Type Var;\
                                      OS_INT8U Tail;\
                                      }_##Type;\
                                      Ext _##Type _##Name;

//����һ��������ͷ��β
#define OS_SET_VAR_HT(Var) do{_#Var.Head=CHK_BYTE;_#Var.Tail=CHK_BYTE}while(0)
//���һ��������ͷ��β
#define OS_CHECK_VAR_HT(Var) ((CHK_BYTE==_#Var.Head && CHK_BYTE==_#Var.Tail)?1:0) 

//����Ҫȫ�ֱ������߾�̬�ֲ��������������·�ʽ����
/*
typedef struct
{
  INT8U Head;
  //�˴��������
  INT8U Tail;
}type_name;
*/

//���ṹ�������ͷ��β�Ƿ���ȷ
#define OS_CHECK_STRUCT_HT(Var) ((CHK_BYTE==(Var).Head  && CHK_BYTE==(Var).Tail)?1:0)
//��ʼ���ṹ�������ͷ��β
#define OS_SET_STRUCT_HT(Var)  do{(Var).Head=CHK_BYTE; (Var).Tail=CHK_BYTE;}while(0)

DECLARE_HT_VAR_TYPE(OS_INT8U,S_Int8U);
DECLARE_HT_VAR_TYPE(OS_INT16U,S_Int16U);
DECLARE_HT_VAR_TYPE(OS_INT32U,S_Int32U);
DECLARE_HT_VAR_TYPE(OS_INT8S,S_Int8S);
DECLARE_HT_VAR_TYPE(OS_INT16S,S_Int16S);
DECLARE_HT_VAR_TYPE(OS_INT32S,S_Int32S);

typedef struct
{
  OS_INT8U Head;
  
  OS_INT8S File[OS_TRACE_NUM][OS_TRACE_BUF_LEN];
  OS_INT8S Func[OS_TRACE_BUF_LEN];
  OS_INT8U Task_ID[OS_TRACE_NUM];//���õ������
  OS_INT16U Line[OS_TRACE_NUM];//���õ��к�
  OS_INT16U Counts[OS_TRACE_NUM];//���õĴ���
  OS_INT8U Index;//��ǰ��������
  
  OS_INT32U On_Off_Flag;//���Կ��ر�־
  OS_INT8U Entry_Flag; //������Ժ�����־
  
  OS_INT8U Tail;
}S_Trace_Info;

OS_EXT NO_INIT S_Trace_Info Trace_Info;

OS_EXT void OS_Trace(CONST OS_INT8S File[],CONST OS_INT8S Function[],OS_INT16U Line);
OS_EXT void OS_Assert_Failed(CONST OS_INT8S File[],CONST OS_INT8S Function[],OS_INT16U Line);
OS_EXT void OS_Assert(OS_BOOL Conditon,CONST OS_INT8S File[],CONST OS_INT8S Function[],OS_INT16U Line);
OS_EXT void OS_Trace_Ctrl(OS_INT32U Flag);
OS_EXT void OS_Trace_Info_Check();

OS_EXT void _OS_Debug_Print(CONST OS_INT8S *format, ...);
OS_EXT void OS_Debug_Print(CONST OS_INT8S *format,...);
OS_EXT void OS_memcpy(void *pDst, void *pSrc,OS_INT32U SrcLen,void *pDst_Start,OS_INT32U DstLen);
OS_EXT void OS_memset(void *pDst, OS_INT8U Value,OS_INT32U SetLen,void *pDst_Start,OS_INT32U DstLen);

OS_EXT OS_INT16U OS_Crc16_0(OS_INT8U *pSrc, OS_INT16U Len);
OS_EXT OS_INT16U OS_Crc16_1(OS_INT8U *pSrc, OS_INT16U Len);
OS_EXT OS_INT8U OS_Check_Sum(void *pSrc,OS_INT16U SrcLen,void *pCS,OS_INT8U CS_Bytes);
OS_EXT void OS_Set_Sum(void *pSrc,OS_INT16U SrcLen,void *pDst,OS_INT8U CS_Bytes,void *pDst_Start,OS_INT16U DstLen);

OS_EXT OS_INT8U OS_Check_STRUCT_Sum(void *pSrc,OS_INT16U SrcLen,OS_INT8U *pCS,OS_INT8U CS_Bytes);
OS_EXT void OS_Set_STRUCT_Sum(void *pSrc,OS_INT16U SrcLen,OS_INT8U *pCS,OS_INT8U CS_Bytes);
OS_EXT void OS_Check();
OS_EXT void OS_Info_Print();
//�ⲿ��ɵ�����Ϣ�������
extern void OS_Put_Char(OS_INT8S Chr);
#endif
