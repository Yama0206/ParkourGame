#include "ReadParkourObjectList.h"

#define PARKOUR_LIST_PATH ("data/File/ParkourObject/ParkourObject.txt")

void ReadParkourObjectList::ReadFile()
{
	FILE* fp = nullptr;

	//�t�@�C�����J��
	if (fopen_s(&fp, PARKOUR_LIST_PATH, "r") == 0) {
		//�t�@�C���̓ǂݍ��݁A�ϐ��ւ̕ۑ�
		while (fscanf_s(fp, "%d, %f,%f,%f , %f,%f,%f, %d", 
			m_sParkourData.m_eType,
			m_sParkourData.m_vPos.x, m_sParkourData.m_vPos.z, m_sParkourData.m_vPos.z,
			m_sParkourData.m_vScale.x, m_sParkourData.m_vScale.y, m_sParkourData.m_vScale.z,
			m_sParkourData.IsAllive
		) != EOF) {
			//���X�g�ɒǉ�
			sparkourObjectInfoList.push_back(m_sParkourData);
		}
	}

	fclose(fp);
}