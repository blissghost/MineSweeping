#include "GameObject.h"
#include "GUI.h"

DialogWindow* DialogWindow::m_pDialogWindow = NULL;
TimeShowBox* TimeShowBox::m_pTimeShowBox = NULL;

//�����һ��¼���״��ת��������ͼƬ������ǡ����족�͡��ʺš�״�����ò�����Ӧ����¼��������ÿ���Ӧ����¼�
void GridBlock::rightClick(void)
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
	GUI::getInstance()->rightClick(m_lineNumber,m_columnNumber);
}

void GridBlock::leftClick(void)
{
	GUI::getInstance()->clickOpen(m_lineNumber,m_columnNumber);

	//�������£�
	//���ݸ���Ϣ(�����кź��к�)��GUI => GUI���ú����㷨��ȡ�㿪�����и��ӺͶ�Ӧ������ => ���ݵ�ͼ����setImage(image[k]).k����[0,9]�����ø���Ϊ������Ӧ�¼�setDisable()
	//GUI������һ�����ֵ�ͼ��-1��ʾ��ʼ̬��0~9��ʾ�㿪������֡��������ֶ�Ӧ�Ÿ���ͼƬ,9��ʾ�㵽�˵��ף�GameOver
	//
	//��������¼����øø���Ϊ������Ӧ�¼�״̬�����ú����㷨����������ֵ������ȡ���º�ĵ�ͼ״�壬����ͼƬ
	//��Ҫ������ô������¼����ݸ�GUI,��GUI����������ͼƬ�ĸ�����
}

void DialogWindow::dialogWindowCB(Fl_Widget* w, void*)
{
	DialogWindow* dialog = DialogWindow::getInstance();
	dialog->m_pInputs[0]->value("");
	dialog->m_pInputs[1]->value("");
	dialog->m_pInputs[2]->value("");
	dialog->hide();
}

void DialogWindow::OkCB(Fl_Widget* w)
{
	DialogWindow* dialog = DialogWindow::getInstance();
	string strH(dialog->m_pInputs[0]->value());
	string strW(dialog->m_pInputs[1]->value());
	string strC(dialog->m_pInputs[2]->value());
	int H,W,C;
	H = atoi(strH.c_str());
	W = atoi(strW.c_str());
	C = atoi(strC.c_str());
	if (H>maxH || H<minH || W>maxW || W<minW || C>W*H)
	{
		fl_alert(dialogWindowStr[6]);
		dialog->m_pInputs[0]->value("");
		dialog->m_pInputs[1]->value("");
		dialog->m_pInputs[2]->value("");
		return;
	}
	dialog->hide();
	GUI* gui = GUI::getInstance();
	gui->setLevelSelf(H,W,C);
	dialog->m_pInputs[0]->value("");
	dialog->m_pInputs[1]->value("");
	dialog->m_pInputs[2]->value("");
}
void DialogWindow::CancelCB(Fl_Widget* w)
{
	DialogWindow* dialog = DialogWindow::getInstance();
	dialog->m_pInputs[0]->value("");
	dialog->m_pInputs[1]->value("");
	dialog->m_pInputs[2]->value("");
	dialog->hide();
}