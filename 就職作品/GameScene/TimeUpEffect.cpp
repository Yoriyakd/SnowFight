#include"TimeUpEffect.h"
GameSceneState TimeUpEffect::AddUpdate()
{
	timeUpEffectCnt++;
	if (timeUpEffectCnt > timeUpEffectPlayTime)
	{
		return SWITCH_RESULT;		//�ڍs��̏�Ԃ�Ԃ�
	}
	return TIME_UP_EFFECT;
}