#include "pch.h"
#include <iostream>
#include <string>
using namespace std;


class Window {
public:
    virtual string render() = 0;
    virtual ~Window() = default;
};

class Scrollbar {
public:
    virtual string render() = 0;
    virtual ~Scrollbar() = default;
};


class WindowsWindow : public Window {
public:
    string render() override {
        return "Rendering Windows-style Window";
    }
};

class WindowsScrollbar : public Scrollbar {
public:
    string render() override {
        return "Rendering Windows-style Scrollbar";
    }
};


class LinuxWindow : public Window {
public:
    string render() override {
        return "Rendering Linux-style Window";
    }
};

class LinuxScrollbar : public Scrollbar {
public:
    string render() override {
        return "Rendering Linux-style Scrollbar";
    }
};



class GUIFactory {
public:
    virtual Window* createWindow() = 0;
    virtual Scrollbar* createScrollbar() = 0;
    virtual ~GUIFactory() = default;
};



class WindowsFactory : public GUIFactory {
public:
    Window* createWindow() override {
        return new WindowsWindow();
    }

    Scrollbar* createScrollbar() override {
        return new WindowsScrollbar();
    }
};

class LinuxFactory : public GUIFactory {
public:
    Window* createWindow() override {
        return new LinuxWindow();
    }

    Scrollbar* createScrollbar() override {
        return new LinuxScrollbar();
    }
};



class Application {
private:
    GUIFactory* factory;
    Window* window;
    Scrollbar* scrollbar;

public:
    Application(GUIFactory* f) : factory(f) {
        window = factory->createWindow();
        scrollbar = factory->createScrollbar();
    }

    string paintUI() {
        return window->render() + " & " + scrollbar->render();
    }

    ~Application() {
        delete window;
        delete scrollbar;
    }
};



TEST(GUIFactoryTest, WindowsFactoryTest) {
    WindowsFactory factory;
    Application app(&factory);
    string result = app.paintUI();
    EXPECT_EQ(result, "Rendering Windows-style Window & Rendering Windows-style Scrollbar");
}

TEST(GUIFactoryTest, LinuxFactoryTest) {
    LinuxFactory factory;
    Application app(&factory);
    string result = app.paintUI();
    EXPECT_EQ(result, "Rendering Linux-style Window & Rendering Linux-style Scrollbar");
}
