#pragma once
#include <GL/freeglut.h>
#include <stdio.h>
#include <iostream>
#define BMP_Header_Length 54  //ͼ���������ڴ���е�ƫ����

//�ж�n�Ƿ�Ϊ2����������
int texture_Power_of_Two(int n);

//��ȡbmp�ļ�������������������
GLuint texture_Load_Texture(const char* file_name);
