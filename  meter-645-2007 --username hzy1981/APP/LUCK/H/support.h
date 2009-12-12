
/**
 * @file support.h
 *     { comment block }
 * @brief
 *     { brief description @ref support.cpp }
 * @author li.yao (nardoo@sohu.com)
 * @version v1.00
 * @date 05/29/2008 08:40
 * @note
 *     { paragraph where a note can be entered. }
 */

#ifndef __SUPPORT__
#define __SUPPORT__


// ��λ����ʾ���ݡ�
void lcdshow (u8 type, offs_t offs);
// type: ��ʾ����(modeA, modeB, modeC)
// offs: ��ʾƫ��λ��(0 ~ �������ò�����)
// return: true(������ʾ) : false(��������)

// ��������ʾ���ݡ�
void display (u8 type, code_t code);
// type: ��ʾ����(modeA, modeB, modeC)
// code: ��ʾ�Ĵ���(�������ò�����)
// return: true(������ʾ) : false(��������)

// ��Ļ��ʾ����(��ʱ���ò�����˸)
void screen (u8 type, curs_t curs);
// type: ��ʾ����(modeA, modeB, modeC)
// curs: �������λ�ã�-1(����ʾ���)

void Init_DisItem (void);


#endif
