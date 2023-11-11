#include "../smolEngine/Application.h"
#include "../smolEngine/Defs.h"
#include "Editor.h"

class smolEditorApp : public Application
{
public:

    smolEditorApp(int argc, char** argv) : Application(argc, argv)
    {
        AddModuleBack(new Editor(true));
    }

    ~smolEditorApp()
    {

    }
};

Application* CreateApplication(int argc, char** argv)
{
    return new smolEditorApp(argc, argv);
}

Application* app = NULL;

int main(int argc, char** argv)
{

    app = CreateApplication(argc, argv);
    app->Run();

    delete app;

    return 0;
}
