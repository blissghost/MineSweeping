#ifndef GLOBAL_VAL_H_
#define GLOBAL_VAL_H_

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const char const* imageName[];
extern const int initMinesCount;//��ʼ���׸���
extern const int initColumns;//��ʼ����
extern const int initLines;
extern const float initBlockWidth;//��ʼ�������ش�С
extern const float initBlockHeight;


//���ڴ��ݵ㿪�ĸ��ӵ�λ�ú����ֵ���Ϣ�ṹ��
struct OpenGridMsg 
{
	int i;
	int j;
	int state;//ͼƬ��Ӧ������[0~9]
};


//��GUI::clickOpen()�����л��������Ľӿ�
//�����㷨�и�GUI�ṩ�Ľӿ�
//void clickOpen(int i, int j, vector<OpenGridMsg>& msg)

//���������ʾ״̬��ö������
enum ImageName
{
	zero=0,one=1,two=2,three=3,four=4,five=5,six=6,seven=7,eight=8,
	mineBoom=9,mineInit=10,mineOut=11,mark=12,markWrong=13,markUnknow=14
};

#endif