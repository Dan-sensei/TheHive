
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
C[Nombre] -> Respeta hermano el nombre de las clases, empieza por "C" Seguido del nombre

    Mirar "CPlantilla.hpp" y "CPlantilla.cpp"


-ObjectManager.hpp
    [Obligatorio]   Incluir el .hpp de la nueva componente

        #include "Components/CTransform.hpp"
        #include "Components/CPlayerController.hpp"
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
            CPlayerController::initComponent();
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

    Por ejemplo, la componente Transform, tiene 6 floats
    struct ICTransform{

        ICTransform(
            float  _x, float  _y, float  _z,
            float _rx, float _ry, float _rz
        );

        float  x,  y,  z;
        float rx, ry, rz;
    };

    Esto es lo que usará el método initializeComponentData(const *void);


