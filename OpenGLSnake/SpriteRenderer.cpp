#include "SpriteRenderer.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void SpriteRenderer::CheckShaderCompileProcess(GLint shader)
{
	GLint success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR: SHADER COMPILATION FAILED " << infoLog << std::endl;
	}
}

SpriteRenderer::SpriteRenderer(Transform *trans, const char *sprite)
{
	//Generate Texture
	glGenTextures(1, &sprite_texture_id_);
	//Bind Texture
	glBindTexture(GL_TEXTURE_2D, sprite_texture_id_);
	//Texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//Load texture
	data = stbi_load(sprite, &sprite_width_, &sprite_height_, &sprite_nr_channels_, STBI_rgb_alpha);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sprite_width_, sprite_height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		std::cout << "ERROR: FAILED TO LOAD TEXTURE" << std::endl;
	}
	stbi_image_free(data);
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Set Texture to shader
	glUseProgram(shader_program_id_);
	//Receive Transform from entity
	transform_ = trans;
	//Rectangle
	float vertices[] = {
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		1, 2, 3
	};

	//Vertex Shader Source
	const char *vertex_shader_ = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec2 aTexCoord;\n"
		"uniform mat4 model;\n"
		"uniform mat4 projection;\n"
		"out vec2 TexCoord;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = projection * model * vec4(aPos, 1.0);\n"
		"	TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
		"}\0";
	//Fragment Shader Source
	const char *fragment_shader_ = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec2 TexCoord;\n"
		"uniform sampler2D text;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(texture(text, TexCoord).rgb, texture(text, TexCoord).a);\n"
		"}\n\0";
	//Create and compile vertex shader
	GLuint vertex_shader_id_ = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader_id_, 1, &vertex_shader_, NULL);
	glCompileShader(vertex_shader_id_);
	CheckShaderCompileProcess(vertex_shader_id_);
	//Create and compile fragment shader
	GLuint fragment_shader_id_ = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader_id_, 1, &fragment_shader_, NULL);
	glCompileShader(fragment_shader_id_);
	CheckShaderCompileProcess(fragment_shader_id_);
	//Create shader program
	shader_program_id_ = glCreateProgram();
	glAttachShader(shader_program_id_, vertex_shader_id_);
	glAttachShader(shader_program_id_, fragment_shader_id_);
	glLinkProgram(shader_program_id_);
	//Check program compile
	GLint success;
	char infoLog[512];
	glGetProgramiv(shader_program_id_, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program_id_, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	//Delete used shaders
	glDeleteShader(vertex_shader_id_);
	glDeleteShader(fragment_shader_id_);
	//Create VBO, VAO, EBO
	glGenVertexArrays(1, &VAO_);
	glGenBuffers(1, &VBO_);
	glGenBuffers(1, &EBO_);
	//Bind VAO
	glBindVertexArray(VAO_);
	//Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//Bind EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Unbinding things
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SpriteRenderer::Draw()
{
	//Model matrix
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, transform_->GetPosition());

	//model = glm::translate(model, glm::vec3(-0.5f * 10.0f, -0.5f * 10.0f, 0.0f));
	model = glm::rotate(model, glm::radians(transform_->GetRotation()), glm::vec3(0.0f, 0.0f, 1.0f));
	//model = glm::translate(model, glm::vec3(0.5f * 10.0f, 0.5f * 10.0f, 0.0f));

	model = glm::scale(model, glm::vec3(sprite_width_, sprite_height_, 1.0f));
	//Projection matrix
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);
	projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, sprite_texture_id_);
	glUseProgram(shader_program_id_);
	unsigned int modelMatLocation = glGetUniformLocation(shader_program_id_, "model");
	unsigned int projectionMatLocation = glGetUniformLocation(shader_program_id_, "projection");
	unsigned int textureLocation = glGetUniformLocation(shader_program_id_, "text");
	glUniform1i(textureLocation, 0);
	glUniformMatrix4fv(modelMatLocation, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(projectionMatLocation, 1, GL_FALSE, glm::value_ptr(projection));
	glBindVertexArray(VAO_);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}