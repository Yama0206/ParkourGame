#include "ObjectList.h"

void CObjectRead::Read()
{
	FILE* fp;
	fopen_s(&fp, ENEMY_TXT_PATH, "r");

	int EnemyIndex = 0;

	while (true) {
		//1�s�ڂ͎g��Ȃ��̂Ő�ɓǂݍ��݂����ς܂���
		/*fgets();*/

		int a = 0;

		//���l�̓ǂݍ���
		fscanf_s(fp, "%d, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %d, %d, %f", );

		//�u,�v���΂����߂ɓǂݍ��ݎ��s
		char c = fgetc(fp);

		//EOF�̏ꍇ�͓ǂݍ��ݏI��
		if (c == EOF) {
			break;
		}

		//���s�R�[�h�̏ꍇ�͕ۑ����ύX����
		if (c == '\n') {
			EnemyIndex++;
		}
	}

	fclose(fp);
}