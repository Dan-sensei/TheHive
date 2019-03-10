#include "Letra2D.hpp"
#include "ZMeshData.hpp"
#include "AssetManager.hpp"
#include <iostream>
#include <SOIL2/SOIL2.h>

#define HEIGTH 64.0f
#define THEIGTH 800.0f
#define TWIDTH 1400.0f
#define MAYUSCULAS 198.0f
#define MINUSCULAS 64.0f

/*

altura 64
1400X800
minusculas
inicio_y minusculas 64

letra   X       W
a       1       32
b       47      33
c       94      30
d       138     34
e       185     30
f       225     28
g       261     34
h       309     32
i       356     19
j       392     26
k       430     37
l       477     17
m       509     47
n       571     32
o       619     31
p       662     34
q       712     32
r       757     25
s       793     29
t       836     21
u       871     33
v       918     36
w       966     51
x       1024    40
y       1075    33
z       1120    33



MAYUSCULAS
inicio_y MAYUSCULAS 198


letra   X       W

A       0       42
B       56      41
C       111     40
D       162     42
E       217     41
F       270     41
G       322     40
H       375     46
I       433     20
J       465     41
K       518     48
L       573     34
M       622     52
N       686     46
O       745     43
P       801     42
Q       856     43
R       913     42
S       967     40
T       1022    40
U       1073    43
V       1132    46
W       1188    62
X       1255    52
Y       1319    46

inicio_y Z 266

Z      0        43




*/

float Letra2D::getX(){
    return X;
}
float Letra2D::getW(){
    auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    float ancho = mode->width;
    return (W/ancho);
}
float Letra2D::getY(){
    return Y;
}
float Letra2D::getH(){
    auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    float alto = mode->height;
    return (H/alto);
}
float Letra2D::getTX(){
    return TX;
}
float Letra2D::getTW(){
    return TW;
}
float Letra2D::getTY(){
    return TY;
}
float Letra2D::getTH(){
    return TH;
}

Letra2D::Letra2D()
{

}

Letra2D::~Letra2D(){

}
void Letra2D::init2(){

    auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    float ancho = mode->width;
    float alto = mode->height;
    H=HEIGTH;//constante

    TX=(X)/TWIDTH;
    TW=(X+W)/TWIDTH;

    TY=(Y)/THEIGTH;
    TH=(Y+H)/THEIGTH;

    ratio=W/H;
    W=((W)/ancho);//SCREEN W porcentual
    H=((H)/alto);//SCREEN H
}
void Letra2D::resize(float alto){
    //redimensionar una letra
    //alto en porcentage
    //float tamy=alto*SCREENH;

    //alto en pixeles
    float tamy=alto;
    float tamx=tamy*ratio;
    W=tamx;//SCREEN W porcentual
    H=tamy;//SCREEN H

    //W=tamx;//SCREEN W
    //H=tamy;//SCREEN H

}
void Letra2D::inita(){
    X=1;
    W=32;

    Y=MINUSCULAS;
}
void Letra2D::initb(){
    X=47;
    W=33;

    Y=MINUSCULAS;
}
void Letra2D::initc(){
    X=94;
    W=30;

    Y=MINUSCULAS;
}
void Letra2D::initd(){
    X=138;
    W=34;

    Y=MINUSCULAS;
}
void Letra2D::inite(){
    X=185;
    W=30;

    Y=MINUSCULAS;
}
void Letra2D::initf(){
    X=225;
    W=28;

    Y=MINUSCULAS;
}
void Letra2D::initg(){
    X=261;
    W=34;

    Y=MINUSCULAS;
}
void Letra2D::inith(){
    X=309;
    W=32;

    Y=MINUSCULAS;
}
void Letra2D::initi(){
    X=356;
    W=19;

    Y=MINUSCULAS;
}
void Letra2D::initj(){
    X=392;
    W=26;

    Y=MINUSCULAS;
}
void Letra2D::initk(){
    X=430;
    W=37;

    Y=MINUSCULAS;
}
void Letra2D::initl(){
    X=477;
    W=17;

    Y=MINUSCULAS;
}
void Letra2D::initm(){
    X=509;
    W=47;

    Y=MINUSCULAS;
}
void Letra2D::initn(){
    X=571;
    W=32;

    Y=MINUSCULAS;
}
void Letra2D::inito(){
    X=619;
    W=31;

    Y=MINUSCULAS;
}
void Letra2D::initp(){
    X=662;
    W=34;

    Y=MINUSCULAS;
}
void Letra2D::initq(){
    X=712;
    W=32;

    Y=MINUSCULAS;
}
void Letra2D::initr(){
    X=757;
    W=25;

    Y=MINUSCULAS;
}
void Letra2D::inits(){
    X=793;
    W=29;

    Y=MINUSCULAS;
}
void Letra2D::initt(){
    X=836;
    W=21;

    Y=MINUSCULAS;
}
void Letra2D::initu(){
    X=871;
    W=33;

    Y=MINUSCULAS;
}
void Letra2D::initv(){
    X=918;
    W=36;

    Y=MINUSCULAS;
}
void Letra2D::initw(){
    X=966;
    W=51;

    Y=MINUSCULAS;
}
void Letra2D::initx(){
    X=1024;
    W=40;

    Y=MINUSCULAS;
}
void Letra2D::inity(){
    X=1075;
    W=33;

    Y=MINUSCULAS;
}
void Letra2D::initz(){
    X=1120;
    W=33;

    Y=MINUSCULAS;
}

void Letra2D::initA(){
    X=0;
    W=42;

    Y=MAYUSCULAS;
}
void Letra2D::initB(){
    X=56;
    W=41;

    Y=MAYUSCULAS;
}
void Letra2D::initC(){
    X=111;
    W=40;

    Y=MAYUSCULAS;
}
void Letra2D::initD(){
    X=162;
    W=42;

    Y=MAYUSCULAS;
}
void Letra2D::initE(){
    X=217;
    W=41;

    Y=MAYUSCULAS;
}
void Letra2D::initF(){
    X=270;
    W=41;

    Y=MAYUSCULAS;
}
void Letra2D::initG(){
    X=322;
    W=40;

    Y=MAYUSCULAS;
}
void Letra2D::initH(){
    X=375;
    W=46;

    Y=MAYUSCULAS;
}
void Letra2D::initI(){
    X=433;
    W=20;

    Y=MAYUSCULAS;
}
void Letra2D::initJ(){
    X=465;
    W=41;

    Y=MAYUSCULAS;
}
void Letra2D::initK(){
    X=518;
    W=48;

    Y=MAYUSCULAS;
}
void Letra2D::initL(){
    X=573;
    W=34;

    Y=MAYUSCULAS;

}
void Letra2D::initM(){
    X=622;
    W=52;

    Y=MAYUSCULAS;
}
void Letra2D::initN(){
    X=686;
    W=46;

    Y=MAYUSCULAS;
}
void Letra2D::initO(){
    X=745;
    W=43;

    Y=MAYUSCULAS;
}
void Letra2D::initP(){
    X=801;
    W=42;

    Y=MAYUSCULAS;
}
void Letra2D::initQ(){
    X=856;
    W=43;

    Y=MAYUSCULAS;
}
void Letra2D::initR(){
    X=913;
    W=42;

    Y=MAYUSCULAS;
}
void Letra2D::initS(){
    X=967;
    W=40;

    Y=MAYUSCULAS;
}
void Letra2D::initT(){
    X=1022;
    W=40;

    Y=MAYUSCULAS;
}
void Letra2D::initU(){
    X=1073;
    W=43;

    Y=MAYUSCULAS;
}
void Letra2D::initV(){
    X=1132;
    W=46;

    Y=MAYUSCULAS;
}
void Letra2D::initW(){
    X=1188;
    W=62;

    Y=MAYUSCULAS;
}
void Letra2D::initX(){
    X=1255;
    W=52;

    Y=MAYUSCULAS;
}
void Letra2D::initY(){
    X=1319;
    W=46;

    Y=MAYUSCULAS;
}
void Letra2D::initZ(){
    X=0;
    W=43;

    Y=266;
}
