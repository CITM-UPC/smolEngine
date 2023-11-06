#include "../smolEngine/Application.h"

class smolEditorApp : public Application
{
public:

    smolEditorApp(int argc, char** argv) : Application(argc, argv)
    {
        AddModuleBack(new Editor());
    }

    ~smolEditorApp()
    {

    }
};

Application* CreateApplication(int argc, char** argv)
{
    return new smolEditorApp(argc, argv);
}