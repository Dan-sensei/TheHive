#include "HUD.hpp"

//      X               |   Y
// TL   0.78754578754   |   0.32724902216
// TR   0.98901098901   |   0.32724902216
// BL   0.78754578754   |   0.96610169491
// BR   0.98901098901   |   0.96610169491

#define X_PRIMARY_BULLETS       0.79194139194f
#define Y_PRIMARY_BULLETS       0.80964797914f
#define X_PRIMARY_CHAMBER       0.88278388278f
#define Y_PRIMARY_CHAMBER       0.83572359843f

#define X_SECONDARY_BULLETS     0.94139194139f
#define Y_SECONDARY_BULLETS     0.90482398957f
#define X_SECONDARY_CHAMBER     0.90915750915f
#define Y_SECONDARY_CHAMBER     0.90482398957f

#define HABS_SIZE               0.04029304029f

#define X_HAB_BM                0.86813186813f
#define Y_HAB_BM                0.50065189048f

#define X_HAB_TR                0.91868131868f
#define Y_HAB_TR                0.32724902216f

#define X_HAB_TL                0.81831501831f
#define Y_HAB_TL                0.32724902216f

#define X_HEALTH                0.4336996337f
#define Y_HEALTH                0.59843546284f
#define W_HEALTH                0.5663003663f

#define WHITE_COLOR         glm::vec4(1,1,1,1)
#define WHITE_ALPHA         glm::vec4(1,1,1,0.5)
#define RED_COLOR           glm::vec4(0.459,0.161,0.161,1)
#define BLUE                glm::vec4(0,0.635,1,1)

#define __ZERO 0


HUD::HUD():
INIT(false),
VAO(-1),VAO_2(-1),
VBO(-1),VBO_2(-1),
EBO(-1),EBO_2(-1),
IndexBuffer(-1),
textureID(-1),
crucetaG(-1),crucetaP(-1),actualCruceta(-1),
IMG_PrimaryW_P(-1),IMG_PrimaryW_S(-1),
IMG_SecondaryW_P(-1),IMG_SecondaryW_S(-1),
IMG_Actual_P(-1),IMG_Actual_S(-1)
{}

HUD::~HUD(){
    if(INIT){
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);

        glDeleteVertexArrays(1, &VAO_2);
        glDeleteBuffers(1, &VBO_2);
    }
}

void HUD::initHUD(unsigned int SW, unsigned int SH, unsigned int TEX, Shader* _SHADER){
    INIT = true;

    textureID = TEX;
    SHADER = _SHADER;

    TEXT_PrimaryBullets = Texto2D(X_PRIMARY_BULLETS,Y_PRIMARY_BULLETS,"",WHITE_COLOR,55);
    TEXT_PrimaryChamber = Texto2D(X_PRIMARY_CHAMBER,Y_PRIMARY_CHAMBER,"",RED_COLOR,30);

    TEXT_SecondaryBullets = Texto2D(X_SECONDARY_BULLETS,Y_SECONDARY_BULLETS,"",WHITE_COLOR,50);
    TEXT_SecondaryChamber = Texto2D(X_SECONDARY_CHAMBER,Y_SECONDARY_CHAMBER,"",RED_COLOR,20);

    HAB_BM = Cuadrado2D(X_HAB_BM+HABS_SIZE,Y_HAB_BM+(HABS_SIZE*1.8f*__ZERO),X_HAB_BM,Y_HAB_BM);
    HAB_BM.setColor(WHITE_ALPHA);

    HAB_TR = Cuadrado2D(X_HAB_TR+HABS_SIZE,Y_HAB_TR+(HABS_SIZE*1.8f*__ZERO),X_HAB_TR,Y_HAB_TR);
    HAB_TR.setColor(WHITE_ALPHA);

    HAB_TL = Cuadrado2D(X_HAB_TL+HABS_SIZE,Y_HAB_TL+(HABS_SIZE*1.8f*__ZERO),X_HAB_TL,Y_HAB_TL);
    HAB_TL.setColor(WHITE_ALPHA);

    HEALTH_BAR = Cuadrado2D(X_HEALTH+(W_HEALTH-X_HEALTH),Y_HEALTH+0.02,X_HEALTH,Y_HEALTH);
    HEALTH_BAR.setColor(BLUE);

    auto manager = Singleton<AssetManager>::Instance();

    crucetaG = manager->getTexture("assets/HUD/NUEVO/cruceta_g.png");
    crucetaP = manager->getTexture("assets/HUD/NUEVO/cruceta_p.png");
    actualCruceta = crucetaG;

    // /////////////////////////////////////////////////
    // Plantilla de las armas
    // /////////////////////////////////////////////////
    float RENDER_QUAD[] = {
        (0.78754578754f*2)-1,  -((0.32724902216f*2)-1), 0.0f, 0.0f, // TL
        (0.98901098901f*2)-1,  -((0.32724902216f*2)-1), 1.0f, 0.0f, // TR
        (0.98901098901f*2)-1,  -((0.96610169491f*2)-1), 1.0f, 1.0f, // BR
        (0.78754578754f*2)-1,  -((0.96610169491f*2)-1), 0.0f, 1.0f, // BL
    };
    // Backup
    // (0.78754578754f*2)-1,  -((0.32724902216f*2)-1), 0.0f, 0.0f,
    // (0.78754578754f*2)-1,  -((0.96610169491f*2)-1), 0.0f, 1.0f,
    // (0.98901098901f*2)-1,  -((0.32724902216f*2)-1), 1.0f, 0.0f,
    // (0.98901098901f*2)-1,  -((0.96610169491f*2)-1), 1.0f, 1.0f,

    GLuint elements[] = {
        2, 1, 0,
    	0, 3, 2
    };

    glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(RENDER_QUAD), &RENDER_QUAD, GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
    	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glVertexAttribFormat(0, 2, GL_FLOAT, false, 0);
        glVertexAttribFormat(1, 2, GL_FLOAT, false, 8);

        glVertexAttribBinding(0, 0);
        glVertexAttribBinding(1, 0);

        glBindVertexBuffer(0, VBO, 0, 16);
    glBindVertexArray(0);

    // /////////////////////////////////////////////////
    // Cruceta
    // /////////////////////////////////////////////////
    float RENDER_QUAD2[] = {
        (0.45641025641f*2)-1,  -((0.42242503259f*2)-1), 0.0f, 0.0f, // TL
        (0.54358974359f*2)-1,  -((0.42242503259f*2)-1), 1.0f, 0.0f, // TR
        (0.54358974359f*2)-1,  -((0.5775749674f*2 )-1), 1.0f, 1.0f, // BR
        (0.45641025641f*2)-1,  -((0.5775749674f*2 )-1), 0.0f, 1.0f, // BL
    };

    glGenVertexArrays(1, &VAO_2);
        glGenBuffers(1, &VBO_2);
        glBindVertexArray(VAO_2);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_2);
        glBufferData(GL_ARRAY_BUFFER, sizeof(RENDER_QUAD2), &RENDER_QUAD2, GL_STATIC_DRAW);

        glGenBuffers(1, &EBO_2);
    	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_2);
    	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glVertexAttribFormat(0, 2, GL_FLOAT, false, 0);
        glVertexAttribFormat(1, 2, GL_FLOAT, false, 8);

        glVertexAttribBinding(0, 0);
        glVertexAttribBinding(1, 0);

        glBindVertexBuffer(0, VBO_2, 0, 16);
    glBindVertexArray(0);
}

void HUD::draw(){
    drawHUDItem(-0.995,textureID,VAO);

    if(IMG_Actual_P != -1)
        drawHUDItem(-0.996,IMG_Actual_P,VAO);
    if(IMG_Actual_S != -1)
        drawHUDItem(-0.997,IMG_Actual_S,VAO);

    drawHUDItem(-0.996,actualCruceta,VAO_2);

    // BALAS
    TEXT_PrimaryBullets.Draw();
    TEXT_PrimaryChamber.Draw();

    TEXT_SecondaryChamber.Draw();
    TEXT_SecondaryBullets.Draw();

    // Cuadrados del cooldown
    HAB_BM.Draw();
    HAB_TR.Draw();
    HAB_TL.Draw();
    HEALTH_BAR.Draw();
}

void HUD::aim(const uint8_t &s){
    if(s){
        actualCruceta = crucetaG;
    }
    else{
        actualCruceta = crucetaP;
    }
}

void HUD::set_TL_CD(const float &cd){ HAB_TL.setPos(X_HAB_BM+HABS_SIZE,Y_HAB_BM+(HABS_SIZE*1.8f),X_HAB_BM,Y_HAB_BM+(HABS_SIZE*1.8f*cd)); }
void HUD::set_TR_CD(const float &cd){ HAB_TR.setPos(X_HAB_TR+HABS_SIZE,Y_HAB_TR+(HABS_SIZE*1.8f),X_HAB_TR,Y_HAB_TR+(HABS_SIZE*1.8f*cd)); }
void HUD::set_BM_CD(const float &cd){ HAB_BM.setPos(X_HAB_TL+HABS_SIZE,Y_HAB_TL+(HABS_SIZE*1.8f),X_HAB_TL,Y_HAB_TL+(HABS_SIZE*1.8f*cd)); }

void HUD::setPrimaryBullets(const int &n)  { TEXT_PrimaryBullets.setText(std::to_string(n));   }
void HUD::setPrimaryChamber(const int &n)  { TEXT_PrimaryChamber.setText(std::to_string(n));   }
void HUD::setSecondaryBullets(const int &n){ TEXT_SecondaryBullets.setText(std::to_string(n)); }
void HUD::setSecondaryChamber(const int &n){ TEXT_SecondaryChamber.setText(std::to_string(n)); }

void HUD::setPrimaryImg(const unsigned int &idP, const unsigned int &idS){
    IMG_PrimaryW_P   = idP;
    IMG_PrimaryW_S   = idS;
    IMG_Actual_P     = idP;
}
void HUD::setSecondaryImg(const unsigned int &idP, const unsigned int &idS){
    IMG_SecondaryW_P = idP;
    IMG_SecondaryW_S = idS;
    IMG_Actual_S     = idS;
}

void HUD::changeHUDWeapon(){
    if(IMG_Actual_P == IMG_PrimaryW_P){
        // PRINCIPAL POR SECUNDARIA
        IMG_Actual_P = IMG_SecondaryW_P;
        IMG_Actual_S = IMG_PrimaryW_S;
    }
    else{
        // SECUNDARIA POR PRINCIPAL
        IMG_Actual_P = IMG_PrimaryW_P;
        IMG_Actual_S = IMG_SecondaryW_S;
    }
}

void HUD::setHealthBarPc(const float &pc){
    HEALTH_BAR.setPos(X_HEALTH+((W_HEALTH-X_HEALTH)*pc),Y_HEALTH+0.02,X_HEALTH,Y_HEALTH);
}

void HUD::drawHUDItem(const float &_ZINDEX, const unsigned int &_IMG, const unsigned int &_VAO){
    SHADER->Bind();

    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _IMG);

    glUniform1f(3,_ZINDEX);

    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
