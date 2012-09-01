#include "Mines.h"

void Mines::initMines(int a_lines, int a_columns, int a_minesCount)
{
	assert(a_minesCount<a_lines*a_columns);
	m_minesCount = a_minesCount;
	m_numberLines = a_lines;
	m_numberColumns = a_columns;
	m_minesMap.resize(m_numberLines);
	vector<bool> minesMapLines;
	minesMapLines.resize(m_numberColumns);
	minesMapLines.assign(m_numberColumns,false);
	m_minesMap.assign(m_numberLines,minesMapLines);

	unsigned int count=0;
	unsigned int alpha=0;
	srand(time(NULL));
	for(int i=0; i<m_minesCount; i++)
	{	//������
		int index = (rand())%(m_numberLines*m_numberColumns);//[0,m_numberLines*m_numberColumns-1]
		if(m_minesMap[index/m_numberColumns][index%m_numberColumns])
		{
			i--;
			alpha++;//ͳ���ظ��Ĵ���
		}
		else
		{
			m_minesMap[index/m_numberColumns][index%m_numberColumns] = true;
		}
		count++;
	}
	cout << "��ʼ���������� " << count << "��ѭ������������" << m_minesCount << ")" << endl;
	cout << "�ظ�������" << alpha << endl;
}
