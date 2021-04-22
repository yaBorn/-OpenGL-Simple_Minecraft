#pragma once
#include <GL/freeglut.h>
#include <math.h>
const float pi = 3.1415926f;
#define CRAMERA_DISTANCE 66666 //�������Ӿ�

//��������ϵ����Ϊ ��z�ᣬˮƽ��xoy

//��ṹ�� (����һ�������������xyz)
struct pointXYZ {
	int x, y, z;
};

//�������
class camera {
private:
	//����ͶӰ�ռ�Ĳ���
	float win_long, win_wide;
	float space_long = 1000000;
	float space_wide = 1000000;
	float space_high = 1000000;
	
	//������ӽ�����(x-per_x ,y-per_y ,z-per_z)
	float x, y, z;
	float per_x, per_y, per_z;
	
	void camera_Vector_Unitization();//��λ���������

public:
	camera();//����

	float out_x();//��������������
	float out_y();
	float out_z();
	float out_per_x();
	float out_per_y();
	float out_per_z();

	pointXYZ point_Front();//��ײ����������ǰ�����ҵ�
	pointXYZ point_Front_XOY();
	pointXYZ point_Rear();
	pointXYZ point_Left();
	pointXYZ point_Right();

	void set_light();//��ҹ�Դ
	void draw_Sky(GLuint sky,bool day);//�������
	void draw_Sight();//����׼��

	void get_window_Size(float winlong, float winwide);//��ȡ���ڴ�С
	void set_projectionSpace(bool projectWay);//����ͶӰ�ռ�(֮ǰҪ��ȡ���ڴ�С)
	void set_lookAt();//�����趨�趨���

	void move_Front_to_Back(float distance);//�ƶ�
	void move_Front_to_Back_XOY(float distance);
	void move_Right_to_Left(float distance);
	void move_Up_to_Down(float distance);

	void turn_Right_to_Left(float angle);//ת��
	void turn_Up_to_Down(float angle);
};
