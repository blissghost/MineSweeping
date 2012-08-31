#ifndef GAME_OBJECT_H_H
#define GAME_OBJECT_H_H

#include "../FLTK.h"
#include <cassert>
#include <memory>
#include <iostream>
#include "../globalVal.h"

//mineInit=10, mark=12, markUnknow=14
const int markImage[] = {10,12,14};
using std::auto_ptr;

//���ڷ���ͼƬ��ͼƬ��
class GridBlock:public Fl_Box
{
public:
	GridBlock(void);
	GridBlock(const char* filename);
	GridBlock(const GridBlock& a_rightSide);
	GridBlock& operator=(const GridBlock& a_rightSide);

	//����ͼƬ
	void setImage(const char *filename);
	void setDisable() {m_enable = false;}

	int getX(void)const {return x();}
	int getY(void)const {return y();}
	int getWidth(void)const {return w();}
	int getHeight(void)const {return h();}
	void setPosition(int a_x, int a_y) {position(a_x,a_y);}
	void setSize(int a_width, int a_height);
	void setLineColumn(int i, int j) {m_lineNumber=i;m_columnNumber=j;}

	//Event����
	int handle(int event);

	//�����¼�����
	void leftClick(void);
	void rightClick(void);

private:
	auto_ptr<Fl_Image> m_pImage;//ͼƬ
	Fl_Shared_Image* m_pSharedImage;//������ͼƬ
	int m_x,m_y;
	int m_width,m_height;
	bool m_enable;//�Ƿ������Ӧ�¼������㿪���ֺ����Ϊfalse��
	bool m_isableLeftClick;//�Ƿ������Ӧ����¼�
	int m_lineNumber;//�����к�
	int m_columnNumber;//�����к�
	int m_rightClickNumber;//�Ҽ���������������һ�����ͼƬ
};

inline GridBlock::GridBlock(void)
:Fl_Box(0,0,0,0,0),m_pSharedImage(NULL),m_x(0),m_y(0),m_width(0),m_height(0),
m_enable(true),m_isableLeftClick(true),m_lineNumber(0),m_columnNumber(0),
m_rightClickNumber(0)
{

}
inline GridBlock::GridBlock(const char* filename)
:Fl_Box(0,0,0,0,0),m_pSharedImage(NULL),m_x(0),m_y(0),m_width(0),m_height(0),
m_enable(true),m_isableLeftClick(true),m_lineNumber(0),m_columnNumber(0),
m_rightClickNumber(0)
{
	setImage(filename);
}
inline GridBlock::GridBlock(const GridBlock& a_rightSide)
:Fl_Box(0,0,0,0,0),m_pSharedImage(NULL),m_x(0),m_y(0),m_width(0),m_height(0),
m_enable(true),m_isableLeftClick(true),m_lineNumber(0),m_columnNumber(0),
m_rightClickNumber(0)
{
	*this = a_rightSide;
}
inline GridBlock& GridBlock::operator=(const GridBlock& a_rightSide)
{
	m_x = a_rightSide.getX();
	m_y = a_rightSide.getY();
	m_width = a_rightSide.getWidth();
	m_height = a_rightSide.getHeight();
	m_enable = a_rightSide.m_enable;
	m_isableLeftClick = a_rightSide.m_isableLeftClick;
	m_lineNumber = a_rightSide.m_lineNumber;
	m_columnNumber = a_rightSide.m_columnNumber;
	m_rightClickNumber = a_rightSide.m_rightClickNumber;
	resize(m_x,m_y,m_width,m_height);
	if (a_rightSide.m_pSharedImage != NULL)//Fl_Shared_Image�����ڵ�����²��ܵ������ķ���
	{
		m_pSharedImage = Fl_Shared_Image::get(a_rightSide.m_pSharedImage->name());//��ȡ��ͬ��sharedImage
		m_pImage.reset(m_pSharedImage->copy(m_width,m_height));//����һ����С��ͬ��Image
		image(m_pImage.get());
		redraw();
	}
	return *this;
}

//����ͼƬ
inline void GridBlock::setImage(const char *filename)
{
	fl_register_images();
	m_pSharedImage = Fl_Shared_Image::get(filename);
	m_pImage.reset(m_pSharedImage->copy(m_width,m_height));
	image(m_pImage.get());
	redraw();
}

//����ͼƬ��С
inline void GridBlock::setSize(int a_width, int a_height)
{
	m_width = a_width;
	m_height = a_height;
	size(m_width,m_height);
	m_pImage.reset(m_pSharedImage->copy(m_width,m_height));
	image(m_pImage.get());//�����޸�image,��Ϊ֮ǰ��image���Զ�����
	redraw();
}


//Event����
inline int GridBlock::handle(int event)
{
	if (!m_enable) return (0);//�㿪���ֺ�ʧȥ����Ȩ
	using std::cout;
	using std::endl;
	switch (event)
	{
	case FL_PUSH:
		switch (Fl::event_button())//ֻ�������¼�
		{
		case FL_LEFT_MOUSE:
			if (m_isableLeftClick)
			{
				cout << "������������" << endl;
				cout << "i=" << m_lineNumber << ",j=" << m_columnNumber << endl;
				leftClick();//�������¼�����
			}
			break;
		case FL_RIGHT_MOUSE:
			rightClick();//�����һ��¼�
			break;
		}
		break;
	}
	return 0;
}

//�����һ��¼���״��ת��������ͼƬ������ǡ����족�͡��ʺš�״�����ò�����Ӧ����¼��������ÿ���Ӧ����¼�
inline void GridBlock::rightClick(void)
{
	m_rightClickNumber++;
	if (m_rightClickNumber>2)
	{
		m_rightClickNumber=0;
	}
	setImage(imageName[markImage[m_rightClickNumber]]);
	//�ڱ��״̬��ֹͣ��Ӧ����¼�
	if (m_rightClickNumber == 0)
	{
		m_isableLeftClick = true;
	}
	else
	{
		m_isableLeftClick = false;		
	}
}

#endif