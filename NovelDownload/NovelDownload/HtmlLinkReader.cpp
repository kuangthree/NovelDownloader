#if _MSC_VER >= 1600  
#pragma execution_character_set("utf-8")  
#endif  
#include "HtmlLinkReader.h"
//#include<QMessageBox>
HtmlLinkReader::HtmlLinkReader(QList<HtmlLink>& list) :linklist(&list)
{
	list.clear();
}


HtmlLinkReader::~HtmlLinkReader()
{
}

bool HtmlLinkReader::add(const QString & in)
/*
����Ϊ<a......href=''>xxxxx</a>��ʽ���ַ�������ȡ�����Ӻ����֣���������½ڶ��壬�����list������true�������κ��쳣���򷵻�false��
*/
{
	//QMessageBox::information(nullptr, "Test", in);
	QString Text;
	QString Href;
	int end = in.indexOf("</a>");
	int start = in.indexOf(">");
	if (end == -1 || start == -1)return false;
	Text = in.mid(start + 1,end-start-1);

	int hrefindex = in.indexOf("href=");
	if (hrefindex == -1)return false;

	int hrefend = -1;

	for (int i = hrefindex+6; i < in.length(); i++)
	{
		if (in[i] == '\'' || in[i] == '\"')
		{
			hrefend = i;
			break;
		}
	}

	if (hrefend == -1)return false;

	Href = in.mid(hrefindex + 6,hrefend-hrefindex-6);

	if ((Text.indexOf("��") == -1 ) && Text.indexOf("��") == -1)
	{
		return false;
	}

	linklist->append({Text,Href});
	return true;
}
