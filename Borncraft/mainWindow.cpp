#include <gl/GLUT.H>
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include "camera.h"
#include "objectList.h"
#pragma comment(lib, "Winmm.lib")
HWND hWnd;//��Ⱦ���ھ��
int win_id;//��Ⱦ����id
int win_id_instruct;//˵���Ӵ���id
GLuint instruction;//˵������

//�Ӵ�����
float win_Long_instruct = 600;
float win_Wide_instruct = 400;
float win_Long = 1980*2 / 3;
float win_Wide = 1080 / 2 + 200;

camera playerCamera;
objectList objectlist;
bool isDay = true;

//��Ⱦ���ڳ�ʼ��
void Initial(void)
{
	glutSetWindow(win_id);//�ര�ڣ��������㴰��

	glEnable(GL_CULL_FACE);//�����޳�
	glEnable(GL_COLOR_MATERIAL);//������ģ����ɫ������
	glEnable(GL_DEPTH_TEST);//������Ȳ���
	glDepthFunc(GL_LESS);//��ʵ�����е�ǰ��

	objectlist.set_place();//��ʼ��������������
	objectlist.load_texture();//��������
	objectlist.creat_Display_Lists();  //������ʾ�б� �� ����

	glClearColor(1.0, 0.5, 0.5, 0.1f);//����

	//����ͶӰ�ռ�
	playerCamera.get_window_Size(win_Long, win_Wide);
	playerCamera.set_projectionSpace(TRUE);
	cout << endl << "�Ҽ������˵�" << endl;
}
//��Ⱦ���ڻ���
void myDisplay(void)
{
	glutSetWindow(win_id);//�ര�ڣ��������㴰��
	glViewport(0, 0, win_Long, win_Wide);//�ӿ�
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//��ɫ����Ȼ������

	//�趨��λ
	playerCamera.set_lookAt();
	
	//���
	playerCamera.draw_Sky(objectlist.Sky, isDay);
	
	//����׼��
	playerCamera.draw_Sight();
	
	//��Դ
	if (!isDay) {
		playerCamera.set_light();//��ҹ�Դ
	}

	//��ʾ�б�
	for (int i = 1; i <= objectlist.diamondNum + 2; i++) {
		glCallList(i);
	}

	glutSwapBuffers();   //˫����ˢ��
	glDisable(GL_LIGHTING);//�رյ�Դ
}

//����˵�����ڳ�ʼ��
void Inital_instruct() {
	glutSetWindow(win_id_instruct);
	glClearColor(0.8, 0.8, 0.8, 0.0f);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, win_Long_instruct, 0.0, win_Wide_instruct);
	instruction = texture_Load_Texture("texture/instruction.bmp");
}
//����˵�����ڻ���
void instructDisplay(void) {
	glutSetWindow(win_id_instruct);
	glViewport(0, 0, win_Long_instruct, win_Wide_instruct);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_ALPHA_TEST);//����ALPHA
	glAlphaFunc(GL_GREATER, 0.9f);
	glEnable(GL_TEXTURE_2D);//����������
	glBindTexture(GL_TEXTURE_2D, instruction);//������
	glBegin(GL_QUADS);
	glColor3f(0.8, 0.8, 0.8);
	glTexCoord2f(1.0, 1.0); glVertex3f(win_Long_instruct, win_Wide_instruct, 0);
	glTexCoord2f(1.0, 0.0); glVertex3f(win_Long_instruct, 0, 0);
	glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
	glTexCoord2f(0.0, 1.0); glVertex3f(0, win_Wide_instruct, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
	glutSwapBuffers();
}

bool button_MIDDLE_Down = false;
int rx , ry ;//��¼�ϴλص����λ��
float window_x, window_y;//��Ļ����
//�����ص�
void OnMouse(int button, int state, int x, int y)
{
	glutSetWindow(win_id);//�ര�ڣ��������㴰��

	rx = x;
	ry = y;
	//�����м����ƶ��ӽǿ���
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		button_MIDDLE_Down = !button_MIDDLE_Down;
		if (button_MIDDLE_Down) {//�˵�����
			glutDetachMenu(GLUT_RIGHT_BUTTON);
		}
		else {
			glutAttachMenu(GLUT_RIGHT_BUTTON);
		}
	}
	//�����������ӷ���
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		objectlist.add_place(
			playerCamera.out_x(),
			playerCamera.out_y(),
			playerCamera.out_z(),
			playerCamera.out_per_x(),
			playerCamera.out_per_y(),
			playerCamera.out_per_z());
	}
	//�����Ҽ���ɾ������
	if (button_MIDDLE_Down && button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		objectlist.delete_place(
			playerCamera.out_x(),
			playerCamera.out_y(),
			playerCamera.out_z(),
			playerCamera.out_per_x(),
			playerCamera.out_per_y(),
			playerCamera.out_per_z());
	}
	return;
}
//�ƶ��ص� �����ӽ�
void OnMotion(int x, int y)
{
	glutSetWindow(win_id);//�ര�ڣ��������㴰��

	if (button_MIDDLE_Down) {
		SetCursor(LoadCursor(NULL, "cursor1.cur"));//�������͸��
		float x_move = (x - rx) / 4;//������ת����
		float y_move = (y - ry) / 4;
		if (x_move < 10 && y_move < 10 && -10 < x_move && -10 < y_move) {
			playerCamera.turn_Right_to_Left(x_move);
			playerCamera.turn_Up_to_Down(y_move);
		}
		if (x + win_Long_instruct >= win_Long ||
			y + win_Wide_instruct >= win_Wide ||
			x - win_Long_instruct <= 0 ||
			y - win_Wide_instruct <= 0) {//��굽�ﴰ�ڱ߽總��ʱ
			window_x = glutGet(GLUT_WINDOW_X);
			window_y = glutGet(GLUT_WINDOW_Y);
			SetCursorPos(window_x + (win_Long / 2), window_y + (win_Wide / 2));
			rx = win_Long / 2;
			ry = win_Wide / 2;
			glutPostRedisplay();
			return;
		}
	}
	rx = x;
	ry = y;
	glutPostRedisplay();
	return;
}
//���ֻص� ���Ƶ�������
void onMouseWheel(int button, int dir, int x, int y)
{
	glutSetWindow(win_id);//�ര�ڣ��������㴰��

	if (dir > 0) {
		objectlist.diamondChoosed -= 1;
		if (0 == objectlist.diamondChoosed) {
			objectlist.diamondChoosed = objectlist.diamondNum;
		}
	}
	if (dir < 0) {
		objectlist.diamondChoosed += 1;
		if (objectlist.diamondNum+1 == objectlist.diamondChoosed) {
			objectlist.diamondChoosed = 1;
		}
	}
}

//���̻ص�
void keyBoard(unsigned char key, int x, int y) {
	glutSetWindow(win_id);//�ര�ڣ��������㴰��

	float distance = 10;
	switch (key) {
		//�ж����������ĵ㴦�Ƿ��з��飨��ײ���ԣ�
	case 'q':
		if (0 == objectlist.judge_isDiamond(
			playerCamera.point_Front().x,
			playerCamera.point_Front().y,
			playerCamera.point_Front().z) &&
			0 == objectlist.judge_isDiamond(
				playerCamera.point_Front().x,
				playerCamera.point_Front().y,
				playerCamera.point_Front().z - 50)) {
			playerCamera.move_Front_to_Back(distance);;
		}break;
	case 'w':
		if (0 == objectlist.judge_isDiamond(
			playerCamera.point_Front_XOY().x,
			playerCamera.point_Front_XOY().y,
			playerCamera.point_Front_XOY().z) &&
			0 == objectlist.judge_isDiamond(
				playerCamera.point_Front_XOY().x,
				playerCamera.point_Front_XOY().y,
				playerCamera.point_Front_XOY().z - 50)) {
			playerCamera.move_Front_to_Back_XOY(distance);
		}break;
	case 's':
		if (0 == objectlist.judge_isDiamond(
			playerCamera.point_Rear().x,
			playerCamera.point_Rear().y,
			playerCamera.point_Rear().z) &&
			0 == objectlist.judge_isDiamond(
				playerCamera.point_Rear().x,
				playerCamera.point_Rear().y,
				playerCamera.point_Rear().z - 50)) {
			playerCamera.move_Front_to_Back_XOY(-distance);
		}break;

	case 'a':
		if (0 == objectlist.judge_isDiamond(
			playerCamera.point_Left().x,
			playerCamera.point_Left().y,
			playerCamera.point_Left().z) &&
			0 == objectlist.judge_isDiamond(
				playerCamera.point_Left().x,
				playerCamera.point_Left().y,
				playerCamera.point_Left().z - 50)) {
			playerCamera.move_Right_to_Left(distance);
		}break;
	case 'd':
		if (0 == objectlist.judge_isDiamond(
			playerCamera.point_Right().x,
			playerCamera.point_Right().y,
			playerCamera.point_Right().z) &&
			0 == objectlist.judge_isDiamond(
				playerCamera.point_Right().x,
				playerCamera.point_Right().y,
				playerCamera.point_Right().z)) {
			playerCamera.move_Right_to_Left(-distance);
		}break;

	case 'e':
		if (0 == objectlist.judge_isDiamond(
			playerCamera.out_x(),
			playerCamera.out_y(),
			playerCamera.out_z() + 25)) {
			playerCamera.move_Up_to_Down(distance);
		}break;
	case 'c':
		if (0 == objectlist.judge_isDiamond(
			playerCamera.out_x(),
			playerCamera.out_y(),
			playerCamera.out_z() - 75)) {
			playerCamera.move_Up_to_Down(-distance);
		}break;
	}
	glutPostRedisplay();
	return;
}

//���ڴ�С�ص�
void changeSize(GLsizei w, GLsizei h){
	glutSetWindow(win_id);//�ര�ڣ��������㴰��

	win_Long = w;
	win_Wide = h;
	playerCamera.get_window_Size(win_Long, win_Wide);
	playerCamera.set_projectionSpace(TRUE);
	glutPostRedisplay();
	return;
}

bool instructOpen = true;
//�˵��ص�
void menu_Events(int option) {
	switch (option) {
	case 1:
		objectlist.save_place();
		break;
	case 2:
		objectlist.load_place();
		objectlist.creat_Display_Lists();
		break;
	case 3:
		objectlist.set_place();
		objectlist.creat_Display_Lists();
		cout << "�������" << endl;
		break;
	case 4:
		isDay = true;
		break;
	case 5:
		isDay = false;
		break;
	case 6:
		if (!instructOpen) {
			instructOpen = true;
			win_id_instruct = glutCreateSubWindow(win_id, 0, 0, win_Long_instruct, win_Wide_instruct);
			Inital_instruct();
			glutDisplayFunc(&instructDisplay);
		}
		break;
	case 7:
		if (instructOpen) {
			instructOpen = false;
			glutDestroyWindow(win_id_instruct);
		}
		break;
	case 8:
		MessageBox(hWnd, "ͼ��ѧ\nBorncraft\n@���", "����:", MB_OK);
		break;
	}
}
//���ò˵�
void menu_Set() {
	glutCreateMenu(&menu_Events);
	//���˵�������Ŀ
	glutAddMenuEntry("Save", 1);
	glutAddMenuEntry("Load", 2);
	glutAddMenuEntry("Inital diamond", 3);
	glutAddMenuEntry("--------------", 0);
	glutAddMenuEntry("Day", 4);
	glutAddMenuEntry("Night", 5);
	glutAddMenuEntry("--------------", 0);
	glutAddMenuEntry("Instructions  open", 6);
	glutAddMenuEntry("Instructions  close", 7);
	glutAddMenuEntry("--------------", 0);
	glutAddMenuEntry("About", 8);
	// �Ѳ˵�������Ҽ�����������
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char * argv[])
{
	PlaySound("texture\\bgm.wav", GetModuleHandle(NULL), SND_ASYNC | SND_LOOP | SND_FILENAME);

	glutInit(&argc, argv);//glut���ʼ��
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);//RGBAģʽ��˫����

	glutInitWindowPosition(500, 200);//����λ��
	glutInitWindowSize(win_Long, win_Wide);//���ڴ�С
	
	win_id = glutCreateWindow("���-Broncraft");//�������ڣ����ڱ���
	hWnd = GetActiveWindow();//��ȡ���ƴ��ھ��
	Initial();//��ʼ������
	glutDisplayFunc(&myDisplay);//myDisplayָ��Ϊ��ǰ������ʾ���ݺ���
	glutKeyboardFunc(&keyBoard);//�����¼��ص�
	glutMouseFunc(&OnMouse);  //��갴���¼��ص�
	glutPassiveMotionFunc(&OnMotion);//����ƶ��¼��ص�
	glutMouseWheelFunc(&onMouseWheel);//�����ֻص�����
	glutReshapeFunc(&changeSize);//���ڴ�С�¼��ص�
	
	menu_Set();//���ò˵�

	//�Ӵ���
	win_id_instruct = glutCreateSubWindow(win_id, 0, 0, win_Long_instruct, win_Wide_instruct);
	Inital_instruct();
	glutDisplayFunc(&instructDisplay);


	glutMainLoop();//���ڿ�����У��ص���������
	return 0;
}