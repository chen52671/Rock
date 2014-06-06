/****************************************************************************

****************************************************************************/

#include "MySlider.h"



static const int BASEBAR_RENDERER_Z = (-3);
static const int PROGRESSBAR_RENDERER_Z = (-2);
static const int SLIDBALL_RENDERER_Z = (-1);

IMPLEMENT_CLASS_GUI_INFO(MySlider)

	MySlider::MySlider():
	_barRenderer(NULL),
	_progressBarRenderer(NULL),
	_progressBarTextureSize(CCSizeZero),
	_slidBallNormalRenderer(NULL),
	_slidBallPressedRenderer(NULL),
	_slidBallDisabledRenderer(NULL),
	_slidBallRenderer(NULL),
	_barLength(0.0),
	_percent(0),
	_scale9Enabled(false),
	_prevIgnoreSize(true),
	_textureFile(""),
	_progressBarTextureFile(""),
	_slidBallNormalTextureFile(""),
	_slidBallPressedTextureFile(""),
	_slidBallDisabledTextureFile(""),
	_capInsetsBarRenderer(CCRectZero),
	_capInsetsProgressBarRenderer(CCRectZero),
	_sliderEventListener(NULL),
	_sliderEventSelector(NULL),
	_barTexType(UI_TEX_TYPE_LOCAL),
	_progressBarTexType(UI_TEX_TYPE_LOCAL),
	_ballNTexType(UI_TEX_TYPE_LOCAL),
	_ballPTexType(UI_TEX_TYPE_LOCAL),
	_ballDTexType(UI_TEX_TYPE_LOCAL),
	_isVertical(false)
{
}

MySlider::~MySlider()
{
	_sliderEventListener = NULL;
	_sliderEventSelector = NULL;
}

MySlider* MySlider::create()
{
	MySlider* widget = new MySlider();
	if (widget && widget->init())
	{
		widget->autorelease();
		return widget;
	}
	CC_SAFE_DELETE(widget);
	return NULL;
}

bool MySlider::init()
{
	if (Widget::init())
	{
		setTouchEnabled(true);
		return true;
	}
	return false;
}

void MySlider::initRenderer()
{
	_barRenderer = CCSprite::create();
	_progressBarRenderer = CCSprite::create();
	_progressBarRenderer->setAnchorPoint(CCPoint(0.0f, 0.5f));
	CCNode::addChild(_barRenderer, BASEBAR_RENDERER_Z, -1);
	CCNode::addChild(_progressBarRenderer, PROGRESSBAR_RENDERER_Z, -1);
	_slidBallNormalRenderer = CCSprite::create();
	_slidBallPressedRenderer = CCSprite::create();
	_slidBallPressedRenderer->setVisible(false);
	_slidBallDisabledRenderer = CCSprite::create();
	_slidBallDisabledRenderer->setVisible(false);
	_slidBallRenderer = CCNode::create();
	_slidBallRenderer->addChild(_slidBallNormalRenderer);
	_slidBallRenderer->addChild(_slidBallPressedRenderer);
	_slidBallRenderer->addChild(_slidBallDisabledRenderer);
	CCNode::addChild(_slidBallRenderer, SLIDBALL_RENDERER_Z, -1);
}

void MySlider::setVertical(bool Vertical)
{
	if (Vertical) _isVertical = true;
	else _isVertical = false;
}


void MySlider::loadBarTexture(const char* fileName, TextureResType texType)
{
	if (!fileName || strcmp(fileName, "") == 0)
	{
		return;
	}
	_textureFile = fileName;
	_barTexType = texType;
	switch (_barTexType)
	{
	case UI_TEX_TYPE_LOCAL:
		if (_scale9Enabled)
		{
			static_cast<extension::CCScale9Sprite*>(_barRenderer)->initWithFile(fileName);
		}
		else
		{
			static_cast<CCSprite*>(_barRenderer)->initWithFile(fileName);
		}
		break;
	case UI_TEX_TYPE_PLIST:
		if (_scale9Enabled)
		{
			static_cast<extension::CCScale9Sprite*>(_barRenderer)->initWithSpriteFrameName(fileName);
		}
		else
		{
			static_cast<CCSprite*>(_barRenderer)->initWithSpriteFrameName(fileName);
		}
		break;
	default:
		break;
	}
	updateRGBAToRenderer(_barRenderer);
	barRendererScaleChangedWithSize();
	progressBarRendererScaleChangedWithSize();
}

void MySlider::loadProgressBarTexture(const char *fileName, TextureResType texType)
{
	if (!fileName || strcmp(fileName, "") == 0)
	{
		return;
	}
	_progressBarTextureFile = fileName;
	_progressBarTexType = texType;
	switch (_progressBarTexType)
	{
	case UI_TEX_TYPE_LOCAL:
		if (_scale9Enabled)
		{
			static_cast<extension::CCScale9Sprite*>(_progressBarRenderer)->initWithFile(fileName);
		}
		else
		{
			static_cast<CCSprite*>(_progressBarRenderer)->initWithFile(fileName);
		}
		break;
	case UI_TEX_TYPE_PLIST:
		if (_scale9Enabled)
		{
			static_cast<extension::CCScale9Sprite*>(_progressBarRenderer)->initWithSpriteFrameName(fileName);
		}
		else
		{
			static_cast<CCSprite*>(_progressBarRenderer)->initWithSpriteFrameName(fileName);
		}
		break;
	default:
		break;
	}
	updateRGBAToRenderer(_progressBarRenderer);
	if (!_isVertical)
		_progressBarRenderer->setAnchorPoint(CCPoint(0.0f, 0.5f));
	else _progressBarRenderer->setAnchorPoint(CCPoint(0.5f, 0.0f));
	_progressBarTextureSize = _progressBarRenderer->getContentSize();
	progressBarRendererScaleChangedWithSize();
}

void MySlider::setScale9Enabled(bool able)
{
	if (_scale9Enabled == able)
	{
		return;
	}

	_scale9Enabled = able;
	CCNode::removeChild(_barRenderer, true);
	CCNode::removeChild(_progressBarRenderer, true);
	_barRenderer = NULL;
	_progressBarRenderer = NULL;
	if (_scale9Enabled)
	{
		_barRenderer = extension::CCScale9Sprite::create();
		_progressBarRenderer = extension::CCScale9Sprite::create();
	}
	else
	{
		_barRenderer = CCSprite::create();
		_progressBarRenderer = CCSprite::create();
	}
	loadBarTexture(_textureFile.c_str(), _barTexType);
	loadProgressBarTexture(_progressBarTextureFile.c_str(), _progressBarTexType);
	CCNode::addChild(_barRenderer, BASEBAR_RENDERER_Z, -1);
	CCNode::addChild(_progressBarRenderer, PROGRESSBAR_RENDERER_Z, -1);
	if (_scale9Enabled)
	{
		bool ignoreBefore = _ignoreSize;
		ignoreContentAdaptWithSize(false);
		_prevIgnoreSize = ignoreBefore;
	}
	else
	{
		ignoreContentAdaptWithSize(_prevIgnoreSize);
	}
	setCapInsetsBarRenderer(_capInsetsBarRenderer);
	setCapInsetProgressBarRebderer(_capInsetsProgressBarRenderer);
}

bool MySlider::isScale9Enabled()
{
	return _scale9Enabled;
}

void MySlider::ignoreContentAdaptWithSize(bool ignore)
{
	if (!_scale9Enabled || (_scale9Enabled && !ignore))
	{
		Widget::ignoreContentAdaptWithSize(ignore);
		_prevIgnoreSize = ignore;
	}
}

void MySlider::setCapInsets(const CCRect &capInsets)
{
	setCapInsetsBarRenderer(capInsets);
	setCapInsetProgressBarRebderer(capInsets);
}

void MySlider::setCapInsetsBarRenderer(const CCRect &capInsets)
{
	_capInsetsBarRenderer = capInsets;
	if (!_scale9Enabled)
	{
		return;
	}
	static_cast<extension::CCScale9Sprite*>(_barRenderer)->setCapInsets(capInsets);
}

const CCRect& MySlider::getCapInsetBarRenderer()
{
	return _capInsetsBarRenderer;
}

void MySlider::setCapInsetProgressBarRebderer(const CCRect &capInsets)
{
	_capInsetsProgressBarRenderer = capInsets;
	if (!_scale9Enabled)
	{
		return;
	}
	static_cast<extension::CCScale9Sprite*>(_progressBarRenderer)->setCapInsets(capInsets);
}

const CCRect& MySlider::getCapInsetProgressBarRebderer()
{
	return _capInsetsProgressBarRenderer;
}

void MySlider::loadSlidBallTextures(const char* normal,const char* pressed,const char* disabled,TextureResType texType)
{
	loadSlidBallTextureNormal(normal, texType);
	loadSlidBallTexturePressed(pressed,texType);
	loadSlidBallTextureDisabled(disabled,texType);
}

void MySlider::loadSlidBallTextureNormal(const char* normal,TextureResType texType)
{
	if (!normal || strcmp(normal, "") == 0)
	{
		return;
	}
	_slidBallNormalTextureFile = normal;
	_ballNTexType = texType;
	switch (_ballNTexType)
	{
	case UI_TEX_TYPE_LOCAL:
		_slidBallNormalRenderer->initWithFile(normal);
		break;
	case UI_TEX_TYPE_PLIST:
		_slidBallNormalRenderer->initWithSpriteFrameName(normal);
		break;
	default:
		break;
	}
	updateRGBAToRenderer(_slidBallNormalRenderer);
}

void MySlider::loadSlidBallTexturePressed(const char* pressed,TextureResType texType)
{
	if (!pressed || strcmp(pressed, "") == 0)
	{
		return;
	}
	_slidBallPressedTextureFile = pressed;
	_ballPTexType = texType;
	switch (_ballPTexType)
	{
	case UI_TEX_TYPE_LOCAL:
		_slidBallPressedRenderer->initWithFile(pressed);
		break;
	case UI_TEX_TYPE_PLIST:
		_slidBallPressedRenderer->initWithSpriteFrameName(pressed);
		break;
	default:
		break;
	}
	updateRGBAToRenderer(_slidBallPressedRenderer);
}

void MySlider::loadSlidBallTextureDisabled(const char* disabled,TextureResType texType)
{
	if (!disabled || strcmp(disabled, "") == 0)
	{
		return;
	}
	_slidBallDisabledTextureFile = disabled;
	_ballDTexType = texType;
	switch (_ballDTexType)
	{
	case UI_TEX_TYPE_LOCAL:
		_slidBallDisabledRenderer->initWithFile(disabled);
		break;
	case UI_TEX_TYPE_PLIST:
		_slidBallDisabledRenderer->initWithSpriteFrameName(disabled);
		break;
	default:
		break;
	}
	updateRGBAToRenderer(_slidBallDisabledRenderer);
}

void MySlider::setPercent(int percent)
{
	if (percent > 100)
	{
		percent = 100;
	}
	if (percent < 0)
	{
		percent = 0;
	}
	_percent = percent;
	float res = percent/100.0f;
	float dis = _barLength * res;
	float hgt = _barWidth * res;
	if(!_isVertical) //水平的
	{

		_slidBallRenderer->setPosition(CCPoint(-_barLength/2.0f + dis, 0.0f));
	}
	else //如果是垂直的
	{

		_slidBallRenderer->setPosition(CCPoint(0.0f , -_barWidth/2.0f + hgt));
	}

	if (_scale9Enabled && !_isVertical)
	{
		static_cast<extension::CCScale9Sprite*>(_progressBarRenderer)->setPreferredSize(CCSize(dis,_progressBarTextureSize.height));
	}
	else
	{
		CCSprite* spriteRenderer = static_cast<CCSprite*>(_progressBarRenderer);
		CCRect rect = spriteRenderer->getTextureRect();
		if(!_isVertical) //水平的
		{
			rect.size.width = _progressBarTextureSize.width * res;
		}
		else //如果是垂直的
		{
			rect.size.height = _progressBarTextureSize.height *res;
		}
		spriteRenderer->setTextureRect(rect, spriteRenderer->isTextureRectRotated(), rect.size);
	}
}

bool MySlider::onTouchBegan(CCTouch *touch, CCEvent *unused_event)
{
	bool pass = Widget::onTouchBegan(touch, unused_event);
	if (_hitted)
	{
		CCPoint nsp = convertToNodeSpace(_touchStartPos);
		if(!_isVertical) //水平的
		{
			setPercent(getPercentWithBallPos(nsp.x));
		}
		else //如果是垂直的
		{
			setPercent(getPercentWithBallPos(nsp.y));
		}
		percentChangedEvent();
	}
	return pass;
}

void MySlider::onTouchMoved(CCTouch *touch, CCEvent *unused_event)
{
	_touchMovePos = touch->getLocation();
	CCPoint nsp = convertToNodeSpace(_touchMovePos);
	if(!_isVertical) //水平的
	{
		_slidBallRenderer->setPosition(CCPoint(nsp.x,0));
		setPercent(getPercentWithBallPos(nsp.x));
	}
	else //如果是垂直的
	{
		_slidBallRenderer->setPosition(CCPoint(0,nsp.y));
		setPercent(getPercentWithBallPos(nsp.y));
	}
	percentChangedEvent();
}

void MySlider::onTouchEnded(CCTouch *touch, CCEvent *unused_event)
{
	Widget::onTouchEnded(touch, unused_event);
}

void MySlider::onTouchCancelled(CCTouch *touch, CCEvent *unused_event)
{
	Widget::onTouchCancelled(touch, unused_event);
}

float MySlider::getPercentWithBallPos(float px)
{
		if(!_isVertical) //水平的
	{
	return (((px-(-_barLength/2.0f))/_barLength)*100.0f);
	}
	else //如果是垂直的
	{
		return (((px-(-_barWidth/2.0f))/_barWidth)*100.0f);
	}

	
}

void MySlider::addEventListenerSlider(CCObject *target, SEL_SlidPercentChangedEvent selector)
{
	_sliderEventListener = target;
	_sliderEventSelector = selector;
}

void MySlider::percentChangedEvent()
{
	if (_sliderEventListener && _sliderEventSelector)
	{
		(_sliderEventListener->*_sliderEventSelector)(this,SLIDER_PERCENTCHANGED);
	}
}

int MySlider::getPercent()
{
	return _percent;
}

void MySlider::onSizeChanged()
{
	Widget::onSizeChanged();
	barRendererScaleChangedWithSize();
	progressBarRendererScaleChangedWithSize();
}

const CCSize& MySlider::getContentSize() const
{
	return _barRenderer->getContentSize();
}

CCNode* MySlider::getVirtualRenderer()
{
	return _barRenderer;
}

void MySlider::barRendererScaleChangedWithSize()
{
	if (_ignoreSize)
	{

		_barRenderer->setScale(1.0f);
		_size = _barRenderer->getContentSize();
		_barLength = _size.width;
		_barWidth =_size.height;
	}
	else
	{
		_barLength = _size.width;
		_barWidth =_size.height;
		if (_scale9Enabled)
		{
			static_cast<extension::CCScale9Sprite*>(_barRenderer)->setPreferredSize(_size);
		}
		else
		{
			CCSize btextureSize = _barRenderer->getContentSize();
			if (btextureSize.width <= 0.0f || btextureSize.height <= 0.0f)
			{
				_barRenderer->setScale(1.0f);
				return;
			}
			float bscaleX = _size.width / btextureSize.width;
			float bscaleY = _size.height / btextureSize.height;
			_barRenderer->setScaleX(bscaleX);
			_barRenderer->setScaleY(bscaleY);
		}
	}
	setPercent(_percent);
}

void MySlider::progressBarRendererScaleChangedWithSize()
{
	if (_ignoreSize)
	{
		if (!_scale9Enabled)
		{
			CCSize ptextureSize = _progressBarTextureSize;
			float pscaleX = _size.width / ptextureSize.width;
			float pscaleY = _size.height / ptextureSize.height;
			_progressBarRenderer->setScaleX(pscaleX);
			_progressBarRenderer->setScaleY(pscaleY);
		}
	}
	else
	{
		if (_scale9Enabled)
		{
			static_cast<extension::CCScale9Sprite*>(_progressBarRenderer)->setPreferredSize(_size);
			_progressBarTextureSize = _progressBarRenderer->getContentSize();
		}
		else
		{
			CCSize ptextureSize = _progressBarTextureSize;
			if (ptextureSize.width <= 0.0f || ptextureSize.height <= 0.0f)
			{
				_progressBarRenderer->setScale(1.0f);
				return;
			}
			float pscaleX = _size.width / ptextureSize.width;
			float pscaleY = _size.height / ptextureSize.height;
			_progressBarRenderer->setScaleX(pscaleX);
			_progressBarRenderer->setScaleY(pscaleY);
		}
	}
			if(!_isVertical) //水平的
	{
	_progressBarRenderer->setPosition(CCPoint(-_barLength * 0.5f, 0.0f));
	}
	else //如果是垂直的
	{
		_progressBarRenderer->setPosition(CCPoint(0.0f,-_barWidth * 0.5f));
	}

	
	setPercent(_percent);
}

void MySlider::onPressStateChangedToNormal()
{
	_slidBallNormalRenderer->setVisible(true);
	_slidBallPressedRenderer->setVisible(false);
	_slidBallDisabledRenderer->setVisible(false);
}

void MySlider::onPressStateChangedToPressed()
{
	_slidBallNormalRenderer->setVisible(false);
	_slidBallPressedRenderer->setVisible(true);
	_slidBallDisabledRenderer->setVisible(false);
}

void MySlider::onPressStateChangedToDisabled()
{
	_slidBallNormalRenderer->setVisible(false);
	_slidBallPressedRenderer->setVisible(false);
	_slidBallDisabledRenderer->setVisible(true);
}

void MySlider::updateTextureColor()
{
	updateColorToRenderer(_barRenderer);
	updateColorToRenderer(_progressBarRenderer);
	updateColorToRenderer(_slidBallNormalRenderer);
	updateColorToRenderer(_slidBallPressedRenderer);
	updateColorToRenderer(_slidBallDisabledRenderer);
}

void MySlider::updateTextureOpacity()
{
	updateOpacityToRenderer(_barRenderer);
	updateOpacityToRenderer(_progressBarRenderer);
	updateOpacityToRenderer(_slidBallNormalRenderer);
	updateOpacityToRenderer(_slidBallPressedRenderer);
	updateOpacityToRenderer(_slidBallDisabledRenderer);
}

void MySlider::updateTextureRGBA()
{
	updateRGBAToRenderer(_barRenderer);
	updateRGBAToRenderer(_progressBarRenderer);
	updateRGBAToRenderer(_slidBallNormalRenderer);
	updateRGBAToRenderer(_slidBallPressedRenderer);
	updateRGBAToRenderer(_slidBallDisabledRenderer);
}

std::string MySlider::getDescription() const
{
	return "MySlider";
}

Widget* MySlider::createCloneInstance()
{
	return MySlider::create();
}

void MySlider::copySpecialProperties(Widget *widget)
{
	MySlider* slider = dynamic_cast<MySlider*>(widget);
	if (slider)
	{
		_prevIgnoreSize = slider->_prevIgnoreSize;
		setScale9Enabled(slider->_scale9Enabled);
		loadBarTexture(slider->_textureFile.c_str(), slider->_barTexType);
		loadProgressBarTexture(slider->_progressBarTextureFile.c_str(), slider->_progressBarTexType);
		loadSlidBallTextureNormal(slider->_slidBallNormalTextureFile.c_str(), slider->_ballNTexType);
		loadSlidBallTexturePressed(slider->_slidBallPressedTextureFile.c_str(), slider->_ballPTexType);
		loadSlidBallTextureDisabled(slider->_slidBallDisabledTextureFile.c_str(), slider->_ballDTexType);
		setPercent(slider->getPercent());
	}
}

