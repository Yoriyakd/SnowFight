#pragma once

enum GameSceneState { IN_GAME, SWITCH_RESULT, IN_RESULT, END_RESULT, TIME_UP_EFFECT, BACK_TO_TITLE};

class AddUpdateBase {
public:
	virtual GameSceneState AddUpdate() = 0;
};