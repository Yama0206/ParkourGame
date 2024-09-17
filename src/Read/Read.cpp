#include "Read.h"

//������
void CRead::Init()
{
	memset(&m_Test, 0.0, sizeof(m_Test));


	//X
	for (int X = 0; X < MAP_CHIP_X_NUM; X++)
	{
		//Y
		for (int Y = 0; Y < MAP_CHIP_Y_NUM; Y++)
		{
			//m_FileReadMapData[Y][X] = 0;
		}
	}
}


//�ǂݍ���
void CRead::ReadFile()
{
	FILE* fp;
	fopen_s(&fp, "Data/Map/�}�b�v�`�b�v.txt", "r");

	int mapIndexX = 0;
	int mapIndexY = 0;

	int resurt = 0;

	while (true) {
		//1�s�ڂ͎g��Ȃ��̂Ő�ɓǂݍ��݂����ς܂���
		/*fgets();*/

		//���l�̓ǂݍ���
		fscanf_s(fp, "%d, %f, %f, %f, %f, %f, %f, %d", &eType, &m_Test.m_vPos.x, &m_Test.m_vPos.y, &m_Test.m_vPos.z, &m_Test.m_vSize.x, &m_Test.m_vSize.y, &m_Test.m_vSize.z, &eType);

		//�u,�v���΂����߂ɓǂݍ��ݎ��s
		char c = fgetc(fp);
	}


	fclose(fp);
}

//�t�@�C���̏�������
void CRead::SaveFile()
{
	//�t�@�C���\���̐錾
	FILE* fp;
	//�t�@�C�����J��
	fopen_s(&fp, "Data/Map/�}�b�v�`�b�v.csv", "a");

	if (fp != NULL) {
		int mapIndexX = 0;
		int mapIndexY = 0;

		while (true) {
			//���l�̓ǂݍ���
	//

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
				fprintf_s(fp, "\n");
			}
			//���s�ł��ǂݍ��ݏI���ł��Ȃ�������v���X
			else
			{
				mapIndexX++;
			}

		}
	}

}

//�`��
void CRead::Draw()
{
	int t = eType;

	DrawFormatString(32, 32,GetColor(255, 0, 0), "%d, %f, %f, %f, %f, %f, %f, %d", &t, m_Test.m_vPos.x, m_Test.m_vPos.y, m_Test.m_vPos.z, m_Test.m_vSize.x, m_Test.m_vSize.y, m_Test.m_vSize.z, &t, true);
}
