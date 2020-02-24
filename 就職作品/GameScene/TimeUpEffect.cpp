#include"TimeUpEffect.h"
GameSceneState TimeUpEffect::AddUpdate()
{
	timeUpEffectCnt++;
	if (timeUpEffectCnt > timeUpEffectPlayTime)
	{
		return SWITCH_RESULT;		//ˆÚsæ‚Ìó‘Ô‚ğ•Ô‚·
	}
	return TIME_UP_EFFECT;
}