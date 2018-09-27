void HomeScence::initAnimation(cocos2d::CCNode* pRootNode)
{
	CCSpriteFrameCache* pCache2 = CCSpriteFrameCache::sharedSpriteFrameCache();  //���SpriteFrame�Ļ���
	pCache2->addSpriteFramesWithFile("GameYDMJ/ani/woman.plist");
	Vector <CCSpriteFrame*> pSpriteFrames2;
	pSpriteFrames2.clear();
	char strBuffer2[256] = { 0 };
	
	for (int k = 1; k < 27; k++)  //��plist�е�ͼƬ�����أ��ŵ�array��
	{
		sprintf(strBuffer2, "Women%d.png", k);
		CCSpriteFrame* pframe = pCache2->spriteFrameByName(strBuffer2);
		if (pframe == nullptr)
			continue;
		pSpriteFrames2.pushBack(pframe);
		if (k == 26)
		{
			for (BYTE i = 0; i < 4; i++)
			{
				pSpriteFrames2.pushBack(pframe);
			}
		}
	}

	CCAnimation *_animation = CCAnimation::createWithSpriteFrames(pSpriteFrames2);
	_animation->setDelayPerUnit(0.15f);
	AnimationCache::getInstance()->addAnimation(_animation, "woman");


 
	CCSpriteFrameCache* pCache = CCSpriteFrameCache::sharedSpriteFrameCache();  //���SpriteFrame�Ļ���
	pCache->addSpriteFramesWithFile("GameYDMJ/ani/man.plist");
	Vector <CCSpriteFrame*> pSpriteFrames;
	char strBuffer[256] = { 0 };
	pSpriteFrames.clear();
	for (int i = 1; i<22; i++)
 	{
		sprintf(strBuffer, "Man%d.png", i);
		CCSpriteFrame* pframe = pCache->spriteFrameByName(strBuffer);
		if (pframe == nullptr)
			continue;
		pSpriteFrames.pushBack(pframe);

		if (i == 21)
		{
			for (BYTE i = 0; i < 4; i++)
			{
				pSpriteFrames.pushBack(pframe);
			}
		}
 	}

	CCAnimation *_animation2 = CCAnimation::createWithSpriteFrames(pSpriteFrames);
	_animation2->setDelayPerUnit(0.15f);
	AnimationCache::getInstance()->addAnimation(_animation2, "man");
}