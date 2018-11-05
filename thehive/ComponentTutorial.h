
//Para crear una nueva componente:

->Enum.hpp<-
Registrar el tipo de componente en Enum.hpp
    enum EComponentType{
        TRANSFORM = 0,
        KEYBOARD,
        RENDERABLE_3D,

        NUEVO_TIPO_DE_COMPONENTE,

        NUM_COMPONENTS        <<---- Esta siempre debe estar la última
    };

->Clase<-
C[Nombre] -> Respetar nombre de clases, empieza por "C" Seguido del nombre

-CNewComponent.hpp
    [Obligatorio]   #include <ComponentArch/IComponent.hpp>
    [Opcional]      Otras clases necesarias, por ejemplo la fachada del modelo 3D
                    Ej:         #include <GameEngine/Model.hpp>

    [Obligatorio]   static void initComponent();

    [Opcional]  -   Por si necesitas inicializar las variables de instancia de la clase
        |-------->  virtual void initializeComponentData(const void* data);


    [Opcional]      Por si necesitas procesar un mensaje (Por ahora sólo está M_UPDATE)
        |-------->  virtual gg::EMessageStatus processMessage();


-CNewComponent.cpp
    [Obligatorio]   #include <ComponentArch/ObjectManager.hpp>

    [Opcional]      Por si necesitas acceder a otra componente de esta/otra entidad
        |-------->  #include <Singleton.hpp>
                    #include <ComponentArch/ObjectManager.hpp>

    [Opcional]      Por si necesitas acceder a algún método de la fachada de Irrlicht (GameEngine)
        |-------->  #include <Singleton.hpp>
                    #include <ComponentArch/GameEngine.hpp>

    [Opcional]      Por si necesitas inicializar las variables de instancia de la clase
        |-------->  #include <ComponentArch/InitStructs.hpp>


    [Obligatorio]   Inicializador de clase, puede estar vacío, pero debe estar.
        |           -cType          = Tipo de componente que debe estar en Enum.hpp
        |           -cMessageType   = Tipo de mensaje que debe estar en MessageTypes.hpp
        |
        void CNewComponent::initComponent() {
            [Linea_opcional] Singleton<ObjectManager>::Instance()->subscribeComponentTypeToMessageType(gg::cType, gg::cMessageType);
            // Si no pusieras nada, no tentría sentido poner el método processMessage(); ya que nunca recibirá ningún mensaje
        }


    [Opcional]      Inicializador de variables de instancia, recibe como parámetro un *void
        |
        void CRenderable_3D::initializeComponentData(const void* data){

            // Debes convertr el puntero a void, a un puntero a la estructura inicializadora definida en InitStructs.hpp
            ICNewComponent* cData = (ICNewComponent*)data;
            //Usar los datos
            cData->Valor1
            cData->Valor2
            ...
        }


    [Opcional]      Manejeador de mensajes
        |
        gg::EMessageStatus CRenderable_3D::processMessage() {

            //  Aquí diferenciaríamos entre los diferents tipos de mensaje (con if, switch, punteros a función...)

            //  Si quisiéramos ver si esta entidad, tiene la componente TRANSFORM, lo haríamos así:
            CTransform* cTransform = static_cast<CTransform*>(Singleton<ObjectManager>::Instance()->getComponent(gg::TRANSFORM, getEntityID()));
            if(cTransform)
                //Tiene la entidad

            return gg::ST_TRUE; // Devuelve un mensaje de éxito o error, aunque ahora no se usa
        }



-ObjectManager.hpp
    [Obligatorio]   Incluir el .hpp de la nueva componente

        #include "Components/CTransform.hpp"
        #include "Components/CKeyboard.hpp"
        #include "Components/CRenderable_3D.hpp"
        #include "Components/CNewComponent.hpp"

    [Obligatorio]   Declarar la función que devuelve un puntero al nuevo tipo de componente
        IComponent* createTransformComponent        ();
        IComponent* createKeyboardComponent         ();
        IComponent* createRenderable_3DComponent    ();
        IComponent* createNewComponentComponent     ();     <<-------


-ObjectManager.cpp

    [Obligatorio]   Guardar en el array de punteros, el puntero a la función creada previamente
        |
        ObjectManager::ObjectManager()
        :memory(128)
        {
            nextAvailableEntityID.push(1);

            ComponentConstructorVector[0]= &ObjectManager::createTransformComponent;
            ComponentConstructorVector[1]= &ObjectManager::createKeyboardComponent;
            ComponentConstructorVector[2]= &ObjectManager::createRenderable_3DComponent;
            ComponentConstructorVector[4]= &ObjectManager::createNewComponentComponent;     <<-------
        }

    [Obligatorio]   Llamar al inicializador de clase
        |
        void ObjectManager::initObjectManager() {
            CTransform::initComponent();
            CKeyboard::initComponent();
            CRenderable_3D::initComponent();
            CNewComponent::initComponent();     <<-------
        }

    [Obligatorio]   Definir por último, la función constructora (Están al final)
        |
        IComponent* ObjectManager::createNewComponentComponent     ()   {
            return new CNewComponent;
        }


-InitStructs.hpp e InitStructs.cpp
    [Opcional]  Definir la estrutura inicializadora de las varibles de instancia de nuestra nueva componente

    Por ejemplo, la componente Transform, tiene 9 floats
    struct ICTransform{

        ICTransform(
            float  _x, float  _y, float  _z,
            float _rx, float _ry, float _rz,
            float _sx, float _sy, float _sz
        );

        float  x,  y,  z;
        float rx, ry, rz;
        float sx, sy, sz;
    };

    Esto es lo que usará el método initializeComponentData(const *void);



