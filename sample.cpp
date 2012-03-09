// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>
#include <math.h>

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

void drawRoundCylinder(double h, double r1, double r2)
{
	glPushMatrix();
	glTranslated(0, 0, r1);
	drawSphere(r1);
	if (h - r1 - r2 > 0) drawCylinder(h - r1 - r2, r1, r2);
	glTranslated(0, 0, h - r1 - r2);
	drawSphere(r2);
	glPopMatrix();
}

/*
void drawTail()
{
	float gap = 0.025;
	float y = -1 / VAL(TAIL_X) * VAL(TAIL_X) * VAL(TAIL_X);
	float x = 1 / VAL(TAIL_Y) * VAL(TAIL_Y) * VAL(TAIL_Y);
	float u = 360 * gap / (2 * 3.1415 * sqrt(x * x + y * y));
	glRotated(180, 1, 0, 0);
	for (int i = 0; i < VAL(TAIL_LENGTH) / gap; i++)
	{
		drawCylinder(gap, 0.1, 0.1);
		glRotated(u, x, y, 0);
		glTranslated(0, 0 , gap);
	}
}
*/

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
		// dodecahedron
		glPushMatrix();
		glTranslated(.0f, 2.0f, .0f);
		drawTorus(VAL(TORUS_R), VAL(TORUS_r));
		glPopMatrix();

		//head
		glPushMatrix();
		glTranslated(0, VAL(LEG_LENGTH) + 0.05 + VAL(HEIGHT) + 0.05 + VAL(HEAD_SIZE), 0);
		glRotated(VAL(HEAD_ROTATE), 0.0, 1.0, 0.0);
		drawSphere(VAL(HEAD_SIZE));
		glPopMatrix();

		//body
		glPushMatrix();
		glTranslated(0, 0.05 + VAL(LEG_LENGTH), 0);
		glRotated(-90, 1.0, 0.0, 0.0);
		drawRoundCylinder(VAL(HEIGHT), 0.7, 0.6);
		glPopMatrix();
		
		//right arm
		glPushMatrix();
		glTranslated(-0.7 - 0.3, VAL(LEG_LENGTH) + 0.05 + VAL(HEIGHT) * 0.8f, 0);
		glRotated(VAL(RIGHT_ARM_ROTATE_X), 1.0, 0.0, 0.0);
		glRotated(VAL(RIGHT_ARM_ROTATE_Y), 0.0, 1.0, 0.0);
		drawRoundCylinder(VAL(ARM_LENGTH), 0.3, 0.26);
		glPopMatrix();

		
		//left arm
		glPushMatrix();
		glTranslated(0.7 + 0.3, VAL(LEG_LENGTH) + 0.05 + VAL(HEIGHT) * 0.8f, 0);
		glRotated(VAL(LEFT_ARM_ROTATE_X), 1.0, 0.0, 0.0);
		glRotated(VAL(LEFT_ARM_ROTATE_Y), 0.0, 1.0, 0.0);
		drawRoundCylinder(VAL(ARM_LENGTH), 0.3, 0.26);
		glPopMatrix();

		//right leg
		glPushMatrix();
		glTranslated(-0.5, VAL(LEG_LENGTH), 0);
		glRotated(VAL(RIGHT_LEG_ROTATE_X), 1.0, 0.0, 0.0);
		glRotated(VAL(RIGHT_LEG_ROTATE_Y), 0.0, 1.0, 0.0);
		drawRoundCylinder(VAL(LEG_LENGTH) - 0.15, 0.37, 0.4);
		glPopMatrix();

		//left leg
		glPushMatrix();
		glTranslated(0.5, VAL(LEG_LENGTH), 0);
		glRotated(VAL(LEFT_LEG_ROTATE_X), 1.0, 0.0, 0.0);
		glRotated(VAL(LEFT_LEG_ROTATE_Y), 0.0, 1.0, 0.0);
		drawRoundCylinder(VAL(LEG_LENGTH) - 0.15, 0.37, 0.4);
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
	controls[HEAD_SIZE] = ModelerControl("Head Size", 0, 2, 0.1f, 1);
	controls[HEAD_ROTATE] = ModelerControl("Head Rotate", -135, 135, 1, 0);
    controls[HEIGHT] = ModelerControl("Height", 1, 5, 0.1f, 2);
    controls[ARM_LENGTH] = ModelerControl("Arm Length", 1, 5, 0.1f, 2);
    controls[LEFT_ARM_ROTATE_X] = ModelerControl("Left Arm Rotate X", -90, 100, 1.0f, 80);
    controls[LEFT_ARM_ROTATE_Y] = ModelerControl("Left Arm Rotate Y", -30, 90, 1.0f, 0);
    controls[RIGHT_ARM_ROTATE_X] = ModelerControl("Right Arm Rotate X", -90, 100, 1.0f, -40);
    controls[RIGHT_ARM_ROTATE_Y] = ModelerControl("Right Arm Rotate Y", -90, 30, 1.0f, 0);
    controls[LEG_LENGTH] = ModelerControl("Leg Length", 1, 5, 0.1f, 2);
    controls[LEFT_LEG_ROTATE_X] = ModelerControl("Left Leg Rotate X", 0, 90, 1.0f, 80);
    controls[LEFT_LEG_ROTATE_Y] = ModelerControl("Left Leg Rotate Y", -80, 90, 1.0f, 0);
    controls[RIGHT_LEG_ROTATE_X] = ModelerControl("Right Leg Rotate X", 0, 90, 1.0f, 90);
    controls[RIGHT_LEG_ROTATE_Y] = ModelerControl("Right Leg Rotate Y", -90, 80, 1.0f, 0);
    //controls[TAIL_X] = ModelerControl("Tail Rotate X", -1, 1, 0.03f, 0.001);
    //controls[TAIL_Y] = ModelerControl("Tail Rotate Y", -1, 1, 0.03f, 1);
    //controls[TAIL_LENGTH] = ModelerControl("Tail Length", 0.5, 5, 0.1f, 2);
    controls[FEET_SIZE] = ModelerControl("Feet Size", 0.5, 3, 0.1f, 1);
    controls[TORUS_R] = ModelerControl("Torus R", 0, 10, 0.1f, 3);
    controls[TORUS_r] = ModelerControl("Torus r", 0, 10, 0.1f, 1);
	

    ModelerApplication::Instance()->Init(&createSampleModel, controls, NUMCONTROLS);
    return ModelerApplication::Instance()->Run();
}
