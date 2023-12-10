#include <cmath>
#include <numbers>

#include <GL/glut.h>

class Vector {
public:
  Vector() : x_{0}, y_{0} {}
  Vector(float x, float y) : x_{x}, y_{y} {}

  void SetX(float x) { x_ = x; }
  void SetY(float y) { y_ = y; }

  float x() const { return x_; }
  float y() const { return y_; }

private:
  float x_;
  float y_;
};

Vector Rotate(float angle, Vector pivot, Vector point) {
  auto rad = angle * (std::numbers::pi_v<float> / 180.0);

  float dx = pivot.x() + (point.x() - pivot.x()) * std::cos(rad) - (point.y() - pivot.y()) * std::sin(rad);
  float dy = pivot.y() + (point.x() - pivot.x()) * std::sin(rad) + (point.y() - pivot.y()) * std::cos(rad);

  return {dx, dy};
}

void DrawLog(Vector point, float w, float h, float angle) {
  auto pivot_x = point.x() + w;
  auto pivot_y = point.y() + h;

  auto p1 = Rotate(angle, {pivot_x, pivot_y}, point);
  auto p2 = Rotate(angle, {pivot_x, pivot_y}, {point.x() + w, point.y()});
  auto p3 = Rotate(angle, {pivot_x, pivot_y}, {point.x() + w, point.y() + h});
  auto p4 = Rotate(angle, {pivot_x, pivot_y}, {point.x(), point.y() + h});

  glBegin(GL_QUADS);
    glVertex2f(p1.x(), p1.y());
    glVertex2f(p2.x(), p2.y());
    glVertex2f(p3.x(), p3.y());
    glVertex2f(p4.x(), p4.y());
  glEnd();
}

void DrawCircle(Vector point, float r, int num_segments) {
  float cx = point.x();
  float cy = point.y();

  glBegin(GL_TRIANGLE_FAN);
  for (int ii = 0; ii < num_segments; ii++)   {
      float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
      float x = r * cosf(theta);//calculate the x component 
      float y = r * sinf(theta);//calculate the y component 
      glVertex2f(x + cx, y + cy);//output vertex 
  }
  glEnd();
}

void DrawTriangle(Vector point, float b, float h) {
  auto center = b / 2;

  glBegin(GL_TRIANGLE_FAN);
    glVertex2f(point.x(), point.y());
    glVertex2f(point.x() + b, point.y());
    glVertex2f(point.x() + center, point.y() - h);
  glEnd();
}

Vector fire_position_1{34, 27};
Vector fire_position_2{35, 29};
Vector fire_position_3{35, 25};

void DrawFirebon() {
  glColor3f(0.431, 0.278, 0.165);
  DrawLog({29, 30}, 1, 7, 20);
  DrawLog({30, 31}, 1, 7, 15);
  DrawLog({32, 30}, 1, 7, 0);
  DrawLog({34, 30}, 1, 7, -15);

  glColor3f(0.941, 0.345, 0.098);
  DrawCircle({32, 28}, 1, 20);
  glBegin(GL_TRIANGLE_FAN);
    glVertex2f(30, 27);
    glVertex2f(31, 29);
    glVertex2f(32, 25);
  glEnd();

  glBegin(GL_TRIANGLE_FAN);
    glVertex2f(32, 27);
    glVertex2f(33, 29);
    glVertex2f(33, 25);
  glEnd();

  glBegin(GL_TRIANGLE_FAN);
    glVertex2f(fire_position_1.x(), fire_position_1.y());
    glVertex2f(fire_position_2.x(), fire_position_2.y());
    glVertex2f(fire_position_3.x(), fire_position_3.y());
  glEnd();

  fire_position_1.SetY(fire_position_1.y() - 0.1);
  fire_position_2.SetY(fire_position_2.y() - 0.1);
  fire_position_3.SetY(fire_position_3.y() - 0.1);

  if (fire_position_1.y() <= 20) {
    fire_position_1.SetY(27);
  }
  if (fire_position_2.y() <= 22) {
    fire_position_2.SetY(29);
  }
  if (fire_position_3.y() <= 18) {
    fire_position_3.SetY(25);
  }

  glColor3f(0.651, 0.647, 0.565);
  glBegin(GL_QUADS);
    glVertex2f(32, 38);
    glVertex2f(34, 38);
    glVertex2f(33.5, 39);
    glVertex2f(32, 39);
  glEnd();

  glBegin(GL_QUADS);
    glVertex2f(30, 37);
    glVertex2f(32, 37);
    glVertex2f(31.5, 38);
    glVertex2f(30, 38);
  glEnd();
}

void DrawTent() {
  glColor3f(0.941, 0.855, 0.141);
  DrawTriangle({15, 25}, 10, 15);

  glBegin(GL_QUADS);
    glVertex2f(15, 25);
    glVertex2f(25, 25);
    glVertex2f(24, 34);
    glVertex2f(16, 34);
  glEnd();

  glColor3f(0.569, 0.565, 0.184);
  DrawTriangle({18, 34}, 4, 11);

  glColor3f(0.659, 0.651, 0.059);
  glBegin(GL_QUADS);
    glVertex2f(5, 13);
    glVertex2f(20, 10);
    glVertex2f(15, 25);
    glVertex2f(1, 27);
  glEnd();

  glColor3f(0.659, 0.651, 0.059);
  glBegin(GL_QUADS);
    glVertex2f(16, 34);
    glVertex2f(2, 35);
    glVertex2f(1, 27);
    glVertex2f(15, 25);
  glEnd();

  glColor3f(0.388, 0.384, 0.031);
  glBegin(GL_QUADS);
    glVertex2f(15, 25);
    glVertex2f(1, 27);
    glVertex2f(1, 27.5);
    glVertex2f(15, 26);
  glEnd();
}

Vector moon_position{0, 6};

void DrawMoon() {
  glColor3f(0.749, 0.749, 0.643);
  DrawCircle(moon_position, 5, 25);

  moon_position.SetX(moon_position.x() + 0.1);
  
  if (moon_position.x() >= 55) {
    moon_position.SetX(0);
  }
}

void DrawSpruces() {
  glColor3f(0.353, 0.741, 0.024);

  glBegin(GL_QUADS);
    glVertex2f(40, 40);
    glVertex2f(41, 40);
    glVertex2f(41, 45);
    glVertex2f(40, 45);
  glEnd();

  DrawTriangle({38, 40}, 5, 6);
  DrawTriangle({38, 37}, 5, 6);
  DrawTriangle({38, 34}, 5, 6);
  DrawTriangle({38, 31}, 5, 6);
  DrawTriangle({38, 28}, 5, 6);

  glBegin(GL_QUADS);
    glVertex2f(46, 40);
    glVertex2f(47, 40);
    glVertex2f(47, 45);
    glVertex2f(46, 45);
  glEnd();

  DrawTriangle({44, 40}, 5, 6);
  DrawTriangle({44, 37}, 5, 6);
  DrawTriangle({44, 34}, 5, 6);
  DrawTriangle({44, 31}, 5, 6);
  DrawTriangle({44, 28}, 5, 6);
}

void InitGL() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 50, 50, 0);
  glMatrixMode(GL_MODELVIEW);
}

void Display() {
  glClearColor(0.212, 0.525, 0.588, 1);

  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  DrawMoon();
  DrawFirebon();
  DrawTent();
  DrawSpruces();
  
  glutSwapBuffers();
}

void Timer(int) {
  glutPostRedisplay();
  glutTimerFunc(1000/60, Timer, 0);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(800, 600);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutCreateWindow("Tugas Akhir");

  glutDisplayFunc(Display);
  glutTimerFunc(0, Timer, 0);
  InitGL();

  glutMainLoop();

  return 0;
}
