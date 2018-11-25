
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
