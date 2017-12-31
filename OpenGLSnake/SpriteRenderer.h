#pragma once
#include <iostream>
#include <glad\glad.h>
#include <GLFW/glfw3.h>
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "Transform.h"


class SpriteRenderer
{
private:
	int sprite_width_;
	int sprite_height_;
	int sprite_nr_channels_;
	unsigned int sprite_texture_id_;
	unsigned char *data;
	Transform *transform_;
	unsigned int VAO_, VBO_, EBO_;
	static GLfloat vertices_[];
	static unsigned int indices_[];
	unsigned int shader_program_id_;
private:
	void CheckShaderCompileProcess(GLint shader);
public:
	SpriteRenderer(Transform *trans, const char *sprite);
	void Draw();
};