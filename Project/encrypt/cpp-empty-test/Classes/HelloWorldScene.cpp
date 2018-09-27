#include "HelloWorldScene.h"
#include "AppMacros.h"
#include <fstream>
#include <vector>

USING_NS_CC;


Scene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	//��ʼ��UPK;
	InitUPKFileSystem();

    // add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");

	Image* image = new Image();

	Data data = GetDataFromUPK("Deemo/Deemo.jpg");
	
	image->initWithImageData(data.getBytes(), data.getSize());

	Texture2D* texutre=new Texture2D();
	texutre->initWithImage(image);

	Sprite* sprite=Sprite::createWithTexture(texutre);

    // position the sprite on the center of the screen
    sprite->setPosition(cocos2d::CCDirector::sharedDirector()->getWinSize()/2);

    // add the sprite as a child to this layer
    this->addChild(sprite);
    
    return true;
}


void HelloWorld::InitUPKFileSystem()
{
	std::string fullPath = FileUtils::getInstance()->fullPathForFilename("Deemo.UPK");
	std::ifstream fin(fullPath.c_str(),std::ios::binary);
	if (!fin)
	{
		CCLOG("File Open Error");
		return;
	}
	//���ȶ�ȡ�ļ�����4byte;
	char fileCountArr[4];

	fin.read(fileCountArr,4);

	int fileCount=0;

	memcpy(&fileCount,fileCountArr,4);

	//Ȼ��ѭ����ȡ�ļ���Ϣ;
	for (int index=0;index<fileCount;index++)
	{
		OneFileInfor oneFileInfor;

		//��ȡm_id;
		char idArr[4];
		int id=0;
		fin.read(idArr,4);
		memcpy(&id,idArr,4);
		oneFileInfor.m_id=id;

		//��ȡm_StartPos;
		char startPosArr[4];
		int startPos=0;
		fin.read(startPosArr,4);
		memcpy(&startPos,startPosArr,4);
		oneFileInfor.m_StartPos=startPos;

		//��ȡm_Size;
		char sizeArr[4];
		int size=0;
		fin.read(sizeArr,4);
		memcpy(&size,sizeArr,4);
		oneFileInfor.m_Size=size;

		//��ȡm_Path;
		char pathArr[256];
		std::string path;
		fin.read(pathArr,256);
		path=pathArr;
		oneFileInfor.m_Path=path;

		m_allFileInforVec.push_back(oneFileInfor);
	}
	fin.close();

}

cocos2d::Data HelloWorld::GetDataFromUPK(const char* filepath)
{
	Data ret;

	//�����ļ�·���ҵ��ļ���Ϣ;
	for (int index=0;index<m_allFileInforVec.size();index++)
	{
		OneFileInfor oneFileInfor=m_allFileInforVec[index];
		std::string path=filepath;
		if (oneFileInfor.m_Path==path)
		{
			//�ҵ����ļ�,��ʼ��ȡ�ļ�����;
			std::string fullPath = FileUtils::getInstance()->fullPathForFilename("Deemo.UPK");
			std::ifstream fin(fullPath.c_str(),std::ios::binary);
			if (!fin)
			{
				CCLOG("File Open Error");
				return ret;
			}

			char* buffer=NULL;
			buffer=(char*)malloc(oneFileInfor.m_Size);

			fin.seekg(oneFileInfor.m_StartPos,std::ios::beg); //ios::cur�ӵ�ǰλ��ƫ��;ios::beg���ļ���ͷƫ��;

			fin.read(buffer,oneFileInfor.m_Size);

			ret.fastSet((unsigned char *)buffer,oneFileInfor.m_Size);

			fin.close();

			break;
		}
		
	}
	
	return ret;
}

