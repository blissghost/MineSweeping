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

	int count=0;
	for(int i=0; i<m_minesCount; i++)
	{	//������
		unsigned int r = time(NULL)<<count;
		cout << r;
		srand(r);
		int index = rand() % (m_numberLines*m_numberColumns);//[0,m_numberLines*m_numberColumns-1]
		if(m_minesMap[index/m_numberColumns][index%m_numberColumns])
		{
			i--;
			cout << "�ظ���" << index << endl;
		}
		else
		{
			m_minesMap[index/m_numberColumns][index%m_numberColumns] = true;
		}
		count++;
		cout << count << endl;
	}
	cout << "��ʼ���������� " << count << "��ѭ������������" << m_minesCount << ")" << endl;
}
