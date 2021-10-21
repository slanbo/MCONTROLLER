#ifndef __BUTTONS__H
#define __BUTTONS__H

#ifdef __cplusplus
extern "C" {
#endif

#include "gpio.h"
#include "Button.hpp"

class rightButton_Short_Press : public Button 
{
public:
	rightButton_Short_Press(const char* name)
		: Button(name){};
	
	void processButtonPress();
	
	
protected:
	
	
private:
	
	
};


class leftButton_Short_Press : public Button 
{
public:
	leftButton_Short_Press(const char* name)
		: Button(name) {}
	;
	
	void processButtonPress();
	
protected:
	
	
private:
};

class rightButton_Long_Press : public Button 
{
public:
	rightButton_Long_Press(const char* name)
		: Button(name){};
	
	void processButtonPress();
	
protected:
	
private:
};

class leftButton_Long_Press : public Button 
{
public:
	leftButton_Long_Press(const char* name)
		: Button(name) {}
	;
	
	void processButtonPress();
	
protected:
	
private:
};

class rightButton_Long_Long_Press : public Button 
{
public:
	rightButton_Long_Long_Press(const char* name)
		: Button(name) {}
	;
	
	void processButtonPress();
	
protected:
	
private:
};

class leftButton_Long_Long_Press : public Button 
{
public:
	leftButton_Long_Long_Press(const char* name)
		: Button(name) {}
	;
	
	void processButtonPress();
	
protected:
	
private:
};

class bothButtons_Short_Press : public Button 
{
public:
	bothButtons_Short_Press(const char* name)
		: Button(name) {}
	;
	
	void processButtonPress();
	
protected:
	
private:
};

	
extern double ticksKey1Pressed;
extern double ticksKey2Pressed;
extern uint32_t lastTimeTicksButtonsPressed;

extern uint8_t leftButtonShortPressCounter;
extern uint8_t leftButtonLongPressCounter;
extern uint8_t leftButtonLongLongPressCounter;
extern uint8_t rightButtonShortPressCounter;
extern uint8_t rightButtonLongPressCounter;
extern uint8_t rightButtonLongLongPressCounter;
extern uint8_t bothButtonsPressCounter;
extern leftButton_Short_Press LeftButton_Short_Press;
extern rightButton_Short_Press RightButton_Short_Press;
extern leftButton_Long_Press LeftButton_Long_Press;
extern leftButton_Long_Long_Press LeftButton_Long_Long_Press;
extern rightButton_Long_Press RightButton_Long_Press;
extern rightButton_Long_Long_Press RightButton_Long_Long_Press;
extern bothButtons_Short_Press BothButtons_Short_Press;

#ifdef __cplusplus
}
#endif
#endif