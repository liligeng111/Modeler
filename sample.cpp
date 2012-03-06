// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>

#include "modelerglobals.h"

// To make a SampleModel, we inherit off of ModelerView
class SampleModel : public ModelerView 
{
public:
    SampleModel(int x, int y, int w, int h, char *label) 
        : ModelerView(x,y,w,h,label) { }

    virtual void draw();
};

// We need to make a creator function, mostly because of
// nasty API stuff that we'd rather stay away from.
ModelerView* createSampleModel(int x, int y, int w, int h, char *label)
{ 
    return new SampleModel(x,y,w,h,label); 
}

// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out SampleModel
void SampleModel::draw()
{
    // This call takes care of a lot of the nasty projection 
    // matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
    ModelerView::draw();

	// draw the floor
	setAmbientColor(.1f,.1f,.1f);
	setDiffuseColor(COLOR_BLUE);
	glPushMatrix();
	glTranslated(-5,0,-5);
	drawBox(10,0.01f,10);
	glPopMatrix();

	glPushMatrix();
	// draw the sample model
	GLfloat maambient[]={0.79225f,0.79225f,0.79225f,1.0f};
	GLfloat madiffuse[]={0.50754f,0.50754f,0.50754f,1.0f};
	GLfloat maspecular[]={0.508273f,0.508273f,0.508273f,0.508273f};
	GLfloat maemi[4]={0.0f,0.0f,0.0f,1.0f};

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,maambient);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,madiffuse);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,maspecular);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,51.2f);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,maemi);

	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));

		//head
		glPushMatrix();
		glTranslated(0, 1 + 0.05 + VAL(HEAD_SIZE) + VAL(HEIGHT), 0);
		glRotated(VAL(HEAD_ROTATE), 0.0, 1.0, 0.0);
		drawSphere(VAL(HEAD_SIZE));
		glPopMatrix();

		//body
		glPushMatrix();
		glTranslated(0, 1, 0);
		glRotated(-90, 1.0, 0.0, 0.0);
		drawCylinder(VAL(HEIGHT), 0.7, 0.7);
		glPopMatrix();
		
		//right arm
		glPushMatrix();
		glTranslated(0.7, 1, 0);
		//glRotated(-90, 1.0, 0.0, 0.0);
		drawCylinder(1, 0.2, 0.2);
		glPopMatrix();

		//right leg
		glPushMatrix();
		glTranslated(0.2, 0, 0);
		glScaled(0.5, 1, 0.5);
		glRotated(-90, 1.0, 0.0, 0.0);
		drawCylinder(1, 0.3, 0.3);
		glPopMatrix();

		//left leg
		glPushMatrix();
		glTranslated(-0.2, 0, 0);
		glScaled(0.5, 1, 0.5);
		glRotated(-90, 1.0, 0.0, 0.0);
		drawCylinder(1, 0.3, 0.3);
		glPopMatrix();

	glPopMatrix();
}

int main()
{
	// Initialize the controls
	// Constructor is 
	// ModelerControl(name, minimumvalue, maximumvalue, stepsize, defaultvalue)
    ModelerControl controls[NUMCONTROLS];
	// gosh, this should be the right way..
    controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
    controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.1f, 0);
    controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);
	controls[HEAD_SIZE] = ModelerControl("Head Size", 0, 2, 0.1, 1);
	controls[HEAD_ROTATE] = ModelerControl("Head Rotate", -135, 135, 1, 0);
    controls[HEIGHT] = ModelerControl("Height", 1, 5, 0.1f, 2);

    ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
    return ModelerApplication::Instance()->Run();
}
