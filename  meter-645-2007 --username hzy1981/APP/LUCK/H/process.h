
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
#define CYCLE     rolltime()

typedef unsigned char  ikey_t; ///< irda key values.


// ���ݺ�����յİ���ֵ���д���
void Process (ikey_t key);

void Initial (void);

#endif
