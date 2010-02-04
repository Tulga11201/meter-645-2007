
/**
 * @file process.h
 *     { comment block }
 * @brief
 *     { brief description @ref process.cpp }
 * @author li.yao (nardoo@sohu.com)
 * @version v1.00
 * @date 05/29/2008 08:40
 * @note
 *     { paragraph where a note can be entered. }
 */

#ifndef __PROCESS__
#define __PROCESS__

// default: 200ms
#define UPDATETIME 250   //��λ������
#define TASK_RUN_TIME 70   //������ִ��ʱ�䣬��λ������

#define SECOND_1(x) ((1000/(UPDATETIME*4))*x)
#define SECOND_2(x) ((1000/(UPDATETIME*2))*x)
#define SECOND_3(x) ((1000/UPDATETIME)*x)
#define CYCLE     rollcycle

typedef unsigned char  ikey_t; ///< irda key values.


// ���ݺ�����յİ���ֵ���д���
void Process (ikey_t key);

void Initial (void);

void SetOrClr_Err_Code(INT8U ErrCode,INT8U SetOrClr);
#define ReNew_Err_Code(ErrCode) SetOrClr_Err_Code(ErrCode,1)
#define Clr_Err_Code(ErrCode)   SetOrClr_Err_Code(ErrCode,0)
#endif
