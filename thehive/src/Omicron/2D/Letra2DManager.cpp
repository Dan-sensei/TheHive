#include "Letra2DManager.hpp"
#include <Omicron/ZMESHES/ZMeshData.hpp>
#include <Omicron/AssetManager.hpp>
//#include <iostream>
#include <SOIL2/SOIL2.h>

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

inicio_y Z 330

Z       0       43
0       54      39
1       107     25
2       143     38
3       193     36
4       241     37
5       293     36
6       343     37
7       392     41
8       443     37
9       495     38
+       548     36
-       599     23
/       635     38
¿       681     30
?       732     29




*/

Letra2DManager::Letra2DManager():letraux(nullptr)
{
    auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    ancho = mode->width;
    alto = mode->height;

    mapHudFunctions.insert(std::make_pair('a',&Letra2D::inita));
    mapHudFunctions.insert(std::make_pair('b',&Letra2D::initb));
    mapHudFunctions.insert(std::make_pair('c',&Letra2D::initc));
    mapHudFunctions.insert(std::make_pair('d',&Letra2D::initd));
    mapHudFunctions.insert(std::make_pair('e',&Letra2D::inite));
    mapHudFunctions.insert(std::make_pair('f',&Letra2D::initf));
    mapHudFunctions.insert(std::make_pair('g',&Letra2D::initg));
    mapHudFunctions.insert(std::make_pair('h',&Letra2D::inith));
    mapHudFunctions.insert(std::make_pair('i',&Letra2D::initi));
    mapHudFunctions.insert(std::make_pair('j',&Letra2D::initj));
    mapHudFunctions.insert(std::make_pair('k',&Letra2D::initk));
    mapHudFunctions.insert(std::make_pair('l',&Letra2D::initl));
    mapHudFunctions.insert(std::make_pair('m',&Letra2D::initm));
    mapHudFunctions.insert(std::make_pair('n',&Letra2D::initn));
    mapHudFunctions.insert(std::make_pair('o',&Letra2D::inito));
    mapHudFunctions.insert(std::make_pair('p',&Letra2D::initp));
    mapHudFunctions.insert(std::make_pair('q',&Letra2D::initq));
    mapHudFunctions.insert(std::make_pair('r',&Letra2D::initr));
    mapHudFunctions.insert(std::make_pair('s',&Letra2D::inits));
    mapHudFunctions.insert(std::make_pair('t',&Letra2D::initt));
    mapHudFunctions.insert(std::make_pair('u',&Letra2D::initu));
    mapHudFunctions.insert(std::make_pair('v',&Letra2D::initv));
    mapHudFunctions.insert(std::make_pair('w',&Letra2D::initw));
    mapHudFunctions.insert(std::make_pair('x',&Letra2D::initx));
    mapHudFunctions.insert(std::make_pair('y',&Letra2D::inity));
    mapHudFunctions.insert(std::make_pair('z',&Letra2D::initz));

    mapHudFunctions.insert(std::make_pair('A',&Letra2D::initA));
    mapHudFunctions.insert(std::make_pair('B',&Letra2D::initB));
    mapHudFunctions.insert(std::make_pair('C',&Letra2D::initC));
    mapHudFunctions.insert(std::make_pair('D',&Letra2D::initD));
    mapHudFunctions.insert(std::make_pair('E',&Letra2D::initE));
    mapHudFunctions.insert(std::make_pair('F',&Letra2D::initF));
    mapHudFunctions.insert(std::make_pair('G',&Letra2D::initG));
    mapHudFunctions.insert(std::make_pair('H',&Letra2D::initH));
    mapHudFunctions.insert(std::make_pair('I',&Letra2D::initI));
    mapHudFunctions.insert(std::make_pair('J',&Letra2D::initJ));
    mapHudFunctions.insert(std::make_pair('K',&Letra2D::initK));
    mapHudFunctions.insert(std::make_pair('L',&Letra2D::initL));
    mapHudFunctions.insert(std::make_pair('M',&Letra2D::initM));
    mapHudFunctions.insert(std::make_pair('N',&Letra2D::initN));
    mapHudFunctions.insert(std::make_pair('O',&Letra2D::initO));
    mapHudFunctions.insert(std::make_pair('P',&Letra2D::initP));
    mapHudFunctions.insert(std::make_pair('Q',&Letra2D::initQ));
    mapHudFunctions.insert(std::make_pair('R',&Letra2D::initR));
    mapHudFunctions.insert(std::make_pair('S',&Letra2D::initS));
    mapHudFunctions.insert(std::make_pair('T',&Letra2D::initT));
    mapHudFunctions.insert(std::make_pair('U',&Letra2D::initU));
    mapHudFunctions.insert(std::make_pair('V',&Letra2D::initV));
    mapHudFunctions.insert(std::make_pair('W',&Letra2D::initW));
    mapHudFunctions.insert(std::make_pair('X',&Letra2D::initX));
    mapHudFunctions.insert(std::make_pair('Y',&Letra2D::initY));
    mapHudFunctions.insert(std::make_pair('Z',&Letra2D::initZ));


    mapHudFunctions.insert(std::make_pair('0',&Letra2D::init0));
    mapHudFunctions.insert(std::make_pair('1',&Letra2D::init1));
    mapHudFunctions.insert(std::make_pair('2',&Letra2D::init2));
    mapHudFunctions.insert(std::make_pair('3',&Letra2D::init3));
    mapHudFunctions.insert(std::make_pair('4',&Letra2D::init4));
    mapHudFunctions.insert(std::make_pair('5',&Letra2D::init5));
    mapHudFunctions.insert(std::make_pair('6',&Letra2D::init6));
    mapHudFunctions.insert(std::make_pair('7',&Letra2D::init7));
    mapHudFunctions.insert(std::make_pair('8',&Letra2D::init8));
    mapHudFunctions.insert(std::make_pair('9',&Letra2D::init9));



    mapHudFunctions.insert(std::make_pair('+',&Letra2D::initmore));
    mapHudFunctions.insert(std::make_pair('-',&Letra2D::initless));
    mapHudFunctions.insert(std::make_pair('/',&Letra2D::initdoblada));
    //mapHudFunctions.insert(std::make_pair('¿',&Letra2D::initint1));
    //mapHudFunctions.insert(std::make_pair('?',&Letra2D::initint2));



    letraux=new Letra2D(ancho,alto);

}
Letra2D* Letra2DManager::getChar(const char &letra){
    if(mapHudFunctions.find(letra) != mapHudFunctions.end())
        (letraux->*mapHudFunctions[letra])();
    letraux->secondinit();
    return letraux;

}
Letra2DManager::~Letra2DManager(){
    delete letraux;
}
