#if _MSC_VER >= 1600  
#pragma execution_character_set("utf-8")  
#endif  
#include "noveldownload.h"
#include<QMessageBox>
NovelDownload::NovelDownload(QWidget *parent)
	: QMainWindow(parent),downloader(nullptr),reader(nullptr),charset("utf8")
{
	ui.setupUi(this);
	connect(ui.downloadButton, SIGNAL(clicked()), this, SLOT(onBtClicked()));
	ui.progressBar->setRange(0, 100);
}

void NovelDownload::onBtClicked()
{
	Url=ui.Urlget->text();
	charset=ui.setCLineEdit->text();
	if (Url != "")
	{
		int end = Url.indexOf('/', Url.indexOf("//") + 2);
		Urlhead = Url.left(end);
		download();
	}
}

void NovelDownload::download()
{
	if (reader != nullptr)
	{
		delete reader;
	}
	ui.textBrowser->append("��������Ŀ¼");
	reader = new ContentReader(Url, list,charset);
	connect(reader, SIGNAL(Getpage()), this, SLOT(onContentIsEnd()));
}

void NovelDownload::onContentIsEnd()
{
	ui.textBrowser->append("Ŀ¼������ɣ����ڷ���");
	reader->Read();
	_countp = list.size();
	ui.textBrowser->append("������ɣ��ܹ�"+tr("%1").arg(_countp)+"��");
	
	if (_countp == 0)
	{
		QMessageBox::information(this, "�Ҳ�������", "��ҳ�������ܲ�Ϊutf8����鿴��ҳԴ�����е�charset��������������ڱ��������ϽǵĿ����ٴ�����");
		ui.textBrowser->append("��ҳ�������ܲ�Ϊutf8����鿴��ҳԴ�����е�charset��������������ڱ��������ϽǵĿ����ٴ�����");
	}

	if (downloader != nullptr)
	{
		delete downloader;
	}
	downloader = new HtmlBookDownloader(list, "����.txt", Urlhead,Url);
	
	downloader->Download(charset);

	downloader->setDownStyle(ui.checkBox->isChecked());

	connect(downloader, SIGNAL(OneDownloaded(int)), this, SLOT(whenOneIsDownloaded(int)));
	connect(downloader, SIGNAL(AllDownloaded()), this, SLOT(whenDownloadedEnd()));
}

void NovelDownload::whenOneIsDownloaded(int i)
{
	ui.progressBar->setValue(i*100/ _countp);
	if(!list.empty())
	ui.textBrowser->append("�����½ڣ�"+ tr("%1").arg(i) + "�� "+list.begin()->text);
}

void NovelDownload::whenDownloadedEnd()
{
	ui.textBrowser->append("�������\n��л����ʹ�ã�By_һ������ \nQt��̽���QQȺ��530679704��");
	QMessageBox::information(this, "�������", "��л����ʹ�ã�By_һ������ \nQt��̽���QQȺ��530679704");
}

NovelDownload::~NovelDownload()
{
	if (downloader != nullptr)delete downloader;
	if (reader != nullptr)delete reader;
}
