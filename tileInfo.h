#pragma once


//����
enum TERRAIN
{
	TR_BLOCK, 
	TR_WATER, TR_POISON, 
	TR_GRASS, 
	TR_END
};

//������Ʈ
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

//��Ʈ��
enum CTRL
{
	CTRL_TERRAINDRAW,	//����		
	CTRL_OBJDRAW,		//������Ʈ	
	CTRL_ERASER,		//���찳		
	CTRL_ALLBLACK,		//������� ��
	CTRL_END
};

//Ÿ�� �Ӽ�
enum ATTRIBUTE
{
	North,
	South,
	West,
	East,
	DirectionCount
};

//Ÿ�� ���� ���� ����ü
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

//Ÿ�ϼ� ���� ���� ����ü
typedef struct tagSampleTile
{
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
}STILE, *PSTILE;

//���� Ÿ�� �޾ƿ� ����ü
struct tagCurrentTile
{
	int x;
	int y;
	int z;
};