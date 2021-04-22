#include "camera.h"

//��λ���������
void camera::camera_Vector_Unitization() {
	float vectorLong = sqrt(pow(per_x - x, 2) + pow(per_y - y, 2) + pow(per_z - z, 2));
	per_x = x + ((per_x - x) / vectorLong);
	per_y = y + ((per_y - y) / vectorLong);
	per_z = z + ((per_z - z) / vectorLong);
}

//����
camera::camera() {
	x = 500;
	y = 500;
	z = 500;
	per_x = 0;
	per_y = 0;
	per_z = 0;
	camera_Vector_Unitization();
}

//�����������
float camera::out_x(){
	return x;
}
float camera::out_y(){
	return y;
}
float camera::out_z(){
	return z;
}
float camera::out_per_x(){
	return per_x;
}
float camera::out_per_y(){
	return per_y;
}
float camera::out_per_z(){
	return per_z;
}

//��ײ����������ǰ�����ҵ�
pointXYZ camera::point_Front()
{
	pointXYZ p;
	p.x = x + ((per_x - x) * 37.5);
	p.y = y + ((per_y - y) * 37.5);
	p.z = z + ((per_z - z) * 37.5);
	return p;
}
pointXYZ camera::point_Front_XOY()
{
	float v_long = sqrt(pow(per_x - x, 2) + pow(per_y - y, 2));
	pointXYZ p;
	p.x = x + ((per_x - x) * 25 / v_long);
	p.y = y + ((per_y - y) * 25 / v_long);
	p.z = z;
	return p;
}
pointXYZ camera::point_Rear()
{
	float v_long = sqrt(pow(per_x - x, 2) + pow(per_y - y, 2));
	pointXYZ p;
	p.x = x - ((per_x - x) * 25 / v_long);
	p.y = y - ((per_y - y) * 25 / v_long);
	p.z = z;
	return p;
}
pointXYZ camera::point_Left()
{
	float v_long = sqrt(pow(per_x - x, 2) + pow(per_y - y, 2));
	pointXYZ p;
	p.x = x + ((y - per_y) * 25 / v_long);
	p.y = y + ((per_x - x) * 25 / v_long);
	p.z = z;
	return p;
}
pointXYZ camera::point_Right()
{
	float v_long = sqrt(pow(per_x - x, 2) + pow(per_y - y, 2));
	pointXYZ p;
	p.x = x - ((y - per_y) * 25 / v_long);
	p.y = y - ((per_x - x) * 25 / v_long);
	p.z = z;
	return p;
}
GLfloat s = 3.0;

//��ҹ�Դ
void camera::set_light()
{
	glPushMatrix();//��������ջ
	glTranslatef(x, y, z);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	GLfloat sun_light_position[] = { 0, 0, 0, 1.0f }; //��Դ��λ������������ϵԲ�ģ����������ʽ	
	GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f }; //RGBAģʽ�Ļ����⣬Ϊ0		
	GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //RGBAģʽ��������⣬ȫ�׹�	
	GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //RGBAģʽ�µľ���� ��ȫ�׹�	
	GLfloat s1 = 1.0;//˥������
	GLfloat s2 = 0.001;
	GLfloat s3 = 0.0;
	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
	glLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION, &s1);
	glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, &s2);
	glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, &s3);
	glEnable(GL_LIGHT0);
	glPopMatrix();
}

//�������
void camera::draw_Sky(GLuint sky,bool day)
{
	glDisable(GL_CULL_FACE);//�ں����ڲ����ر����޳�
	glDisable(GL_DEPTH_TEST);//��������ڵ����ر���ȣ����Ȼ���
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, sky);
	glPushMatrix();
	glTranslatef(x, y, z);//���Ӹ������
	GLUquadricObj *sky_obj;
	sky_obj = gluNewQuadric();//���������������
	gluQuadricTexture(sky_obj, GL_TRUE);
	if (day == true) {
		glColor3f(1.0f, 1.0f, 1.0f);//�൱������
	}
	else {
		glColor3f(0.2f, 0.2f, 0.2f);
	}
	gluSphere(sky_obj, 20, 30, 30);
	gluDeleteQuadric(sky_obj);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

//����׼��
void camera::draw_Sight()
{
	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	glVertex3f(per_x, per_y, per_z);
	glEnd();
}

//��ȡ���ڴ�С
void camera::get_window_Size(float winlong, float winwide) {
	win_long = winlong;
	win_wide = winwide;
}

//����ͶӰ�ռ�(֮ǰҪ��ȡ���ڴ�С)
void camera::set_projectionSpace(bool projectWay) {
	glMatrixMode(GL_PROJECTION);//ͶӰ����Ӧ��
	glLoadIdentity();
	if ( FALSE == projectWay) {
		//��ͶӰ�ռ�
		glOrtho(-space_long, space_long, -space_high, space_high, -space_wide, space_wide);
	}
	else {
		//͸��ͶӰ�ռ�
		gluPerspective(70, win_long / win_wide, 0.1, CRAMERA_DISTANCE / 4);//�趨��Ұ��Զ���룬����Զ�����ضѻ�
	}
}

//�����趨�趨���
void camera::set_lookAt() {
	glMatrixMode(GL_MODELVIEW);	//ģ����ͼ����Ӧ��
	glLoadIdentity();
	gluLookAt(x, y, z, per_x, per_y, per_z, 0, 0, 1);
}

//�ƶ�
void camera::move_Front_to_Back(float distance) {
	float x_past = x;
	float y_past = y;
	float z_past = z;
	x = (per_x - x)*distance + x;
	y = (per_y - y)*distance + y;
	z = (per_z - z)*distance + z;
	per_x = (per_x - x_past)*distance + per_x;
	per_y = (per_y - y_past)*distance + per_y;
	per_z = (per_z - z_past)*distance + per_z;
	//camera_Vector_Unitization();
}
void camera::move_Front_to_Back_XOY(float distance) {
	float x_past = x;
	float y_past = y;
	float v_long = sqrt(pow(per_x - x, 2) + pow(per_y - y, 2));
	x = (per_x - x)*distance / v_long + x;
	y = (per_y - y)*distance / v_long + y;
	per_x = (per_x - x_past)*distance / v_long + per_x;
	per_y = (per_y - y_past)*distance / v_long + per_y;
	//camera_Vector_Unitization();
	//��Ϊ����ά��xoy���ͶӰ
	//������xoy�Ƕ�Խ��per-x��per-yԽС������е�ͶӰԽ����
	//��˳�ͶӰ���ȣ�ʹ���ƶ�����ָ�distance
	//����������������
}
void camera::move_Right_to_Left(float distance) {
	float x_past = x;
	float y_past = y;
	float px_past = per_x;
	float py_past = per_y;
	float v_long = sqrt(pow(per_x - x, 2) + pow(per_y - y, 2));
	x = (y_past - per_y)*distance / v_long + x_past;
	y = (per_x - x_past)*distance / v_long + y_past;
	per_x = (y_past - py_past)*distance / v_long + px_past;
	per_y = (px_past - x_past)*distance / v_long + py_past;
}
void camera::move_Up_to_Down(float distance) {
	z += distance;
	per_z += distance;
}

//ת��
void camera::turn_Right_to_Left(float angle) {
	float x_past = x;
	float y_past = y;
	float px_past = per_x;
	float py_past = per_y;
	per_x = ((px_past - x_past)*cos(angle *pi / 180)) + ((py_past - y_past)*sin(angle*pi / 180)) + x_past;
	per_y = ((py_past - y_past)*cos(angle *pi / 180)) - ((px_past - x_past)*sin(angle*pi / 180)) + y_past;
}
void camera::turn_Up_to_Down(float angle) {
	per_z -= angle * pi / 180;
	camera_Vector_Unitization();
}
