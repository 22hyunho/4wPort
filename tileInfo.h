#pragma once


//지형
enum TERRAIN
{
	TR_BLOCK, 
	TR_WATER, TR_POISON, 
	TR_GRASS, 
	TR_END
};

//오브젝트
enum OBJECT
{
	OBJ_BLOCK, 
	OBJ_TRAP1, 
	OBJ_TRAP2,
	OBJ_STAIR,
	OBJ_LEVER,
	OBJ_NONE,
	OBJ_NORMAL
};

//컨트롤
enum CTRL
{
	CTRL_TERRAINDRAW,	//지형		
	CTRL_OBJDRAW,		//오브젝트	
	CTRL_ERASER,		//지우개		
	CTRL_ALLBLACK,		//모든지형 블랙
	CTRL_END
};

//타일 속성
enum ATTRIBUTE
{
	North,
	South,
	West,
	East,
	DirectionCount
};

//타일 정보 담은 구조체
typedef struct tagTile
{
	dImage*		objImg;
	TERRAIN		terrain;
	OBJECT		obj;
	RECT		rc;
	RECT		objRC;
	int			x;
	int			y;
	int			z;
	int			terrainFrameX;
	int			terrainFrameY;
	int			objFrameX;
	int			objFrameY;
	int			terImgIndex;
	int			objImgIndex;
}TILE, *PTILE;

//타일셋 정보 담을 구조체
typedef struct tagSampleTile
{
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
}STILE, *PSTILE;

//현재 타일 받아올 구조체
struct tagCurrentTile
{
	int x;
	int y;
	int z;
};