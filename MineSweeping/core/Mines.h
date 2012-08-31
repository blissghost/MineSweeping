#ifndef MINES_H_
#define MINES_H_

#include <cstdlib>
#include <ctime>
#include <cassert>
#include <vector>
#include <iostream>
#include "../globalVal.h"

using std::vector;
using std::cout;
using std::endl;
class Mines
{
public:
	Mines(void);
	void initMines(int a_lines, int a_columns, int a_minesCount);
	bool isMine(int a_line, int a_column);//�����Ǳ߽�������������ܳ���Խ�������
	int countRoundMines(int i, int j);//ͳ����Χ�ĵ�������

private:
	vector<vector<bool> > m_minesMap;//�׵Ĳ���ͼ
	int m_minesCount;//�׵ĸ���
	int m_numberLines,m_numberColumns;//����������

	bool isMine2(int a_line, int a_column);//���Ǳ߽��������������Խ��һ��
};
inline Mines::Mines(void):m_minesCount(initMinesCount),
m_numberLines(initLines),m_numberColumns(initColumns)
{
	initMines(m_numberLines,m_numberColumns,m_minesCount);
}

//�ⲿʹ�ã����ܳ���Խ�����
inline bool Mines::isMine(int a_line, int a_column)
{
	assert(a_line>-1);
	assert(a_column>-1);
	assert(a_line<m_numberLines);
	assert(a_column<m_numberColumns);
	return m_minesMap[a_line][a_column];
}

//�ڲ�ʹ�ã�����Խ��һ��
inline bool Mines::isMine2(int a_line, int a_column)
{
	assert(a_line>-2);
	assert(a_column>-2);
	assert(a_line<m_numberLines+1);
	assert(a_column<m_numberColumns+1);
	if (a_line==-1 || a_line==m_numberLines
		|| a_column==-1 || a_column==m_numberColumns)//�߽����
	{
//		cout << "�߽����" << endl;
		return false;
	}
	return m_minesMap[a_line][a_column];
}

inline int Mines::countRoundMines(int i, int j)
{
	int count=0;
	if (isMine2(i-1,j-1))	count++;
	if (isMine2(i,j-1))		count++;
	if (isMine2(i+1,j-1))	count++;
	if (isMine2(i-1,j))		count++;
	if (isMine2(i+1,j))		count++;
	if (isMine2(i-1,j+1))	count++;
	if (isMine2(i,j+1))		count++;
	if (isMine2(i+1,j+1))	count++;
	assert(count<9);
	return count;
}
#endif