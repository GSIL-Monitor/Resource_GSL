#ifndef BZStencil_h__
#define BZStencil_h__
#pragma once

///�������ִ�������http://blog.csdn.net/gebitan505/article/details/38729061��
///��Ϊ����Ч�������ɰ�׿��skia�汾�ı���ɡ��Ǳ���ԭ��
//���������������3D�����ַ�ҳ���������ı߽ǻ���ʵ�ܶࡣ
//�ٲ��ã���������ϵͳ�Ĳ���������
//��Ա����������Ľ����и���ʵ�� ��ӭmail glunoy@163.com лл��ķ���

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CocosGUI.h"
using namespace cocos2d::ui;

//#define DRAW_BACK_CLIP

USING_NS_CC;
class pp :public Node
{
	friend class HelloWorld;
public:
	pp();

	~pp(){}

	static pp* create();
	virtual bool init();

	bool isPlaying(){ return is_playing; }

	void update(float);

	void init_data();

	void Play() { init_data(); is_playing = true; is_bzmode = true; }
protected:
	float mWidth;
	float mHeight;
	float mCornerX; // ��ק���Ӧ��ҳ��
	float mCornerY;

	Vec2 mTouch; // ��ק��
	Vec2 mBezierStart1; // ������������ʼ��
	Vec2 mBezierControl1; // ���������߿��Ƶ�
	Vec2 mBeziervertex1; // ���������߶���
	Vec2 mBezierEnd1; // ���������߽�����

	Vec2 mBezierStart2; // ��һ������������
	Vec2 mBezierControl2;
	Vec2 mBeziervertex2;
	Vec2 mBezierEnd2;

	float mMiddleX;
	float mMiddleY;
	float mDegrees;
	float mTouchToCornerDis;

	bool mIsRTandLB;   // �Ƿ�������������

	void calcCornerXY(float x, float y);
	Vec2 getCross(Vec2 P1, Vec2 P2, Vec2 P3, Vec2 P4);
	void calcPoints();

	ClippingNode* clip_front_;
	ClippingNode* clip_back_;

	Sprite* sp_back_;//�Ƶı��� �Ժ��װ��˵�����ǲ���

	bool is_playing;
	bool is_bzmode;//ǰ��ִ��bz ������ȫ����
	bool page_mode;//ԭ�ط����ǰ����鱾��?
	bool is_right_to_left;//�Ƿ��������
protected:
	//����touch����ǰҳ�ͱ�ҳҪ��ʾ�Ĳ���
	void make_area_ltor(DrawNode*& pfront, DrawNode*& pback);// ��������
	void make_area_rtol(DrawNode*& pfront, DrawNode*& pback);

	void update_ltor(float);
	void update_rtol(float);
	
};


#endif // BZStencil_h__

