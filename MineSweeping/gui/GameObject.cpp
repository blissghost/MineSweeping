#include "GameObject.h"
#include "GUI.h"

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
