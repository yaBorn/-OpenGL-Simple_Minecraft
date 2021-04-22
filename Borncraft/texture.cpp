#include "texture.h"

//�ж�n�Ƿ�Ϊ2����������
int texture_Power_of_Two(int n)
	{
		if (n <= 0) {
			return 0;
		}
		return (n & (n - 1)) == 0;
	}

//��ȡbmp�ļ�������������������
GLuint texture_Load_Texture(const char * file_name)
	{
		GLint width, height, total_bytes;
		GLubyte* pixels = 0;
		GLuint last_texture_ID = 0, texture_ID = 0;

		// ���ļ������ʧ�ܣ�����	
		FILE* pFile;
		if (fopen_s(&pFile, file_name, "rb")) {
			std::cout << "�ļ� " << file_name << " ����ʧ�� �޷���" << std::endl;
			return 0;
		}

		// ��ȡ�ļ���ͼ��Ŀ�Ⱥ͸߶�	
		fseek(pFile, 0x0012, SEEK_SET);
		fread(&width, 4, 1, pFile);
		fread(&height, 4, 1, pFile);
		fseek(pFile, BMP_Header_Length, SEEK_SET);

		// ����ÿ��������ռ�ֽ����������ݴ����ݼ����������ֽ���	
		GLint line_bytes = width * 3;
		while (line_bytes % 4 != 0) {
			++line_bytes;
		}
		total_bytes = line_bytes * height;

		// �����������ֽ��������ڴ�
		pixels = (GLubyte*)malloc(total_bytes);
		if (0 == pixels) {
			fclose(pFile);
			std::cout << "�ļ� " << file_name << " ����ʧ�� ����Ϊ0" << std::endl;
			return 0;
		}

		// ��ȡ��������	
		if (fread(pixels, total_bytes, 1, pFile) <= 0) {
			free(pixels);
			fclose(pFile);
			std::cout << "�ļ� " << file_name << " ����ʧ�� ����ȱʧ" << std::endl;
			return 0;
		}

		// �Ծ;ɰ汾�ļ��ݣ����ͼ��Ŀ�Ⱥ͸߶Ȳ��ǵ������η�������Ҫ��������
		// ��ͼ���߳�����OpenGL�涨�����ֵ��Ҳ����	
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
		//std::cout << (int)max;
		if (!texture_Power_of_Two(width)
			|| !texture_Power_of_Two(height)
			|| width > max
			|| height > max)
		{
			GLint new_width;
			GLint new_height;
			if (file_name == "sky.bmp"&&max > 4096) {//��պ����������
				new_width = 4096;
				new_height = 4096;
			}
			else {
				new_width = 512;
				new_height = 512; // �涨���ź��µĴ�СΪ�߳���������		
			}
			GLint new_line_bytes, new_total_bytes;
			GLubyte* new_pixels = 0;

			// ����ÿ����Ҫ���ֽ��������ֽ���	
			new_line_bytes = new_width * 3;
			while (new_line_bytes % 4 != 0) {
				++new_line_bytes;
			}
			new_total_bytes = new_line_bytes * new_height;

			// �����ڴ�		
			new_pixels = (GLubyte*)malloc(new_total_bytes);
			if (0 == new_pixels) {
				free(pixels);
				fclose(pFile);
				std::cout << "�ļ� " << file_name << " ����ʧ�� �ڴ����ʧ��" << std::endl;
				return 0;
			}

			// ������������		
			gluScaleImage(GL_RGB,
				width, height, GL_UNSIGNED_BYTE, pixels,
				new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			// �ͷ�ԭ�����������ݣ���pixelsָ���µ��������ݣ�����������width��height		
			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;
		}

		//���ð�ɫΪ͸����0,֮ǰ��ȡ��RGB��������ҪRGBA
		unsigned char* texture = 0;
		texture = (unsigned char*)malloc(width * height * 4);
		for (int m = 0; m < width; m++) {
			for (int j = 0; j < height; j++) {
				//����ɫֵд��   	
				texture[m*width * 4 + j * 4] = pixels[m*width * 3 + j * 3];
				texture[m*width * 4 + j * 4 + 1] = pixels[m*width * 3 + j * 3 + 1];
				texture[m*width * 4 + j * 4 + 2] = pixels[m*width * 3 + j * 3 + 2];

				//����alphaֵ,�����ɫΪ͸��ɫ   
				if (texture[m*width * 4 + j * 4] >= 240
					&& texture[m*width * 4 + j * 4 + 1] >= 240
					&& texture[m*width * 4 + j * 4 + 2] >= 240) {
					texture[m*width * 4 + j * 4 + 3] = 0;//͸����alpha=0  
					//cout << (int)texture[m*width * 4 + j * 4 + 3];
				}
				else {
					texture[m*width * 4 + j * 4 + 3] = 255;//��͸����alpha=255  
					//cout << (int)texture[m*width * 4 + j * 4 + 3];
				}
			}
		}

		// ����һ���µ�������
		glGenTextures(1, &texture_ID);
		if (0 == texture_ID) {
			free(pixels);
			free(texture);
			fclose(pFile);
			std::cout << "�ļ� " << file_name << " ����ʧ�� �������ʧ��" << std::endl;
			return 0;
		}

		// ���µ������������������������
		// �ڰ�ǰ���Ȼ��ԭ���󶨵������ţ��Ա��������лָ�	
		GLint lastTextureID = last_texture_ID;
		glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);
		glBindTexture(GL_TEXTURE_2D, texture_ID);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_BGRA_EXT, GL_UNSIGNED_BYTE, texture);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glBindTexture(GL_TEXTURE_2D, lastTextureID);  //�ָ�֮ǰ�������
		free(pixels);
		free(texture);
		std::cout << "�ļ� " << file_name << " ���سɹ�" << std::endl;
		return texture_ID;
	}