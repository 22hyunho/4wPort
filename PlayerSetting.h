#pragma once

//방향속성
#define RIGHT	0x00000001
#define LEFT	0x00000002
#define UP		0x00000004
#define DOWN	0x00000008

//키설정
#define KEY_UP		'W'
#define KEY_LEFT	'A'
#define KEY_DOWN	'S'
#define KEY_RIGHT	'D'

#define KEY_DODGE	VK_SPACE
#define KEY_TRAP	'Q'

enum COLLISIONDIRECT
{
	CD_RIGHT,
	CD_LEFT,
	CD_UP,
	CD_DOWN
};

enum TRAPLIST
{
	TRAP_BEAR,
	TRAP_SLOW
};

class PlayerSetting
{
};

