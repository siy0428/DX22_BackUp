#include "OXAllocateHierarchy.h"

void Anime_Test_Init(void)
{
	ModelAnime_Init("model\\anime\\anime_test.x", "model\\anime\\anime_test.png");
}


void Anime_Test_Uninit(void)
{
	ModelAnime_Uninit();
}


void Anime_Test_Draw(void)
{
	ModelAnime_Draw(0.016f);
}