#include "SweepInterface.h"

inline bool notInMsg(int i, int j, vector<OpenGridMsg>& msg)
{
	for (vector<OpenGridMsg>::iterator it=msg.begin();
		it != msg.end(); it++)
	{
		if (i==it->i && j==it->j)
		{
			return false;
		}
	}
	return true;
}

//ǰ��������msgΪ��
void SweepInterface::clickOpen(int i, int j, vector<OpenGridMsg>& msg)
{
	OpenGridMsg amsg;
	if (m_mines.isMine(i,j))//�ȵ�����
	{
		amsg.i = i;
		amsg.j = j;
		amsg.state = mineBoom;//��
		msg.push_back(amsg);
		return;
	}
	if (notInMsg(i,j,msg))//����λ���Ƿ������
	{
		amsg.i = i;
		amsg.j = j;
		amsg.state = m_mines.countRoundMines(i,j);
//		cout << "(" << i << "," << j <<")��Χ������" << amsg.state << endl;
		msg.push_back(amsg);
		if (amsg.state == 0)//�����Χû���ף������㿪��Χ��
		{
			if (i-1>=0 && j-1>=0)						clickOpen(i-1,j-1,msg);
			if (j-1>=0)									clickOpen(i,j-1,msg);
			if (i+1<m_numberLines && j-1>=0)			clickOpen(i+1,j-1,msg);
			if (i-1>=0)									clickOpen(i-1,j,msg);
			if (i+1<m_numberLines)						clickOpen(i+1,j,msg);
			if (i-1>=0 && j+1<m_numberColumns)			clickOpen(i-1,j+1,msg);
			if (j+1<m_numberColumns)						clickOpen(i,j+1,msg);
			if (i+1<m_numberLines && j+1<m_numberColumns)	clickOpen(i+1,j+1,msg);
		}
	}
}
