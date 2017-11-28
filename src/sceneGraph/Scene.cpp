//
// Created by Jip Boesenkool on 09/11/2017.
//

#include <iostream>
#include "Scene.h"
#include "../Window.h"

Scene::Scene()
{
	//Setup shaders

	//Setup scene

//Track
	track = new TransformNode();
	track->m_bVolume = new BoundingSphere( &track->m_transform );
	Model *redSphereModel = new Model("../resources/models/sphere.obj", Window::shaderPhongProgram, &track->m_transform);
	redSphereModel->m_material = Material{
			glm::vec3(0.5f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(0.9f, 0.6f, 0.6f),
			32.0f
	};
	Model *blueSphereModel = new Model("../resources/models/sphere.obj", Window::shaderPhongProgram, &track->m_transform);
	blueSphereModel->m_material = Material{
			glm::vec3(0.0f, 0.0f, 0.5f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.6f, 0.6f, 0.9f),
			32.0f
	};
	Model *metalicSphereModel = new Model("../resources/models/sphere.obj", Window::shaderEnvProgram, &track->m_transform);
	metalicSphereModel->m_material = Material{
			glm::vec3(0.0f, 0.0f, 0.5f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.6f, 0.6f, 0.9f),
			32.0f
	};

	blueSphere = new GeometryNode( blueSphereModel );
	redSphere = new GeometryNode( redSphereModel );
//Set 0
	ControlPoint *c00 = new ControlPoint( redSphere );
	c00->m_transform.m_position = glm::vec3(-2.0f, 1.0f, 0.0f);
	c00->m_transform.Scale(0.1f);
	c00->m_bVolume = new BoundingSphere( &c00->m_transform );
	c00->AddChild( redSphere );
	m_controlPoints.push_back(c00);
	ControlPoint *c01 = new ControlPoint( redSphere );
	c01->m_transform.m_position = glm::vec3(-1.0f, 2.0f, 0.0f);
	c01->m_transform.Scale(0.1f);
	c01->m_bVolume = new BoundingSphere( &c01->m_transform );
	c01->AddChild( redSphere );
	m_controlPoints.push_back(c01);
	ControlPoint *p0 = new ControlPoint( blueSphere );
	p0->m_transform.m_position = glm::vec3(-1.5f, 1.5f, 0.0f);
	p0->m_transform.Scale(0.1f);
	p0->m_bVolume = new BoundingSphere( &p0->m_transform );
	p0->AddChild( blueSphere );
	m_controlPoints.push_back(p0);

	c00->m_cpPaired = c01;
	c01->m_cpPaired = c00;

//Set 1
	ControlPoint *c10 = new ControlPoint( redSphere );
	c10->m_transform.m_position = glm::vec3(1.0f, 2.0f, 0.0f);
	c10->m_transform.Scale(0.1f);
	c10->m_bVolume = new BoundingSphere( &c10->m_transform );
	c10->AddChild( redSphere );
	m_controlPoints.push_back(c10);
	ControlPoint *c11 = new ControlPoint( redSphere );
	c11->m_transform.m_position = glm::vec3(2.0f, 1.0f, 0.0f);
	c11->m_transform.Scale(0.1f);
	c11->m_bVolume = new BoundingSphere( &c11->m_transform );
	c11->AddChild( redSphere );
	m_controlPoints.push_back(c11);
	ControlPoint *p1 = new ControlPoint( blueSphere );
	p1->m_transform.m_position = glm::vec3(1.5f, 1.5f, 0.0f);
	p1->m_transform.Scale(0.1f);
	p1->m_bVolume = new BoundingSphere( &p1->m_transform );
	p1->AddChild( blueSphere );
	m_controlPoints.push_back(p1);

	c10->m_cpPaired = c11;
	c11->m_cpPaired = c10;
//Set 2
	ControlPoint *c20 = new ControlPoint( redSphere );
	c20->m_transform.m_position = glm::vec3(2.0f, -1.0f, 0.0f);
	c20->m_transform.Scale(0.1f);
	c20->m_bVolume = new BoundingSphere( &c20->m_transform );
	c20->AddChild( redSphere );
	m_controlPoints.push_back(c20);
	ControlPoint *c21 = new ControlPoint( redSphere );
	c21->m_transform.m_position = glm::vec3(1.0f, -2.0f, 0.0f);
	c21->m_transform.Scale(0.1f);
	c21->m_bVolume = new BoundingSphere( &c21->m_transform );
	c21->AddChild( redSphere );
	m_controlPoints.push_back(c21);
	ControlPoint *p2 = new ControlPoint( blueSphere );
	p2->m_transform.m_position = glm::vec3(1.5f, -1.5f, 0.0f);
	p2->m_transform.Scale(0.1f);
	p2->m_bVolume = new BoundingSphere( &p2->m_transform );
	p2->AddChild( blueSphere );
	m_controlPoints.push_back(p2);

	c20->m_cpPaired = c21;
	c21->m_cpPaired = c20;
//Set 3
	ControlPoint *c30 = new ControlPoint( redSphere );
	c30->m_transform.m_position = glm::vec3(-1.0f, -2.0f, 0.0f);
	c30->m_transform.Scale(0.1f);
	c30->m_bVolume = new BoundingSphere( &c30->m_transform );
	c30->AddChild( redSphere );
	m_controlPoints.push_back(c30);
	ControlPoint *c31 = new ControlPoint( redSphere );
	c31->m_transform.m_position = glm::vec3(-2.0f, -1.0f, 0.0f);
	c31->m_transform.Scale(0.1f);
	c31->m_bVolume = new BoundingSphere( &c31->m_transform );
	c31->AddChild( redSphere );
	m_controlPoints.push_back(c31);
	ControlPoint *p3 = new ControlPoint( blueSphere );
	p3->m_transform.m_position = glm::vec3(-1.5f, -1.5f, 0.0f);
	p3->m_transform.Scale(0.1f);
	p3->m_bVolume = new BoundingSphere( &p3->m_transform );
	p3->AddChild( blueSphere );
	m_controlPoints.push_back(p3);

	c30->m_cpPaired = c31;
	c31->m_cpPaired = c30;

//Set 3
	handle3 = new BezierHandleNode(&c30->m_transform, &p3->m_transform, &c31->m_transform);
	p3->m_parent = handle3;
	c30->m_parent = handle3;
	c31->m_parent = handle3;

	handle3->AddChild(c30);
	handle3->AddChild(p3);
	handle3->AddChild(c31);
	track->AddChild(handle3);
//Set 2
	handle2 = new BezierHandleNode(&c20->m_transform, &p2->m_transform, &c21->m_transform, handle3);
	p2->m_parent = handle2;
	c20->m_parent = handle2;
	c21->m_parent = handle2;

	handle3->m_prev = handle2;
	handle2->AddChild(c20);
	handle2->AddChild(p2);
	handle2->AddChild(c21);
	track->AddChild(handle2);
//Set 1
	handle1 = new BezierHandleNode(&c10->m_transform, &p1->m_transform, &c11->m_transform, handle2);
	p1->m_parent = handle1;
	c10->m_parent = handle1;
	c11->m_parent = handle1;

	handle2->m_prev = handle1;
	handle1->AddChild(c10);
	handle1->AddChild(p1);
	handle1->AddChild(c11);
	track->AddChild(handle1);
//Set 0
	handle0 = new BezierHandleNode(&c00->m_transform, &p0->m_transform, &c01->m_transform, handle1);
	p0->m_parent = handle0;
	c00->m_parent = handle0;
	c01->m_parent = handle0;

	handle1->m_prev = handle0;
	handle0->AddChild(c00);
	handle0->AddChild(p0);
	handle0->AddChild(c01);

	handle0->m_prev = handle3;
	handle3->SetNext( handle0 );

	track->AddChild(handle0);

//End track
//Plot player
	cart = new TransformNode(  );
	cart->m_transform.m_position = handle0->BezierCurvePoint(0.5f);
	cart->m_transform.Scale(0.25f);
	cart->m_bVolume = new BoundingSphere( &cart->m_transform );
	cart->AddChild( new GeometryNode( metalicSphereModel ) );
	track->AddChild( cart );
//End player

	world.AddChild( track );

//Lighting
	light2world = new TransformNode(  );
	pointLightObj = new PointLightModel(Window::shaderPhongProgram, Window::shaderVisualLightProgram, &light2world->m_transform);
	light2world->AddChild( new GeometryNode( pointLightObj ) );
//End Lighting

	InitPickingRenderBuffer();
	sceneLoaded = true;
}

Scene::~Scene()
{
	delete( &world );
}

void Scene::Draw()
{
	if(!sceneLoaded)
	{
		return;
	}
	RenderPickingToBuffer();

	world.Draw( glm::mat4(1.0f) );
}

void Scene::Update()
{
	if(!sceneLoaded)
	{
		return;
	}
	cart->m_transform.SetPosition( handle0->BezierCurvePoint(0.5f) );
	world.Update();
}

void Scene::InitPickingRenderBuffer()
{
	// create a framebuffer object
	glGenFramebuffers(1, &m_fbo);
	//attach the texture and the render buffer to the frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

	// generate a texture id
	glGenTextures(1, &m_fboTexture);
	glBindTexture(GL_TEXTURE_2D, m_fboTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Window::width, Window::height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	// set texture parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	//create a renderbuffer object for the depth buffer
	glGenRenderbuffers(1, &m_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, Window::width, Window::height);

	// unbind the render buffer
	glBindRenderbuffer(GL_RENDERBUFFER, 0);


	//attach the texture and the render buffer to the frame buffer */
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_fboTexture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

	// check the frame buffer
	if ( glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "Framebuffer status not complete" << '\n';
	}

	// return to the default frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Scene::RenderPickingToBuffer()
{
	// bind the frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

	// clear the frame buffer
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// select the shader program
	glUseProgram(Window::shaderPickProgram);
	GLint uColor 	= glGetUniformLocation(Window::shaderPickProgram, "color");
	GLint uModel 	= glGetUniformLocation(Window::shaderPickProgram, "model");

//Draw control points to picking shader
	for( int i = 0; i < m_controlPoints.size(); i++ )
	{
		ControlPoint *cp = m_controlPoints[i];
		//Upload the packed RGBA values to the shader
		int r = (i & 0x000000FF) >>  0;
		int g = (i & 0x0000FF00) >>  8;
		int b = (i & 0x00FF0000) >> 16;
		glUniform4f(uColor, r/255.0f, g/255.0f ,b/255.0f, 1.0f);
		glUniformMatrix4fv(uModel, 1, GL_FALSE, &cp->m_storedMatrix[0][0]);

		// Draw
		glBindVertexArray(cp->m_geoNode->m_model->m_VAO);
		glDrawElements(GL_TRIANGLES, cp->m_geoNode->m_model->m_mesh.m_indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	//check that our framebuffer is ok
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "Framebuffer Error" << '\n';
	}

	// return to the default frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Scene::MouseSelect(double xpos, double ypos)
{
	int x, y;
	GLuint r,g,b,a, pixel_index;

	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	// generate the pixel buffer object
	glGenBuffers(1,&m_pbo);
	glBindBuffer(GL_PIXEL_PACK_BUFFER, m_pbo);
	glBufferData(GL_PIXEL_PACK_BUFFER, Window::width * Window::height * 4, nullptr, GL_STREAM_READ);
	// to avoid weird behaviour the first frame the data is loaded
	glReadPixels(0, 0, Window::width, Window::height, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	/* read one pixel buffer */
	glBindBuffer(GL_PIXEL_PACK_BUFFER, m_pbo);
	/* map the other pixel buffer */
	glReadPixels(0, 0, Window::width, Window::height, GL_BGRA, GL_UNSIGNED_BYTE, 0);
	GLubyte *ptr = (GLubyte*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_WRITE);
	/* get the mouse coordinates */
	y = (int)(Window::height - 2.0*ypos);
	x = (int)(2.0*xpos);
	if (x >= 0 && x < Window::width && y >= 0 && y < Window::height){
		pixel_index = (x + y * Window::width) * 4;
		b = ptr[pixel_index];
		g = ptr[pixel_index + 1];
		r = ptr[pixel_index + 2];
		a = ptr[pixel_index + 3];
		if(a != 0)
		{
			Window::selectedObject = r;
			std::cout << "selected object: " << Window::selectedObject << std::endl;
		}
	}
	glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
	glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}