#ifndef HTLCDlib_h
#define HTLCDlib_h


#undef HTLCD_EXT
#ifndef HTLCD_C
#define HTLCD_EXT extern
#else
#define HTLCD_EXT
#endif


HTLCD_EXT volatile INT8U Show_Lcd_Ram[MAX_SEG+1];         //0~MAX_SEG
HTLCD_EXT volatile INT8U Show_Lcd_Flag;

typedef struct
{
  INT16U Sign;
  INT8U x;        //Seg
  INT8U y;        //com
}LCD_S_D_POS;


//Sx,Seg,Com,�����ǳ���Ԫ�أ�Sx���������Ա���һ����˼
HTLCD_EXT const LCD_S_D_POS LCD_S_Const[]=
{ 
  {0,0,0},			//λ��0����ʾΪ��
  {1,23,1},
  {2,23,2},
  {3,23,3},
  {4,23,4},
  {5,23,5},
  {6,23,6},
  {7,23,7},  
  {8,18,7},  
  {9,31,1},
  {10,31,3},
    
  {11,31,5},
  {12,31,7},  
  {13,30,7},
  {14,30,5},
  {15,30,3},
  {16,30,1},  
  {17,29,1},
  {18,29,3},
  {19,29,5},  
  {20,29,7},  
    
  {21,32,1},
  {22,31,0},
  {23,32,0},
  {24,23,0},
  {25,32,2},
  {26,32,3},
  {27,32,4},
  {28,32,5},
  {29,32,6},
  {30,32,7},
    
  {31,19,7},
  {32,31,2},
  {33,31,4},
  {34,31,6},
  {35,30,6},
  {36,30,4},
  {37,30,2},
  {38,30,0},  
  {39,29,0},
  {40,29,2},
    
  {41,29,4},
  {42,29,6},
  {43,9,7},
  {44,0,7},
  {45,24,7},
  {46,24,3},
  {47,25,3},
  {48,2,7},
  {49,25,5},
  {50,25,6},
  
  {51,27,6},
  {52,27,5},
  {53,27,4},
  {54,27,2},  
  {55,21,1},
  {56,21,2},
  {57,21,3},
  {58,21,4},
  {59,21,5},
  {60,21,6},
    
  {61,21,7},
  {62,22,7},
  {63,22,6},
  {64,22,5},
  {65,22,4},
  {66,22,3},  
  {67,22,2},
  {68,22,1},
  {69,22,0},
  {70,24,1},
    
  {71,25,1},
  {72,24,2},
  {73,25,2},
  {74,25,4},
  {75,25,7},
  {76,26,7},
  {77,27,3},
  {78,27,1},
  {79,27,0},  
  {80,28,3},
  
  {81,28,7},
  {82,28,1},
  {83,26,0},
  {84,10,7},
  {85,11,7},
  {86,12,7},
  {87,13,7},
  {88,14,7},
  {89,15,7},
  {90,21,0},
  
  {91,28,0},
  {92,28,5},
  {93,28,6},
  {94,28,4},
  {95,28,2},
  {96,20,7},
  {97,26,2},
  {98,26,5},
  {99,26,3},  
  {100,26,6},
  
  {101,26,1},
  {102,26,4},  
  {103,4,7}
};
 
#define MAX_S_NUM (sizeof(LCD_S_Const)/sizeof(LCD_S_D_POS))
//Sx,Seg,Com,�����ǳ���Ԫ�أ���������Nxһ���ʾһ������
HTLCD_EXT const LCD_S_D_POS LCD_D_Const[]=
{
  {0,0,0},      //λ��0����ʾΪ��
  {4,1,7},      //:
  {6,3,7},      //:
  {7,5,7},      //.
  {8,27,7},     //.
  {9,6,7},      //.
  {10,7,7},     //.
  {11,8,7},     //.
  
  {19,16,7},    //.
  {20,17,7},    //.
  {21,24,6},    //.
  {22,24,5}     //.
};

#define MAX_D_NUM (sizeof(LCD_D_Const)/sizeof(LCD_S_D_POS))


#define MAX_AU_ID 4
typedef struct
{
  INT16U Sign;    //Sx, Dx,  Nx
  INT8U x;                    //Seg
  INT8U y;                    //com
  //INT8U RelaType;             //��������
  //INT8U RelaNum;             //��������
  //INT8U RelaID[MAX_AU_ID];    //����Ԫ��
}LCD_N_POS;

HTLCD_EXT const LCD_N_POS LCD_N_Const[]=
{
  //Sx,Seg,Com,�����Ǳ���Ԫ�أ�8�ַ���A~G���ϲ��ܱ���һ����˼,ͬʱ������������־����
  {0,0,0},			 //λ��0����ʾΪ��
  {1,18,0},      //A
  {1,18,1},      //B
  {1,18,4},      //C
  {1,18,6},      //D
  {1,18,5},      //E
  {1,18,2},      //F
  {1,18,3},      //G
  
  {2,19,0},      //A
  {2,19,1},      //B
  {2,19,4},      //C
  {2,19,6},      //D
  {2,19,5},      //E
  {2,19,2},      //F
  {2,19,3},      //G
  
  {3,0,0},      //A
  {3,0,1},      //B
  {3,0,4},      //C
  {3,0,6},      //D
  {3,0,5},      //E
  {3,0,2},      //F
  {3,0,3},      //G
  
  {4,1,0},      //A
  {4,1,1},      //B
  {4,1,4},      //C
  {4,1,6},      //D
  {4,1,5},      //E
  {4,1,2},      //F
  {4,1,3},      //G
  
  {5,2,0},      //A
  {5,2,1},      //B
  {5,2,4},      //C
  {5,2,6},      //D
  {5,2,5},      //E
  {5,2,2},      //F
  {5,2,3},      //G
  
  
  {6,3,0},      //A
  {6,3,1},      //B
  {6,3,4},      //C
  {6,3,6},      //D
  {6,3,5},      //E
  {6,3,2},      //F
  {6,3,3},      //G
  
  {7,4,0},      //A
  {7,4,1},      //B
  {7,4,4},      //C
  {7,4,6},      //D
  {7,4,5},      //E
  {7,4,2},      //F
  {7,4,3},      //G
  
  {8,5,0},      //A
  {8,5,1},      //B
  {8,5,4},      //C
  {8,5,6},      //D
  {8,5,5},      //E
  {8,5,2},      //F
  {8,5,3},      //G
  
  {9,6,0},      //A
  {9,6,1},      //B
  {9,6,4},      //C
  {9,6,6},      //D
  {9,6,5},      //E
  {9,6,2},      //F
  {9,6,3},      //G
  
  
  {10,7,0},      //A
  {10,7,1},      //B
  {10,7,4},      //C
  {10,7,6},      //D
  {10,7,5},      //E
  {10,7,2},      //F
  {10,7,3},      //G
  
  {11,8,0},      //A
  {11,8,1},      //B
  {11,8,4},      //C
  {11,8,6},      //D
  {11,8,5},      //E
  {11,8,2},      //F
  {11,8,3},      //G
  
  
  {12,9,0},      //A
  {12,9,1},      //B
  {12,9,4},      //C
  {12,9,6},      //D
  {12,9,5},      //E
  {12,9,2},      //F
  {12,9,3},      //G
  
  {13,20,0},      //A
  {13,20,1},      //B
  {13,20,4},      //C
  {13,20,6},      //D
  {13,20,5},      //E
  {13,20,2},      //F
  {13,20,3},      //G
  
  
  {14,10,0},      //A
  {14,10,1},      //B
  {14,10,4},      //C
  {14,10,6},      //D
  {14,10,5},      //E
  {14,10,2},      //F
  {14,10,3},      //G
  
  {15,11,0},      //A
  {15,11,1},      //B
  {15,11,4},      //C
  {15,11,6},      //D
  {15,11,5},      //E
  {15,11,2},      //F
  {15,11,3},      //G
  
  
  {16,12,0},      //A
  {16,12,1},      //B
  {16,12,4},      //C
  {16,12,6},      //D
  {16,12,5},      //E
  {16,12,2},      //F
  {16,12,3},      //G
  
  {17,13,0},      //A
  {17,13,1},      //B
  {17,13,4},      //C
  {17,13,6},      //D
  {17,13,5},      //E
  {17,13,2},      //F
  {17,13,3},      //G
  
  
  {18,14,0},      //A
  {18,14,1},      //B
  {18,14,4},      //C
  {18,14,6},      //D
  {18,14,5},      //E
  {18,14,2},      //F
  {18,14,3},      //G
  
  {19,15,0},      //A
  {19,15,1},      //B
  {19,15,4},      //C
  {19,15,6},      //D
  {19,15,5},      //E
  {19,15,2},      //F
  {19,15,3},      //G
  
  
  {20,16,0},      //A
  {20,16,1},      //B
  {20,16,4},      //C
  {20,16,6},      //D
  {20,16,5},      //E
  {20,16,2},      //F
  {20,16,3},      //G
  
  {21,17,0},      //A
  {21,17,1},      //B
  {21,17,4},      //C
  {21,17,6},      //D
  {21,17,5},      //E
  {21,17,2},      //F
  {21,17,3}     //G
};


#define MAX_N_NUM (sizeof(LCD_N_Const)/sizeof(LCD_N_POS))
typedef struct
{
  INT8U Type_8;     //0~9,A b,C,d,E,F,�Ͽ�('O'),�¿�('o'),=,-
  INT8U Num;        //Ԫ�ظ���
  INT8U Pxy8[7];    //��ʾ��Ԫ�ض���'A'~'G'���
}LCD_LED;

//��'8'������
HTLCD_EXT const LCD_LED LED_Pixy8_Const[]=
{ {0},
  {'0',6,{'A','B','C','D','E','F'}},
  {'1',2,{'B','C'}},
  {'2',5,{'A','B','D','E','G'}},
  {'3',5,{'A','B','C','D','G'}},
  {'4',4,{'B','C','F','G'}},
  {'5',5,{'A','C','D','F','G'}},
  {'6',6,{'A','C','D','E','F','G'}},
  {'7',3,{'A','B','C'}},
  {'8',7,{'A','B','C','D','E','F','G'}},
  {'9',6,{'A','B','C','D','F','G'}},
  
  {'A',6,{'A','B','C','E','F','G'}},
  {'a',6,{'A','B','C','E','F','G'}},
  {'B',5,{'C','D','E','F','G'}},
  {'b',5,{'C','D','E','F','G'}},
  {'C',4,{'A','D','E','F'}},
  {'d',5,{'B','C','D','E','G'}},
  {'D',5,{'B','C','D','E','G'}},
  {'r',2,{'E','G'}},
  {'R',2,{'E','G'}},
  {'E',5,{'A','D','E','F','G'}},
  {'F',4,{'A','E','F','G'}},
  {'G',6,{'A','C','D','E','F','G'}},
  {'H',5,{'B','C','E','F','G'}},
  {'I',2,{'B','C'}},
  {'i',2,{'B','C'}},
  {'L',3,{'D','E','F'}},
  {'l',3,{'D','E','F'}},
  {'O',6,{'A','B','C','D','E','F'}},   //�Ͽ�
  {'o',4,{'C','D','E','G'}},      			//�¿�
  {'P',5,{'A','B','E','F','G'}},
  {'=',2,{'A','D'}},
  {'-',1,{'G'}},
  {'U',5,{'B','C','D','E','F'}},
  {'S',5,{'A','C','D','F','G'}},
  {'T',3,{'A','E','F'}},
  {'t',3,{'A','E','F'}},
  {'n',5,{'A','B','C','E','F'}},
  {'N',5,{'A','B','C','E','F'}}
};


#define MAX_LED_NUM (sizeof(LED_Pixy8_Const)/sizeof(LCD_LED))


#endif 