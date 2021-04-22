#pragma once
#include <GL/freeglut.h>
#include "texture.h"
#include <set>
#include <fstream>
#include <sstream>
#include <io.h>
#include <direct.h>
using namespace std;
#define DISTANCE 9999 //�ռ����

//��Ʒ���� ����Ϊλ�ò���������Ҫ���ļ�,����������ֵ��
class objectList {
private:
	//��������
	struct coordinate {
		int x;
		int y;
		int z;
		//���� < ,���������е�����
		friend bool operator < (const coordinate &n1, const coordinate &n2) {
			if (n1.x != n2.x) {
				return n1.x < n2.x;
			}
			else {
				if (n1.y != n2.y) {
					return n1.y < n2.y;
				}
				else {
					return n1.z < n2.z;
				}
			}
		}
	};

	set<coordinate>::iterator it;//����������
	set<coordinate> place_Diamond_grass;//������������
	set<coordinate> place_Diamond_plank;
	set<coordinate> place_Tree;
	set<coordinate> place_Diamond_half;

public:
	//������
	GLuint Diamond_grass;
	GLuint Diamond_plank;
	GLuint Branch;
	GLuint Leaf;
	GLuint Sky;
	int diamondNum = 4;//��������
	int diamondChoosed;//��ǰѡ��ķ���

	//��ȡ���ش浵
	void load_place();
	void save_place();

	//��������
	void load_texture();
	//��ʼ��λ�ò���
	void set_place();

	//�ж�����x,y,z���ڵĵ�λ��ռ��Ƿ���Ʒ���
	//���ط���������ţ�����0Ϊ������
	int judge_isDiamond(float x, float y, float z);

	//���,ɾ������
	void add_place(float x, float y, float z, float per_x, float per_y, float per_z);
	void delete_place(float x, float y, float z, float per_x, float per_y, float per_z);

	//������ʾ�б�
	void creat_Display_Lists();

private:
	//����ƽ������
	void draw_Texture();
	//��������
	void draw_Grid();
	//���Ʒ���
	void draw_Diamind_half();
	void draw_Diamond_grass();
	void draw_Diamond_plank();
	void draw_Diamond_colour();
	//������
	string tree_grammar;
	void tree_Branch(float baseRadius, float topRadius, float height);
	void tree_Leaf();
	void draw_Tree(string grammar);
	void set_treeGrammar();

};
