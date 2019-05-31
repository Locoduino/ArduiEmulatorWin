#pragma once

enum MessagesTypes
{
	Idle,
	Reset,
	SerialMessage,
	DebugMessage,
	PinMessagePinMode,
	PinMessagePinState,
	PinMessagePinName,
	NewExpander,
	LcdMessage
};

extern void NamedPipesBegin(const CString &pipeSenderName, const CString &pipeListenerName, unsigned int inIdleDelay = 1000);
extern void NamedPipesDispose();
extern void NamedPipesSendRaw(const CString& mess);
extern void NamedPipesSend(MessagesTypes, const CString &mess);
extern void NamedPipesSend(MessagesTypes, int inPin, int inExpID, const CString &mess);
extern void NamedPipesSend(MessagesTypes, int inPin, int inExpID, int inInt);
extern void NamedPipesSend(MessagesTypes, int inPin, int inExpID, int inInt1, int inInt2);
extern void NamedPipesSend(MessagesTypes, int int1, int int2, int int3, const CString& mess);
extern int NamedPipesSenderConnect();
extern int NamedPipesIdle();
extern void NamedPipesIdleReset();



