#ifndef GAME_OBJECT_H_H
#define GAME_OBJECT_H_H

#include "../FLTK.h"
#include <cassert>
#include <memory>
#include <iostream>
#include <string>
#include "../globalVal.h"

//mineInit=10, mark=12, markUnknow=14
const int markImage[] = {10,12,14};
using std::auto_ptr;
using std::cout;
using std::endl;
using std::string;

//���ڷ���ͼƬ��ͼƬ��
class GridBlock:public Fl_Box
{
public:
	GridBlock(void);
	GridBlock(const char* filename);
	GridBlock(const GridBlock& a_rightSide);
	GridBlock& operator=(const GridBlock& a_rightSide);
	~GridBlock(void) {}

	//����ͼƬ
	void setImage(const char *filename);
	const char* getImageName(void) const {return m_pSharedImage->name();}
	void setDisable() {m_enable = false;}
	bool isEnable()const {return m_enable;}
	bool isMark()const {return m_rightClickNumber==1;}//�Ƿ����˺���
	void init();//�����ʱ����Ҫ�õ�

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

//���ñ���
inline void GridBlock::init()
{
	m_enable = true;
	m_isableLeftClick = true;
	m_rightClickNumber = 0;
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
	if (Fl_Box::handle(event)) return 1;//���ø�����¼�
	if (!m_enable) return (0);//�㿪���ֺ�ʧȥ����Ȩ
	switch (event)
	{
	case FL_PUSH:
		switch (Fl::event_button())//ֻ�������¼�
		{
		case FL_LEFT_MOUSE:
			if (m_isableLeftClick)
			{
//				cout << "������������" << endl;
//				cout << "i=" << m_lineNumber << ",j=" << m_columnNumber << endl;
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


class ImageBox:protected GridBlock
{
public:
	ImageBox(void) {}
	void setImage(const char* filename) {GridBlock::setImage(filename);}
	void setPosition(int a_x, int a_y) {GridBlock::setPosition(a_x,a_y);}
	void setSize(int a_width, int a_height) {GridBlock::setSize(a_width,a_height);}
	int handle(int e) {return 0;}
};

//�Ի���ʹ�õ���ģʽ
class DialogWindow:public Fl_Single_Window
{
private:
	static DialogWindow* m_pDialogWindow;
	DialogWindow(void);
public:
	static DialogWindow* getInstance();
	static void releaseInstance();
	~DialogWindow(void) {releaseInstance();}

private:
	void createObjects(void);
	auto_ptr<Fl_Button> m_pButtons[2];
	auto_ptr<Fl_Int_Input> m_pInputs[3];
	static void dialogWindowCB(Fl_Widget* w, void*);
	static void OkCB(Fl_Widget* w);
	static void CancelCB(Fl_Widget* w);
};

inline DialogWindow* DialogWindow::getInstance()
{
	if(m_pDialogWindow==NULL)
	{
		m_pDialogWindow=new DialogWindow();
	}
	return m_pDialogWindow;
}
inline void DialogWindow::releaseInstance()
{
	delete m_pDialogWindow;
	m_pDialogWindow = NULL;
}
inline DialogWindow::DialogWindow(void)
:Fl_Single_Window(dialogWindowWidth,dialogWindowHeight,dialogWindowStr[0])
{
	begin();//������������Ӷ���
		createObjects();
	end();
	show();
}
inline void DialogWindow::createObjects(void)
{
	m_pInputs[0].reset(new Fl_Int_Input(0.4*dialogWindowWidth,0.2*dialogWindowHeight,80,20,dialogWindowStr[1]));
	m_pInputs[1].reset(new Fl_Int_Input(0.4*dialogWindowWidth,0.4*dialogWindowHeight,80,20,dialogWindowStr[2]));
	m_pInputs[2].reset(new Fl_Int_Input(0.4*dialogWindowWidth,0.6*dialogWindowHeight,80,20,dialogWindowStr[3]));
	m_pButtons[0].reset(new Fl_Button(0.7*dialogWindowWidth,0.3*dialogWindowHeight,80,20,dialogWindowStr[4]));//ȷ��
	m_pButtons[1].reset(new Fl_Button(0.7*dialogWindowWidth,0.45*dialogWindowHeight,80,20,dialogWindowStr[5]));//ȡ��
	callback(&DialogWindow::dialogWindowCB);
	m_pButtons[0]->callback(&DialogWindow::OkCB);
	m_pButtons[1]->callback(&DialogWindow::CancelCB);
}

class TimeShowBox:public Fl_Group
{
private:
	static TimeShowBox* m_pTimeShowBox;
public:
	static TimeShowBox* getInstance();
	static void releaseInstance();
	~TimeShowBox(void) {releaseInstance();}

public:
	TimeShowBox(void);
	void resize(int a_x, int a_y, int a_width, int a_height);
	void setRemainMines(int a_num);
	void setMarkMines(int a_num);
	void showTimer(int a_time);

private:
	void createObjects(void);
	auto_ptr<Fl_Box> m_pBox[3];//��ʾ�׵�����
	int m_width;
	int m_height;
	char m_str[10];
};
inline TimeShowBox* TimeShowBox::getInstance()
{
	if(m_pTimeShowBox==NULL)
	{
		m_pTimeShowBox=new TimeShowBox();
	}
	return m_pTimeShowBox;
}
inline void TimeShowBox::releaseInstance()
{
	delete m_pTimeShowBox;
	m_pTimeShowBox = NULL;
}

inline TimeShowBox::TimeShowBox(void)
:Fl_Group(0,0,timeShowBoxWidth,timeShowBoxHeight,0),
m_width(timeShowBoxWidth), m_height(timeShowBoxHeight)
{
	box(FL_DOWN_BOX);
	createObjects();
	show();
}
inline void TimeShowBox::resize(int a_x, int a_y, int a_width, int a_height)
{
	m_width = a_width;
	m_height = a_height;
	Fl_Group::resize(a_x,a_y, a_width,a_height);
}
inline void TimeShowBox::createObjects(void)
{
	fl_register_images();
	begin();
		m_pBox[0].reset(new Fl_Box(FL_DOWN_BOX,4,4,0.3*m_width,m_height-8,0));
		m_pBox[1].reset(new Fl_Box(FL_DOWN_BOX,0.35*m_width,4,0.3*m_width,m_height-8,0));
		m_pBox[2].reset(new Fl_Box(FL_DOWN_BOX,0.7*m_width-4,4,0.3*m_width,m_height-8,0));
	end();
}
	
inline void TimeShowBox::setRemainMines(int a_num)
{
	if (a_num<0) a_num=0;
	sprintf(m_str,TimeShowBoxStr[0],a_num);
	m_pBox[0]->copy_label(m_str);
	m_pBox[0]->redraw_label();
}

inline void TimeShowBox::setMarkMines(int a_num)
{
	sprintf(m_str,TimeShowBoxStr[1],a_num);
	m_pBox[1]->copy_label(m_str);
	m_pBox[1]->redraw_label();
}

inline void TimeShowBox::showTimer(int a_time)
{
	sprintf(m_str,TimeShowBoxStr[2],a_time);
	m_pBox[2]->copy_label(m_str);
	m_pBox[2]->redraw_label();
}
#endif
