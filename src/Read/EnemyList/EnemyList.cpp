#include "EnemyList.h"

void CEnemyRead::ReadFile()
{
	FILE* fp;
	fopen_s(&fp, ENEMY_TXT_PATH, "r");

	int mapIndexX = 0;
	int mapIndexY = 0;

	int resurt = 0;

	while (true) {
		//1�s�ڂ͎g��Ȃ��̂Ő�ɓǂݍ��݂����ς܂���
		/*fgets();*/

		//���l�̓ǂݍ���
		fscanf_s(fp, "%d, %f, %f, %f, %f, %f, %f", );

		//�u,�v���΂����߂ɓǂݍ��ݎ��s
		char c = fgetc(fp);

		//EOF�̏ꍇ�͓ǂݍ��ݏI��
		if (c == EOF) {
			break;
		}

		//���s�R�[�h�̏ꍇ�͕ۑ����ύX����
		if (c == '\n') {
			mapIndexY++;
			mapIndexX = 0;
		}
		//���s�ł��ǂݍ��ݏI���ł��Ȃ�������v���X
		else
		{
			mapIndexX++;
		}

	}

	fclose(fp);
}