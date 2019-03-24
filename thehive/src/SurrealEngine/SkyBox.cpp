#include "SkyBox.hpp"

SkyBox::SkyBox()
:engine(nullptr)
{
    engine=Singleton<SurrealEngine>::Instance();
    auto manager =Singleton<AssetManager>::Instance();
    inicio=manager->getShader("skyboxShader");
    fin=manager->getShader("Default");

    view=inicio->getUniformLocation("view");
    text=inicio->getUniformLocation("skybox");

    skyboxtype = 0;

     //otro forma de cargar el cubemap
    // std::vector<std::string> auxfaces // Cargamos las imagenes que forman la skybox
    // {
    //     "assets/skybox/right.tga", //right
    //     "assets/skybox/left.tga", //left
    //     "assets/skybox/top.tga", //top
    //     "assets/skybox/bottom.tga", //bottom
    //     "assets/skybox/back.tga", //back
    //     "assets/skybox/front.tga" //front
    // };

    //cubemapTexture = this->loadCubemap(auxfaces);




    // //
    // std::vector<const GLchar*> faces;
    // faces.reserve(6);
    // faces.resize(6);
    // faces[0] = ( "assets/skybox/skybox2RT.png" );
    // faces[1] = ( "assets/skybox/skybox2LF.png" );
    // faces[2] = ( "assets/skybox/skybox2UP.png" );
    // faces[3] = ( "assets/skybox/skybox2DN.png" );
    // faces[4] = ( "assets/skybox/skybox2FT.png" );
    // faces[5] = ( "assets/skybox/skybox2BK.png" );
    // cubemapTexture = loadCubemap(faces);

    std::vector<const GLchar*> faces;
    faces.reserve(6);
    faces.resize(6);

    faces[0] = ( "assets/skybox/skyboxRT.png" );
    faces[1] = ( "assets/skybox/skyboxLF.png" );
    faces[2] = ( "assets/skybox/skyboxUP.png" );
    faces[3] = ( "assets/skybox/skyboxDN.png" );
    faces[4] = ( "assets/skybox/skyboxFT.png" );
    faces[5] = ( "assets/skybox/skyboxBK.png" );
    cubemapTexture[0] = loadCubemap(faces);

    faces[0] = ( "assets/skybox/skybox2RT.png" );
    faces[1] = ( "assets/skybox/skybox2LF.png" );
    faces[2] = ( "assets/skybox/skybox2UP.png" );
    faces[3] = ( "assets/skybox/skybox2DN.png" );
    faces[4] = ( "assets/skybox/skybox2FT.png" );
    faces[5] = ( "assets/skybox/skybox2BK.png" );
    cubemapTexture[1] = loadCubemap(faces);

    faces[0] = ( "assets/skybox/skybox3RT.png" );
    faces[1] = ( "assets/skybox/skybox3LF.png" );
    faces[2] = ( "assets/skybox/skybox3UP.png" );
    faces[3] = ( "assets/skybox/skybox3DN.png" );
    faces[4] = ( "assets/skybox/skybox3FT.png" );
    faces[5] = ( "assets/skybox/skybox3BK.png" );
    cubemapTexture[2] = loadCubemap(faces);

}


SkyBox::~SkyBox(){
    glDeleteVertexArrays(1, &skyboxVAO);
    glDeleteBuffers(1, &skyboxVBO);
}

            //otro forma de cargar el cubemap
// unsigned int SkyBox::loadCubemap(std::vector<std::string> faces)
// {
//
//     unsigned int textureID;
//     glGenTextures(1, &textureID);
//     glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
//
//     int width, height, nrChannels;
//     for (unsigned int i = 0; i < faces.size(); i++)
//     {
//         unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
//         if (data)
//         {
//             glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
//                          0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
//             );
//             stbi_image_free(data);
//         }
//         else
//         {
//             //std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
//             stbi_image_free(data);
//         }
//     }
//     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//     //glBindTexture( GL_TEXTURE_CUBE_MAP, 0);
//
//
//     return textureID;
// }


unsigned int SkyBox::loadCubemap( std::vector<const GLchar * > faces)
    {
        unsigned int textureID;
        glGenTextures( 1, &textureID );

        int imageWidth, imageHeight;
        unsigned char *image;

        glBindTexture( GL_TEXTURE_CUBE_MAP, textureID );

        for ( GLuint i = 0; i < faces.size( ); i++ )
        {
            image = SOIL_load_image( faces[i], &imageWidth, &imageHeight, 0, SOIL_LOAD_RGB );
            glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image );
            SOIL_free_image_data( image );
        }
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
        //glBindTexture( GL_TEXTURE_CUBE_MAP, 0);

        return textureID;
    }

void SkyBox::init(){

    float a = 10000.0f;
    float b = -10000.0f;
    float centroX = 0.0f;
    float centroY = 0.0f;
    float centroZ = 100.0f;

    float skyboxVertices[] = {
    // positions
    b + centroX, a + centroY, b + centroZ,
    b + centroX, b + centroY, b + centroZ,
    a + centroX, b + centroY, b + centroZ,
    a + centroX, b + centroY, b + centroZ,
    a + centroX, a + centroY, b + centroZ,
    b + centroX, a + centroY, b + centroZ,

    b + centroX, b + centroY, a + centroZ ,
    b + centroX, b + centroY, b + centroZ ,
    b + centroX, a + centroY, b + centroZ ,
    b + centroX, a + centroY, b + centroZ ,
    b + centroX, a + centroY, a + centroZ ,
    b + centroX, b + centroY, a + centroZ ,

    a + centroX, b + centroY, b + centroZ,
    a + centroX, b + centroY, a + centroZ,
    a + centroX, a + centroY, a + centroZ,
    a + centroX, a + centroY, a + centroZ,
    a + centroX, a + centroY, b + centroZ,
    a + centroX, b + centroY, b + centroZ,

    b + centroX, b + centroY, a + centroZ,
    b + centroX, a + centroY, a + centroZ,
    a + centroX, a + centroY, a + centroZ,
    a + centroX, a + centroY, a + centroZ,
    a + centroX, b + centroY, a + centroZ,
    b + centroX, b + centroY, a + centroZ,

    b + centroX,  a + centroY, b + centroZ,
    a + centroX,  a + centroY, b + centroZ,
    a + centroX,  a + centroY, a + centroZ,
    a + centroX,  a + centroY, a + centroZ,
    b + centroX,  a + centroY, a + centroZ,
    b + centroX,  a + centroY, b + centroZ,

    b + centroX, b + centroY, b + centroZ,
    b + centroX, b + centroY, a + centroZ,
    a + centroX, b + centroY, b + centroZ,
    a + centroX, b + centroY, b + centroZ,
    b + centroX, b + centroY, a + centroZ,
    a + centroX, b + centroY, a + centroZ
    };


    glGenVertexArrays(1, &skyboxVAO );
    glGenBuffers(1, &skyboxVBO );
    glBindVertexArray( skyboxVAO );
    glBindBuffer( GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData( GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    //glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 3 * sizeof( GLfloat ), (GLvoid *) 0);
    glBindVertexArray(0);

    //tutotutorially
    //glDepthMask(GL_FALSE);

    //glBindVertexArray(skyboxVAO);
    //glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    //glDrawArrays(GL_TRIANGLES, 0, 36);
    //glDepthMask(GL_TRUE);


    //glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));

}

void SkyBox::Draw(){
    if(engine->key(gg::GG_5) && skyboxtype !=0){
        skyboxtype = 0;
    }
    if(engine->key(gg::GG_6) && skyboxtype !=1){
        skyboxtype = 1;
    }
    if(engine->key(gg::GG_7) && skyboxtype !=2){
        skyboxtype = 2;
    }

    auto viewt = engine->getVP();
    glDepthMask(GL_FALSE);
    glDepthFunc( GL_LEQUAL );
    inicio->Bind();
    //view = glm::mat4( glm::mat3( engine->getCam()->GetViewMatrix() ) );
    glUniformMatrix4fv(view, 1, GL_FALSE, &(viewt)[0][0]);
    //glUniformMatrix4fv( glGetUniformLocation( inicio.Program, "view" ), 1, GL_FALSE, glm::value_ptr( viewt ) );
    glBindVertexArray( skyboxVAO );
    glActiveTexture(GL_TEXTURE0);
    glBindTexture( GL_TEXTURE_CUBE_MAP, cubemapTexture[skyboxtype] );

    glUniform1i(text, 0);
    glDrawArrays( GL_TRIANGLES, 0, 36 );
    glBindVertexArray( 0 );
    glDepthFunc( GL_LESS );
    glDepthMask(GL_TRUE);

    fin->Bind();
}
