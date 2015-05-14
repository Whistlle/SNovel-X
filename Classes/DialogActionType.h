#ifdef TEST_DIALOG_ACTION_TYPE \
	|| DEBUG_ALL


#pragma once

enum class DialogActionType
{
	Default,
	Dialog = 1,
	EnterActor,
	ExitActor,
	ChangeMotion,
	Shake,
	MoveActor,
	EnterScene,
	ExitScene
};

#endif 