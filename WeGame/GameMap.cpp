#include "pch.h"
#include "GameMap.h"
#include "Address.h"
#include "ReadWrite.h"
#include "GetGameData.h"
#include "GameCall.h"

��ͼ���� Ѱ·_��ͼ����()
{
	��ͼ���� ��_��ͼ����;
	ULONG64 ��_�������� = _ReadLong(_ReadLong(_ReadLong(������) + ʱ���ַ) + ����ƫ��);
	ULONG64 ��_�������� = ����(��_�������� + ����ƫ��);

	��_��ͼ����.�� = _ReadInt(_ReadLong(��_�������� + ����ƫ��) + ��_�������� * 8 + 0);
	��_��ͼ����.�� = _ReadInt(_ReadLong(��_�������� + ����ƫ��) + ��_�������� * 8 + 4);
	��_��ͼ����.��ʱ���� = _ReadLong(_ReadLong(��_�������� + ����ƫ��) + 32 * ��_�������� + 8);
	��_��ͼ����.ͨ������ = ��_��ͼ����.�� * ��_��ͼ����.��;
	for (size_t i = 0; i < ��_��ͼ����.ͨ������; i++)
	{
		��_��ͼ����.��ͼͨ��.insert(��_��ͼ����.��ͼͨ��.begin() + i, _ReadInt(��_��ͼ����.��ʱ���� + i * 4));
	}
	��_��ͼ����.��ʼ����.x = ȡ��ǰ����().x + 1;
	��_��ͼ����.��ʼ����.y = ȡ��ǰ����().y + 1;
	��_��ͼ����.�յ�����.x = ȡBOSS����().x + 1;
	��_��ͼ����.�յ�����.y = ȡBOSS����().y + 1;
	if (��_��ͼ����.��ʼ����.x == ��_��ͼ����.�յ�����.x && ��_��ͼ����.��ʼ����.y == ��_��ͼ����.�յ�����.y)
	{
		return ��_��ͼ����;
	}
	��_��ͼ����.����ƣ�� = Ѱ·_��ȡ�߷�(��_��ͼ����.��ͼͨ��, ��_��ͼ����.��, ��_��ͼ����.��, ��_��ͼ����.��ʼ����, ��_��ͼ����.�յ�����, ��_��ͼ����.��ͼ�߷�);
	return ��_��ͼ����;
}
DWORD Ѱ·_��ȡ�߷�(vector<DWORD> ��_��ͼͨ��, DWORD ��_����, DWORD ��_�߶�, ������ ��_��ͼ���, ������ ��_��ͼ�յ�, vector<������>& ��_��ʵ�߷�)
{
	������ start_coordinate;
	������ end_coordinate;
	vector<vector<��Ϸ��ͼ>> map_flag;
	vector<vector<��Ϸ��ͼ>> map_array;
	vector<������> cross_way;

	if (��_��ͼ���.x == ��_��ͼ�յ�.x && ��_��ͼ���.y == ��_��ͼ�յ�.y)
	{
		��_��ʵ�߷�.clear();
		��_��ʵ�߷�.resize(0);
		return 0;
	}
	Ѱ·_���ɵ�ͼ(��_����, ��_�߶�, ��_��ͼͨ��, map_array);
	Ѱ·_��ʾ��ͼ(map_array, ��_����, ��_�߶�, map_flag);
	start_coordinate.x = ��_��ͼ���.x * 3 - 2;
	start_coordinate.y = ��_��ͼ���.y * 3 - 2;
	end_coordinate.x = ��_��ͼ�յ�.x * 3 - 2;
	end_coordinate.y = ��_��ͼ�յ�.y * 3 - 2;
	Ѱ·_·���㷨(map_flag, start_coordinate, end_coordinate, ��_���� * 3, ��_�߶� * 3, cross_way);
	return Ѱ·_��������(cross_way, ��_��ʵ�߷�);

}
VOID Ѱ·_���ɵ�ͼ(DWORD ��_����, DWORD ��_�߶�, vector<DWORD> ��_��ͼͨ��, vector<vector<��Ϸ��ͼ>>& ��_��Ϸ��ͼ)
{
	��_��Ϸ��ͼ.clear();
	��_��Ϸ��ͼ.resize(��_����);
	for (DWORD x = 0; x < ��_����; x++)
	{
		��_��Ϸ��ͼ[x].resize(��_�߶�);
	}
	int i = 0;
	for (DWORD y = 0; y < ��_�߶�; y++)
	{
		for (DWORD x = 0; x < ��_����; x++)
		{
			��_��Ϸ��ͼ[x][y].��ͼ����.x = x;
			��_��Ϸ��ͼ[x][y].��ͼ����.y = y;
			��_��Ϸ��ͼ[x][y].��ͼͨ�� = ��_��ͼͨ��[i];
			��_��Ϸ��ͼ[x][y].��ͼ��� = Ѱ·_�жϷ���(��_��ͼͨ��[i], 0);
			��_��Ϸ��ͼ[x][y].��ͼ�ұ� = Ѱ·_�жϷ���(��_��ͼͨ��[i], 1);
			��_��Ϸ��ͼ[x][y].��ͼ�ϱ� = Ѱ·_�жϷ���(��_��ͼͨ��[i], 2);
			��_��Ϸ��ͼ[x][y].��ͼ�±� = Ѱ·_�жϷ���(��_��ͼͨ��[i], 3);
			��_��Ϸ��ͼ[x][y].������ɫ = 0xFFFFFF;
			i++;
			if (��_��Ϸ��ͼ[x][y].��ͼͨ�� == 0)
				��_��Ϸ��ͼ[x][y].������ɫ = 0x000000;
		}
	}
}
VOID Ѱ·_��ʾ��ͼ(vector<vector<��Ϸ��ͼ>> ��_��ͼ����, DWORD ��_����, DWORD ��_�߶�, vector<vector<��Ϸ��ͼ>>& ��_��ͼ��ǩ)
{
	��_��ͼ��ǩ.clear();
	��_��ͼ��ǩ.resize(��_���� * 3);
	for (DWORD x = 0; x < ��_���� * 3; x++)
	{
		��_��ͼ��ǩ[x].resize(��_�߶� * 3);
	}
	for (DWORD y = 0; y < ��_�߶�; y++)
	{
		for (DWORD x = 0; x < ��_����; x++)
		{
			��_��ͼ��ǩ[(x + 1) * 3 - 2][(y + 1) * 3 - 2].������ɫ = 0xFFFFFF;
			if (��_��ͼ����[x][y].��ͼ���)
				��_��ͼ��ǩ[(x + 1) * 3 - 3][(y + 1) * 3 - 2].������ɫ = 0xFFFFFF;
			if (��_��ͼ����[x][y].��ͼ�ұ�)
				��_��ͼ��ǩ[(x + 1) * 3 - 1][(y + 1) * 3 - 2].������ɫ = 0xFFFFFF;
			if (��_��ͼ����[x][y].��ͼ�ϱ�)
				��_��ͼ��ǩ[(x + 1) * 3 - 2][(y + 1) * 3 - 3].������ɫ = 0xFFFFFF;
			if (��_��ͼ����[x][y].��ͼ�±�)
				��_��ͼ��ǩ[(x + 1) * 3 - 2][(y + 1) * 3 - 1].������ɫ = 0xFFFFFF;
		}
	}
}
VOID Ѱ·_·���㷨(vector<vector<��Ϸ��ͼ>> ��_��ͼ��ǩ, ������ ��_��ͼ���, ������ ��_��ͼ�յ�, DWORD ��_����, DWORD ��_�߶�, vector<������>& ��_�߷�����)
{
	BOOL �Ѵ��ڿ����б�, �Ѵ��ڹر��б�;
	������ ���������;
	��ͼ�ڵ� �����ڵ�, ��ʱ�ڵ�;
	vector<��ͼ�ڵ�> �����б�, �ر��б�;
	DWORD ��̱�� = 0;
	DWORD ��СFֵ, Ԥ��Gֵ;
	DWORD x, y;
	��ʱ�ڵ�.��ǰ����.x = ��_��ͼ���.x;
	��ʱ�ڵ�.��ǰ����.y = ��_��ͼ���.y;
	��_��ͼ��ǩ[��_��ͼ���.x][��_��ͼ���.y].������ɫ = 0x00FF00;
	��_��ͼ��ǩ[��_��ͼ�յ�.x][��_��ͼ�յ�.y].������ɫ = 0x0000FF;
	�����б�.insert(�����б�.begin(), ��ʱ�ڵ�);
	do
	{
		��СFֵ = 0;
		for (y = 0; y < �����б�.size(); y++)
		{
			if (��СFֵ == 0)
			{
				��СFֵ = �����б�[0].��ͼF��;
				��̱�� = y;
			}
			if (�����б�[y].��ͼF�� < ��СFֵ)
			{
				��СFֵ = �����б�[y].��ͼF��;
				��̱�� = y;
			}
		}
		��ʱ�ڵ� = �����б�[��̱��];
		�����б�.erase(�����б�.begin() + ��̱��);
		�ر��б�.insert(�ر��б�.begin(), ��ʱ�ڵ�);
		if (��ʱ�ڵ�.��ǰ����.x != ��_��ͼ���.x || ��ʱ�ڵ�.��ǰ����.y != ��_��ͼ���.y)
		{
			if (��ʱ�ڵ�.��ǰ����.x != ��_��ͼ�յ�.x || ��ʱ�ڵ�.��ǰ����.y != ��_��ͼ�յ�.y)
			{
				��_��ͼ��ǩ[��ʱ�ڵ�.��ǰ����.x][��ʱ�ڵ�.��ǰ����.y].������ɫ = 0x0080FF;
			}
		}
		for (y = 0; y < �ر��б�.size(); y++)
		{
			if (�ر��б�[y].��ǰ����.x == ��_��ͼ�յ�.x && �ر��б�[y].��ǰ����.y == ��_��ͼ�յ�.y)
			{
				�����ڵ� = �ر��б�[y];
				do
				{
					for (unsigned int x = 0; x < �ر��б�.size(); x++)
					{
						if (�ر��б�[x].��ǰ����.x == �����ڵ�.��������.x && �ر��б�[x].��ǰ����.y == �����ڵ�.��������.y)
						{
							�����ڵ� = �ر��б�[x];
							break;
						}
					}
					if (�����ڵ�.��ǰ����.x != ��_��ͼ���.x || �����ڵ�.��ǰ����.y != ��_��ͼ���.y)
					{
						��_��ͼ��ǩ[�����ڵ�.��ǰ����.x][�����ڵ�.��ǰ����.y].������ɫ = 0x00D8D8;
						��_�߷�����.insert(��_�߷�����.begin(), �����ڵ�.��ǰ����);
					}
				} while (�����ڵ�.��ǰ����.x != ��_��ͼ���.x || �����ڵ�.��ǰ����.y != ��_��ͼ���.y);
				��_�߷�����.insert(��_�߷�����.begin(), ��_��ͼ���);
				��_�߷�����.insert(��_�߷�����.end(), ��_��ͼ�յ�);
				return;
			}
		}
		for (y = 0; y < 4; y++)
		{
			if (y == 0)
			{
				���������.x = ��ʱ�ڵ�.��ǰ����.x;
				���������.y = ��ʱ�ڵ�.��ǰ����.y - 1;
			}
			else if (y == 1)
			{
				���������.x = ��ʱ�ڵ�.��ǰ����.x - 1;
				���������.y = ��ʱ�ڵ�.��ǰ����.y;
			}
			else if (y == 2)
			{
				���������.x = ��ʱ�ڵ�.��ǰ����.x + 1;
				���������.y = ��ʱ�ڵ�.��ǰ����.y;
			}
			else
			{
				���������.x = ��ʱ�ڵ�.��ǰ����.x;
				���������.y = ��ʱ�ڵ�.��ǰ����.y + 1;
			}
			if (���������.x < 0 || ���������.x >(��_���� - 1) || ���������.y < 0 || ���������.y >(��_�߶� - 1))
				continue;
			if (��_��ͼ��ǩ[���������.x][���������.y].������ɫ == 0x000000)
				continue;
			�Ѵ��ڹر��б� = false;
			for (x = 0; x < �ر��б�.size(); x++)
			{
				if (�ر��б�[x].��ǰ����.x == ���������.x && �ر��б�[x].��ǰ����.y == ���������.y)
				{
					�Ѵ��ڹر��б� = true;
					break;
				}
			}
			if (�Ѵ��ڹر��б�)
				continue;
			�Ѵ��ڿ����б� = false;
			for (x = 0; x < �����б�.size(); x++)
			{
				if (�����б�[x].��ǰ����.x == ���������.x && �����б�[x].��ǰ����.y == ���������.y)
				{
					if (���������.x != ��ʱ�ڵ�.��ǰ����.x || ���������.y != ��ʱ�ڵ�.��ǰ����.y)
						Ԥ��Gֵ = 14;
					else
						Ԥ��Gֵ = 10;
					if (��ʱ�ڵ�.��ͼG�� + Ԥ��Gֵ < �����б�[x].��ͼG��)
						�����б�[x].�������� = ��ʱ�ڵ�.��ǰ����;
					�Ѵ��ڿ����б� = true;
					break;
				}
			}
			if (�Ѵ��ڿ����б� == false)
			{
				if (���������.x == ��ʱ�ڵ�.��ǰ����.x || ���������.y == ��ʱ�ڵ�.��ǰ����.y)
					Ԥ��Gֵ = 10;
				else
					Ԥ��Gֵ = 14;
				�����ڵ�.��ͼG�� = ��ʱ�ڵ�.��ͼG�� + Ԥ��Gֵ;
				�����ڵ�.��ͼH�� = ��_��ͼ�յ�.x - ���������.x * 10 + ��_��ͼ�յ�.y - ���������.y * 10;
				�����ڵ�.��ͼF�� = �����ڵ�.��ͼG�� + �����ڵ�.��ͼH��;
				�����ڵ�.��ǰ���� = ���������;
				�����ڵ�.�������� = ��ʱ�ڵ�.��ǰ����;
				�����б�.insert(�����б�.begin(), �����ڵ�);
			}
		}
	} while (�����б�.size() != 0);
}
DWORD Ѱ·_��������(vector<������> ��_ģ���߷�, vector<������>& ��_��ʵ�߷�)
{
	DWORD x, y;
	DWORD k = 0;
	������ ��_��ʱ����;
	for (DWORD i = 0; i < ��_ģ���߷�.size(); i++)
	{
		x = (��_ģ���߷�[i].x + 2) % 3;
		y = (��_ģ���߷�[i].y + 2) % 3;
		if (x == 0 && y == 0)
		{
			��_��ʱ����.x = (��_ģ���߷�[i].x + 2) / 3 - 1;
			��_��ʱ����.y = (��_ģ���߷�[i].y + 2) / 3 - 1;
			��_��ʵ�߷�.insert(��_��ʵ�߷�.begin() + k, ��_��ʱ����);
			k++;
		}
	}
	return(k);
}
BOOL  Ѱ·_�жϷ���(DWORD ��_ͨ��, DWORD ��_����)
{
	unsigned char ��_��������[4];
	unsigned char ��_���򼯺�[16][4] = { { 0, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 1, 1, 0 }, { 1, 0, 0, 0 }, { 1, 1, 0, 0 }, { 1, 0, 1, 0 }, { 1, 1, 1, 0 },
	{ 0, 0, 0, 1 }, { 0, 1, 0, 1 }, { 0, 0, 1, 1 }, { 0, 1, 1, 1 }, { 1, 0, 0, 1 }, { 1, 1, 0, 1 }, { 1, 0, 1, 1 }, { 1, 1, 1, 1 } };
	if (��_ͨ�� >= 0 && ��_ͨ�� <= 15)
		for (int i = 0; i < 4; i++)
			��_��������[i] = ��_���򼯺�[��_ͨ��][i];
	else
		for (int i = 0; i < 4; i++)
			��_��������[i] = 0;
	if (��_��������[��_����] == 1)
		return TRUE;
	else
		return FALSE;
}

DWORD Ѱ·_���㷽��(������ ��_��ǰ����, ������ ��_�¸�����)
{
	DWORD ��_���� = 0;
	DWORD ��_X, ��_Y;
	��_X = ��_��ǰ����.x - ��_�¸�����.x;
	��_Y = ��_��ǰ����.y - ��_�¸�����.y;
	if (��_X == 0 && ��_Y == 0)
	{
		return 4;
	}

	if (��_X == 0)
	{
		if (��_Y == 1)
		{
			��_���� = 2;
		}
		else
		{
			��_���� = 3;
		}
	}
	else if (��_Y == 0)
	{
		if (��_X == 1)
		{
			��_���� = 0;
		}
		else
		{
			��_���� = 1;
		}
	}
	return ��_����;
}

VOID �����ͼ(int ����ID)
{
	__int64 ˳ͼ���� = ˳ͼCall(����ID);
	__int64 ����ṹ = ˳ͼ����;

	int ��ʼX = _ReadInt(����ṹ + 0);
	int ��ʼY = _ReadInt(����ṹ + 4);
	int ����X = _ReadInt(����ṹ + 8);
	int ����Y = _ReadInt(����ṹ + 12);

	//  '0��
	int X = 0;
	int Y = 0;
	if (����ID == 0)
	{
		X = ��ʼX + ����X + 20;
		Y = ��ʼY + ����Y / 2;
	}
	// 1��
	if (����ID == 1)
	{
		X = ��ʼX - 20;
		Y = ��ʼY + ����Y / 2;
	}
	// 2��
	if (����ID == 2)
	{

		X = ��ʼX + ����X / 2;
		Y = ��ʼY + ����Y + 20;
	}
	// 2��
	if (����ID == 3)
	{
		X = ��ʼX + ����X / 2;
		Y = ��ʼY - 20;
	}
	����Call(X, Y, 0);
	Sleep(100);
	����Call(��ʼX + ����X / 2, ��ʼY, 0);
}