#include "Arduino.h"
#include "NamedPipes.h"

#ifdef ARDUINO_ARCH_ESP32

static hw_timer_t timers[4];

hw_timer_t::hw_timer_t()
{
	this->id = 255;
	this->prescaler = 0;
	this->cntValue = 0;
	this->alarmValue = 0;
	this->countUp = true;
	this->autoReload = false;
	this->edgeValue = true;
	this->funcToCall = NULL;

	this->enabled = false;
	this->alarmEnabled = false;
	this->currentValue = 0;
}

hw_timer_t* timerBegin(int inId, int inPrescaler, bool inCountUp) 
{	
	if (inId < 0 || inId > 3)
		return NULL;

	hw_timer_t* pTimer = & timers[inId];

	pTimer->id = inId;
	pTimer->prescaler = inPrescaler;
	pTimer->countUp = inCountUp;
	pTimer->enabled = true;

	NamedPipesSend(MessagesTypes::TimerMessage, inId, 'D');

	return pTimer;
}

void timerAttachInterrupt(hw_timer_t *pTimer, void (*inFuncToCall)(), bool inEdgeValue) 
{
	pTimer->funcToCall = inFuncToCall;
	pTimer->edgeValue = inEdgeValue;
}

void timerAlarmWrite(hw_timer_t *pTimer, int inAlarmValue, bool inAutoReload) 
{
	pTimer->alarmValue = inAlarmValue;
	pTimer->autoReload = inAutoReload;
}

void timerWrite(hw_timer_t *pTimer, int inCntValue)
{
	pTimer->cntValue = inCntValue;
	if (pTimer->countUp)
		pTimer->currentValue = 0;
	else
		pTimer->currentValue = pTimer->alarmValue;
}

void timerAlarmEnable(hw_timer_t *pTimer)
{
	pTimer->alarmEnabled = true;
	NamedPipesSend(MessagesTypes::TimerMessage, pTimer->id, 'B');
}

void timerStart(hw_timer_t* pTimer)
{
	pTimer->enabled = true;
}

void timerStop(hw_timer_t *pTimer)
{
	pTimer->enabled = false;
}

void timerAlarmDisable(hw_timer_t *pTimer)
{
	pTimer->alarmEnabled = false;
	NamedPipesSend(MessagesTypes::TimerMessage, pTimer->id, 'E');
}

void timerDetachInterrupt(hw_timer_t *pTimer) 
{
	timerAttachInterrupt(pTimer, NULL, false);
}

void timerEnd(hw_timer_t *pTimer) 
{
	pTimer->enabled = false;
	timerAttachInterrupt(pTimer, NULL, pTimer->edgeValue);
	NamedPipesSend(MessagesTypes::TimerMessage, pTimer->id, 'R');
}

int dateStart = 0;

void timersLoop()
{
	if (dateStart == 0)
		dateStart = millis();
	else
		if (millis() - dateStart >= 10)
		{
			for (int i = 0; i < 4; i++)
			{
				if (timers[i].enabled)
				{
					bool raiseTrigger = false;
					if (timers[i].countUp)
					{
						timers[i].currentValue++;
						if (timers[i].currentValue >= timers[i].alarmValue)
						{
							timers[i].currentValue = 0;
							raiseTrigger = true;
						}
					}
					else
					{
						timers[i].currentValue--;
						if (timers[i].currentValue <= 0)
						{
							timers[i].currentValue = timers[i].cntValue;
							raiseTrigger = true;
						}
					}
					if (raiseTrigger)
					{
						timers[i].funcToCall();
						if (!timers[i].autoReload)
						{
							timers[i].enabled = false;
						}
					}
				}
			}
			dateStart = millis();
		}
}

#endif
