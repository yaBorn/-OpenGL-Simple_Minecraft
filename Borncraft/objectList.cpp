#include "objectList.h"

//�浵 ����
void objectList::load_place()
{
	place_Diamond_half.clear();
	place_Diamond_grass.clear();
	place_Diamond_plank.clear();
	place_Tree.clear();

	if (_access("save/", 0) == -1) {
		cout << "δ�ҵ��浵" << endl;
	}
	string s;
	coordinate p;
	ifstream file;

	file.open("save/diamondGrass.txt");
	if (!file.is_open()) {
		cout << "�浵 ȱʧ" << endl;
		return;
	}
	while (getline(file, s)) {
		p.x = atoi(s.c_str());
		getline(file, s);
		p.y = stoi(s.c_str());
		getline(file, s);
		p.z = stoi(s.c_str());
		place_Diamond_grass.insert(p);
	}
	file.close();

	file.open("save/diamondPlank.txt");
	if (!file.is_open()) {
		cout << "�浵 ȱʧ" << endl;
		return;
	}
	while (getline(file, s)) {
		p.x = atoi(s.c_str());
		getline(file, s);
		p.y = stoi(s.c_str());
		getline(file, s);
		p.z = stoi(s.c_str());
		place_Diamond_plank.insert(p);
	}
	file.close();

	file.open("save/tree.txt");
	if (!file.is_open()) {
		cout << "�浵 ȱʧ" << endl;
		return;
	}
	while (getline(file, s)) {
		p.x = atoi(s.c_str());
		getline(file, s);
		p.y = stoi(s.c_str());
		getline(file, s);
		p.z = stoi(s.c_str());
		place_Tree.insert(p);
	}
	file.close();

	file.open("save/half.txt");
	if (!file.is_open()) {
		cout << "�浵 ȱʧ" << endl;
		return;
	}
	while (getline(file, s)) {
		p.x = atoi(s.c_str());
		getline(file, s);
		p.y = stoi(s.c_str());
		getline(file, s);
		p.z = stoi(s.c_str());
		place_Diamond_half.insert(p);
	}
	file.close();

	cout << "��ȡ���" << endl;
}
void objectList::save_place()
{
	if (_access("save/", 0) == -1) {
		_mkdir("save");
	}
	ofstream file;
	file.open("save/diamondGrass.txt", ios::trunc);
	if (!file.is_open()) {
		cout << "�ݷ��鴢�� ʧ��" << endl;
		return;
	}
	for (it = place_Diamond_grass.begin(); it != place_Diamond_grass.end(); it++) {
		file << (*it).x << endl << (*it).y << endl << (*it).z << endl;
	}
	file.close();

	file.open("save/diamondPlank.txt", ios::trunc);
	if (!file.is_open()) {
		cout << "ľ���鴢�� ʧ��" << endl;
		return;
	}
	for (it = place_Diamond_plank.begin(); it != place_Diamond_plank.end(); it++) {
		file << (*it).x << endl << (*it).y << endl << (*it).z << endl;
	}
	file.close();

	file.open("save/tree.txt", ios::trunc);
	if (!file.is_open()) {
		cout << "���������� ʧ��" << endl;
		return;
	}
	for (it = place_Tree.begin(); it != place_Tree.end(); it++) {
		file << (*it).x << endl << (*it).y << endl << (*it).z << endl;
	}
	file.close();

	file.open("save/half.txt", ios::trunc);
	if (!file.is_open()) {
		cout << "��ש���� ʧ��" << endl;
		return;
	}
	for (it = place_Diamond_half.begin(); it != place_Diamond_half.end(); it++) {
		file << (*it).x << endl << (*it).y << endl << (*it).z << endl;
	}
	file.close();

	cout << "�������" << endl;
}

//��������
void objectList::load_texture()
{
	set_treeGrammar();
	Diamond_grass = texture_Load_Texture("texture/diamondGrass.bmp");
	Diamond_plank = texture_Load_Texture("texture/diamondPlank.bmp");
	Branch = texture_Load_Texture("texture/treeBranch.bmp");
	Leaf = texture_Load_Texture("texture/treeLeaf.bmp");
	Sky = texture_Load_Texture("texture/sky.bmp");
}

//��ʼ��λ�ò���
void objectList::set_place()
{
	place_Diamond_half.clear();
	place_Diamond_grass.clear();
	place_Diamond_plank.clear();
	place_Tree.clear();
	diamondChoosed = 1;//��ʼ��ѡ��1��ŷ���
	coordinate setPlace;
	for (setPlace.z = 0; setPlace.z <= 0; setPlace.z++) {
		for (setPlace.y = 0; setPlace.y <= 100; setPlace.y++) {
			for (setPlace.x = 0; setPlace.x <= 100; setPlace.x++) {
				place_Diamond_grass.insert(setPlace);
			}
		}
	}
}

//�ж��������ڵĵ�λ��ռ��Ƿ���Ʒ���
int objectList::judge_isDiamond(float x, float y, float z)
{
	coordinate place;
	place.x = (int)x / 50;
	place.y = (int)y / 50;
	place.z = (int)z / 50;
	if (place_Diamond_grass.find(place) != place_Diamond_grass.end()) {
		//�з���
		return 1;
	}
	if (place_Diamond_plank.find(place) != place_Diamond_plank.end()) {
		return 2;
	}
	if (place_Tree.find(place) != place_Tree.end()) {
		return 3;
	}
	if (place_Diamond_half.find(place) != place_Diamond_half.end()) {
		return 4;
	}
	return 0;
}

//��ӣ�ɾ������
void objectList::add_place(float x, float y, float z, float per_x, float per_y, float per_z) 
{
	//x,y,z->px,py,pz ������ ȡ�ɽ���Զ �����50���� n���� �ж�isDiamond
	//ȡisDiamond����һ������
	float vectorLong = sqrt(pow(per_x - x, 2) + pow(per_y - y, 2) + pow(per_z - z, 2));
	float disX = (per_x - x) * sqrt(pow(50, 2)*3) / vectorLong;
	float disY = (per_y - y) * sqrt(pow(50, 2)*3) / vectorLong;
	float disZ = (per_z - z) * sqrt(pow(50, 2)*3) / vectorLong;
	float exX, exY, exZ;

	for (int i = 1; i <= 50; i++) {
		exX = x + (i*disX/10);
		exY = y + (i*disY/10);
		exZ = z + (i*disZ/10);
		if (judge_isDiamond(exX, exY, exZ)!=0 && i != 1) {//�õ���Ʒ���
			coordinate place;
			place.x = (int)(exX - disX/10) / 50;
			place.y = (int)(exY - disY/10) / 50;
			place.z = (int)(exZ - disZ/10) / 50;
			switch (diamondChoosed)
			{
			case 1:			
				place_Diamond_grass.insert(place);//�����������place
				glDeleteLists(1, 1);
				glNewList(1, GL_COMPILE);//������ʾ�б�
				for (it = place_Diamond_grass.begin(); it != place_Diamond_grass.end(); it++) {
					glPushMatrix();
					glTranslatef(50 * (*it).x, 50 * (*it).y, 50 * (*it).z);
					draw_Diamond_grass();
					glPopMatrix();
				}
				glEndList();
				break;
			case 2:
				place_Diamond_plank.insert(place);
				glDeleteLists(2, 1);
				glNewList(2, GL_COMPILE);//������ʾ�б�
				for (it = place_Diamond_plank.begin(); it != place_Diamond_plank.end(); it++) {
					glPushMatrix();
					glTranslatef(50 * (*it).x, 50 * (*it).y, 50 * (*it).z);
					draw_Diamond_plank();
					glPopMatrix();
				}
				glEndList();
				break;
			case 3:
				place_Tree.insert(place);//�����������place
				glDeleteLists(3, 1);
				glNewList(3, GL_COMPILE);//������ʾ�б�
				for (it = place_Tree.begin(); it != place_Tree.end(); it++) {
					glPushMatrix();
					glTranslatef(50 * (*it).x, 50 * (*it).y, 50 * (*it).z);
					glTranslatef(25, 25, 0);
					draw_Tree(tree_grammar);
					glPopMatrix();
				}
				glEndList();
				break;
			case 4:
				place_Diamond_half.insert(place);//�����������place
				glDeleteLists(4, 1);
				glNewList(4, GL_COMPILE);//������ʾ�б�
				for (it = place_Diamond_half.begin(); it != place_Diamond_half.end(); it++) {
					glPushMatrix();
					glTranslatef(50 * (*it).x, 50 * (*it).y, 50 * (*it).z);
					draw_Diamind_half();
					glPopMatrix();
				}
				glEndList();
				break;
			}
			glutPostRedisplay();
			return;
		}
	}
}
void objectList::delete_place(float x, float y, float z, float per_x, float per_y, float per_z)
{
	//x,y,z->px,py,pz ������ ȡ�ɽ���Զ �����50���� n���� �ж�isDiamond
	//ȡisDiamond����һ������
	float vectorLong = sqrt(pow(per_x - x, 2) + pow(per_y - y, 2) + pow(per_z - z, 2));
	float disX = (per_x - x) * sqrt(pow(50, 2) * 3) / vectorLong;
	float disY = (per_y - y) * sqrt(pow(50, 2) * 3) / vectorLong;
	float disZ = (per_z - z) * sqrt(pow(50, 2) * 3) / vectorLong;
	float exX, exY, exZ;//ȡ����ɢ��
	for (int i = 1; i <= 50; i++) {
		exX = x + (i*disX / 10);
		exY = y + (i*disY / 10);
		exZ = z + (i*disZ / 10);
		int diamond = judge_isDiamond(exX, exY, exZ);
		if (diamond != 0 && i != 1) {//�õ��ڷ����ڣ���=1���������ù����ĵ�
			coordinate place;
			place.x = (int)exX / 50;
			place.y = (int)exY / 50;
			place.z = (int)exZ / 50;
			switch (diamond)
			{
			case 1:
				place_Diamond_grass.erase(place);//�����������place
				glDeleteLists(1, 1);
				glNewList(1, GL_COMPILE);//������ʾ�б�
				for (it = place_Diamond_grass.begin(); it != place_Diamond_grass.end(); it++) {
					glPushMatrix();
					glTranslatef(50 * (*it).x, 50 * (*it).y, 50 * (*it).z);
					draw_Diamond_grass();
					glPopMatrix();
				}
				glEndList();
				break;
			case 2:
				place_Diamond_plank.erase(place);
				glDeleteLists(2, 1);
				glNewList(2, GL_COMPILE);//������ʾ�б�
				for (it = place_Diamond_plank.begin(); it != place_Diamond_plank.end(); it++) {
					glPushMatrix();
					glTranslatef(50 * (*it).x, 50 * (*it).y, 50 * (*it).z);
					draw_Diamond_plank();
					glPopMatrix();
				}
				glEndList();
				break;
			case 3:
				place_Tree.erase(place);//�����������place
				glDeleteLists(3, 1);
				glNewList(3, GL_COMPILE);//������ʾ�б�
				for (it = place_Tree.begin(); it != place_Tree.end(); it++) {
					glPushMatrix();
					glTranslatef(50 * (*it).x, 50 * (*it).y, 50 * (*it).z);
					glTranslatef(25, 25, 0);
					draw_Tree(tree_grammar);
					glPopMatrix();
				}
				glEndList();
				break;
			case 4:
				place_Diamond_half.erase(place);
				glDeleteLists(4, 1);
				glNewList(4, GL_COMPILE);
				for (it = place_Diamond_half.begin(); it != place_Diamond_half.end(); it++) {
					glPushMatrix();
					glTranslatef(50 * (*it).x, 50 * (*it).y, 50 * (*it).z);
					draw_Diamind_half();
					glPopMatrix();
				}
				glEndList();
				break;
			}
			glutPostRedisplay();
			return;
		}
	}
}

//������ʾ�б�
void objectList::creat_Display_Lists()
{
	glDeleteLists(1, diamondNum + 2);
	if (!glIsList((GLuint)1)) {//�ݷ���
		glNewList(1, GL_COMPILE);
		for (it = place_Diamond_grass.begin(); it != place_Diamond_grass.end(); it++) {
			glPushMatrix();
			glTranslatef(50 * (*it).x, 50 * (*it).y, 50 * (*it).z);
			draw_Diamond_grass();
			glPopMatrix();
		}
		glEndList();
	}
	if (!glIsList((GLuint)2)) {//ľ�巽��
		glNewList(2, GL_COMPILE);
		for (it = place_Diamond_plank.begin(); it != place_Diamond_plank.end(); it++) {
			glPushMatrix();
			glTranslatef(50 * (*it).x, 50 * (*it).y, 50 * (*it).z);
			draw_Diamond_plank();
			glPopMatrix();
		}
		glEndList();
	}
	if (!glIsList((GLuint)3)) {//��
		glNewList(3, GL_COMPILE);
		for (it = place_Tree.begin(); it != place_Tree.end(); it++) {
			glPushMatrix();
			glTranslatef(50 * (*it).x,50 * (*it).y, 50 * (*it).z);
			glTranslatef(25, 25, 0);
			draw_Tree(tree_grammar);
			glPopMatrix();
		}
		glEndList();
	}
	if (!glIsList((GLuint)4)) {//��ש
		glNewList(4, GL_COMPILE);
		for (it = place_Diamond_half.begin(); it != place_Diamond_half.end(); it++) {
			glPushMatrix();
			glTranslatef(50 * (*it).x, 50 * (*it).y, 50 * (*it).z);
			draw_Diamind_half();
			glPopMatrix();
		}
		glEndList();
	}
	if (!glIsList((GLuint)5)) {//����
		glNewList(5, GL_COMPILE);
		draw_Grid();
		glEndList();
	}
	if (!glIsList((GLuint)6)) {//ƽ������
		glNewList(6, GL_COMPILE);
		draw_Texture();
		glEndList();
	}
}

//ƽ������
void objectList::draw_Texture()
{
	GLfloat earth_mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //������ʵĻ�������ɫ��ƭ��ɫ	
	GLfloat earth_mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //������ʵ����������ɫ��ƫ��ɫ	
	GLfloat earth_mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };   //������ʵľ��淴�����ɫ����ɫ	
	GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //������ʵķ������ɫ��Ϊ0	
	GLfloat earth_mat_shininess = 30.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);

	glEnable(GL_ALPHA_TEST);//����ALPHA
	glAlphaFunc(GL_GREATER, 0.9f);
	glEnable(GL_TEXTURE_2D);//����������
	glBindTexture(GL_TEXTURE_2D, Diamond_grass);//������
	glBegin(GL_QUADS);//���ƶ����
	glColor3f(0.5, 0.5, 0.5);
	glNormal3f(0, 0, 1);//ָ��������
	glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 100);//������������������Ӧ
	glTexCoord2f(1.0, 0.0); glVertex3f(99, 0, 100);
	glTexCoord2f(1.0, 1.0); glVertex3f(99, 132, 100);
	glTexCoord2f(0.0, 1.0); glVertex3f(0, 132, 100);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
}
//����
void objectList::draw_Grid()
{
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);//��ɫx��
	glVertex3f(-DISTANCE, 0, 0); glVertex3f(DISTANCE, 0, 0);
	glColor3f(0, 1, 0);//��ɫy��
	glVertex3f(0, -DISTANCE, 0); glVertex3f(0, DISTANCE, 0);
	glColor3f(0, 0.7, 1);//��ɫz��
	glVertex3f(0, 0, -DISTANCE); glVertex3f(0, 0, DISTANCE);
	glColor3f(0.5, 0.5, 0.5);
	for (int i = 0; i * 50 <= DISTANCE; i++) {
		glVertex2f(i * 50, -DISTANCE); glVertex2f(i * 50, DISTANCE);
		glVertex2f(-i * 50, -DISTANCE); glVertex2f(-i * 50, DISTANCE);
	}
	for (int i = 0; i * 50 <= DISTANCE; i++) {
		glVertex2f(-DISTANCE, i * 50); glVertex2f(DISTANCE, i * 50);
		glVertex2f(-DISTANCE, -i * 50); glVertex2f(DISTANCE, -i * 50);
	}
	glEnd();
}
//�뷽�� 
void objectList::draw_Diamind_half()
{
	glEnable(GL_ALPHA_TEST);//����ALPHA
	glAlphaFunc(GL_GREATER, 0.9f);
	glEnable(GL_TEXTURE_2D);//����������
	glBindTexture(GL_TEXTURE_2D, Diamond_plank);//������

	glBegin(GL_QUADS);
	//����	
	glNormal3f(0, 0, -1);//����
	glColor3ub(175, 100, 75);
	glTexCoord2f(0.25, 0.0); glVertex3f(0, 0, 0);
	glTexCoord2f(0.25, 0.25); glVertex3f(0, 50, 0);
	glTexCoord2f(0.5, 0.25); glVertex3f(50, 50, 0);
	glTexCoord2f(0.5, 0.0); glVertex3f(50, 0, 0);
	//����A		
	glNormal3f(0, -1, 0);
	glColor3ub(175, 100, 75);
	glTexCoord2f(0.25, 1.0); glVertex3f(0, 0, 0);
	glTexCoord2f(0.5, 1.0); glVertex3f(50, 0, 0);
	glColor3ub(132.5, 140, 67.5);
	glTexCoord2f(0.5, 0.75); glVertex3f(50, 0, 25);
	glTexCoord2f(0.25, 0.75); glVertex3f(0, 0, 25);
	//����B	
	glNormal3f(1, 0, 0);
	glColor3ub(175, 100, 75);
	glTexCoord2f(0.75, 0.75); glVertex3f(50, 0, 0);
	glTexCoord2f(0.75, 0.5); glVertex3f(50, 50, 0);
	glColor3ub(132.55, 140, 67.5);
	glTexCoord2f(0.5, 0.5); glVertex3f(50, 50, 25);
	glTexCoord2f(0.5, 0.75); glVertex3f(50, 0, 25);
	//����C	
	glNormal3f(0, 1, 0);
	glColor3ub(175, 100, 75);
	glTexCoord2f(0.5, 0.25); glVertex3f(50, 50, 0);
	glTexCoord2f(0.25, 0.25); glVertex3f(0, 50, 0);
	glColor3ub(132.5, 140, 67.5);
	glTexCoord2f(0.25, 0.5); glVertex3f(0, 50, 25);
	glTexCoord2f(0.5, 0.5); glVertex3f(50, 50, 25);
	//����D	
	glNormal3f(-1, 0, 0);
	glColor3ub(175, 100, 75);
	glTexCoord2f(0.0, 0.5); glVertex3f(0, 50, 0);
	glTexCoord2f(0.0, 0.75); glVertex3f(0, 0, 0);
	glColor3ub(132.5, 140, 67.5);
	glTexCoord2f(0.25, 0.75); glVertex3f(0, 0, 25);
	glTexCoord2f(0.25, 0.5); glVertex3f(0, 50, 25);
	//����	
	glNormal3f(0, 0, 1);
	glColor3ub(90, 180, 60);
	glTexCoord2f(0.25, 0.75); glVertex3f(0, 0, 25);
	glTexCoord2f(0.5, 0.75); glVertex3f(50, 0, 25);
	glTexCoord2f(0.5, 0.5); glVertex3f(50, 50, 25);
	glTexCoord2f(0.25, 0.5); glVertex3f(0, 50, 25);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
}
//�ݷ���(ע��ÿ�������˳�򣬱����޳�)
void objectList::draw_Diamond_grass()
{
	glEnable(GL_ALPHA_TEST);//����ALPHA
	glAlphaFunc(GL_GREATER, 0.9f);
	glEnable(GL_TEXTURE_2D);//����������
	glBindTexture(GL_TEXTURE_2D, Diamond_grass);//������

	glBegin(GL_QUADS);
	//����	
	glNormal3f(0, 0, -1);//����
	glColor3ub(175, 100, 75);
	glTexCoord2f(0.25, 0.0); glVertex3f(0, 0, 0);
	glTexCoord2f(0.25, 0.25); glVertex3f(0, 50, 0);
	glTexCoord2f(0.5, 0.25); glVertex3f(50, 50, 0);
	glTexCoord2f(0.5, 0.0); glVertex3f(50, 0, 0);
	//����A		
	glNormal3f(0, -1, 0);
	glColor3ub(175, 100, 75);
	glTexCoord2f(0.25, 1.0); glVertex3f(0, 0, 0);
	glTexCoord2f(0.5, 1.0); glVertex3f(50, 0, 0);
	glColor3ub(132.5, 140, 67.5);
	glTexCoord2f(0.5, 0.75); glVertex3f(50, 0, 50);
	glTexCoord2f(0.25, 0.75); glVertex3f(0, 0, 50);
	//����B	
	glNormal3f(1, 0, 0);
	glColor3ub(175, 100, 75);
	glTexCoord2f(0.75, 0.75); glVertex3f(50, 0, 0);
	glTexCoord2f(0.75, 0.5); glVertex3f(50, 50, 0);
	glColor3ub(132.55, 140, 67.5);
	glTexCoord2f(0.5, 0.5); glVertex3f(50, 50, 50);
	glTexCoord2f(0.5, 0.75); glVertex3f(50, 0, 50);
	//����C	
	glNormal3f(0, 1, 0);
	glColor3ub(175, 100, 75);
	glTexCoord2f(0.5, 0.25); glVertex3f(50, 50, 0);
	glTexCoord2f(0.25, 0.25); glVertex3f(0, 50, 0);
	glColor3ub(132.5, 140, 67.5);
	glTexCoord2f(0.25, 0.5); glVertex3f(0, 50, 50);
	glTexCoord2f(0.5, 0.5); glVertex3f(50, 50, 50);
	//����D	
	glNormal3f(-1, 0, 0);
	glColor3ub(175, 100, 75);
	glTexCoord2f(0.0, 0.5); glVertex3f(0, 50, 0);
	glTexCoord2f(0.0, 0.75); glVertex3f(0, 0, 0);
	glColor3ub(132.5, 140, 67.5);
	glTexCoord2f(0.25, 0.75); glVertex3f(0, 0, 50);
	glTexCoord2f(0.25, 0.5); glVertex3f(0, 50, 50);
	//����	
	glNormal3f(0, 0, 1);
	glColor3ub(90, 180, 60);
	glTexCoord2f(0.25, 0.75); glVertex3f(0, 0, 50);
	glTexCoord2f(0.5, 0.75); glVertex3f(50, 0, 50);
	glTexCoord2f(0.5, 0.5); glVertex3f(50, 50, 50);
	glTexCoord2f(0.25, 0.5); glVertex3f(0, 50, 50);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
}
//ľ�巽��
void objectList::draw_Diamond_plank()
{
	glEnable(GL_ALPHA_TEST);//����ALPHA
	glAlphaFunc(GL_GREATER, 0.9f);
	glEnable(GL_TEXTURE_2D);//����������
	glBindTexture(GL_TEXTURE_2D, Diamond_plank);//������

	glBegin(GL_QUADS);
	//����	
	glNormal3f(0, 0, -1);
	glColor3ub(250, 193, 107);
	glTexCoord2f(0.25, 0.0); glVertex3f(0, 0, 0);
	glTexCoord2f(0.25, 0.25); glVertex3f(0, 50, 0);
	glTexCoord2f(0.5, 0.25); glVertex3f(50, 50, 0);
	glTexCoord2f(0.5, 0.0); glVertex3f(50, 0, 0);
	//����A	
	glNormal3f(0, -1, 0);
	glTexCoord2f(0.25, 1.0); glVertex3f(0, 0, 0);
	glTexCoord2f(0.5, 1.0); glVertex3f(50, 0, 0);
	glTexCoord2f(0.5, 0.75); glVertex3f(50, 0, 50);
	glTexCoord2f(0.25, 0.75); glVertex3f(0, 0, 50);
	//����B	
	glNormal3f(1, 0, 0);
	glTexCoord2f(0.75, 0.75); glVertex3f(50, 0, 0);
	glTexCoord2f(0.75, 0.5); glVertex3f(50, 50, 0);
	glTexCoord2f(0.5, 0.5); glVertex3f(50, 50, 50);
	glTexCoord2f(0.5, 0.75); glVertex3f(50, 0, 50);
	//����C	
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.5, 0.25); glVertex3f(50, 50, 0);
	glTexCoord2f(0.25, 0.25); glVertex3f(0, 50, 0);
	glTexCoord2f(0.25, 0.5); glVertex3f(0, 50, 50);
	glTexCoord2f(0.5, 0.5); glVertex3f(50, 50, 50);
	//����D	
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0.0, 0.5); glVertex3f(0, 50, 0);
	glTexCoord2f(0.0, 0.75); glVertex3f(0, 0, 0);
	glTexCoord2f(0.25, 0.75); glVertex3f(0, 0, 50);
	glTexCoord2f(0.25, 0.5); glVertex3f(0, 50, 50);
	//����	
	glNormal3f(0, 0, 1);
	glTexCoord2f(0.25, 0.75); glVertex3f(0, 0, 50);
	glTexCoord2f(0.5, 0.75); glVertex3f(50, 0, 50);
	glTexCoord2f(0.5, 0.5); glVertex3f(50, 50, 50);
	glTexCoord2f(0.25, 0.5); glVertex3f(0, 50, 50);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
}
//�ʷ���
void objectList::draw_Diamond_colour()
{
	glBegin(GL_QUADS);
	//����	
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 50, 0);
	glColor3f(0, 0, 1);
	glVertex3f(50, 50, 0);
	glVertex3f(50, 0, 0);
	//����A		
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(50, 0, 0);
	glColor3f(0, 1, 0);
	glVertex3f(50, 0, 50);
	glVertex3f(0, 0, 50);
	//����B	
	glColor3f(0, 1, 0);
	glVertex3f(50, 0, 0);
	glVertex3f(50, 50, 0);
	glColor3f(0, 1, 1);
	glVertex3f(50, 50, 50);
	glVertex3f(50, 0, 50);
	//����C		
	glColor3f(1, 1, 0);
	glVertex3f(50, 50, 0);
	glVertex3f(0, 50, 0);
	glColor3f(1, 0, 1);
	glVertex3f(0, 50, 50);
	glVertex3f(50, 50, 50);
	//����D	
	glColor3f(1, 0, 1);
	glVertex3f(0, 50, 0);
	glVertex3f(0, 0, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 50);
	glVertex3f(0, 50, 50);
	//����		
	glColor3f(1, 1, 0);
	glVertex3f(0, 0, 50);
	glVertex3f(50, 0, 50);
	glColor3f(0, 0, 1);
	glVertex3f(50, 50, 50);
	glVertex3f(0, 50, 50);
	glEnd();
}
//��
void objectList::tree_Branch(float baseRadius, float topRadius, float height)
{
	GLUquadricObj *tree_obj;
	tree_obj = gluNewQuadric();//���������������
	glBindTexture(GL_TEXTURE_2D, Branch);//������
	gluQuadricTexture(tree_obj, GL_TRUE);
	//glColor3ub(155, 81, 33);
	glColor3ub(125, 125, 125);
	gluCylinder(tree_obj, baseRadius, topRadius, height, 30, 30);//����
	glTranslatef(0.0f, 0.0f, height);
	gluSphere(tree_obj, topRadius, 30, 30);
	gluDeleteQuadric(tree_obj);
}
void objectList::tree_Leaf()
{
	glBindTexture(GL_TEXTURE_2D, Leaf);//������
	//glColor3f(1.0f, 0.0f, 0.0f);
	glColor3ub(125, 125, 125);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(0, 0, 0);
	glTexCoord2f(1.0, 0.0); glVertex3f(10, 10, 0);
	glTexCoord2f(1.0, 1.0); glVertex3f(0, 20, 0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-10, 10, 0);
	glEnd();	
}
void objectList::draw_Tree(string grammar)
{
	glDisable(GL_CULL_FACE);//�����޳�
	glEnable(GL_ALPHA_TEST);//����ALPHA
	glAlphaFunc(GL_GREATER, 0.9f);
	glEnable(GL_TEXTURE_2D);//����������

	float baseRadius = 10, topRadius = 6, height = 200;
	int i = 0;
	while (i < grammar.length()) {
		switch (grammar[i]) {
			//F�������ɣ�X����Ҷ�ӣ�AB�������ɲ�����+-/*%&����任��[]����ջ
		case'F':tree_Branch(baseRadius, topRadius, height); break;
		case'X':tree_Leaf(); break;
		case'A':height *= 0.6; baseRadius *= 0.5; topRadius *= 0.5; break;
		case'B':height /= 0.6; baseRadius /= 0.5; topRadius /= 0.5; break;
		case'+':glRotatef(35, 1, 0, 0); break;
		case'-':glRotatef(-35, 1, 0, 0); break;
		case'*':glRotatef(35, 0, 1, 0); break;
		case'/':glRotatef(-35, 0, 1, 0); break;
		case'%':glRotatef(35, 0, 0, 1); break;
		case'&':glRotatef(-35, 0, 0, 1); break;
		case'[':glPushMatrix(); break;
		case']':glPopMatrix(); break;
		}
		i++;
	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_CULL_FACE);//�����޳�
}
void objectList::set_treeGrammar()
{
	ifstream file("texture/treeGrammar.txt");
	if (!file.is_open()) {
		cout << "�ļ� texture/treeGrammar.txt ��ʧ��" << endl;
		tree_grammar = "";
		return;
	}
	cout << "�ļ� texture/treeGrammar.txt �򿪳ɹ�" << endl;
	stringstream ss;
	ss << file.rdbuf();
	tree_grammar = ss.str();
	file.close();
}
