#include "../smolEngine/Application.h"
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

int main(int argc, char** argv)
{

    auto app = CreateApplication(argc, argv);
    app->Run();

    delete app;

    return 0;
}
