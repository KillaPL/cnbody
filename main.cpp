#include <Gosu/Gosu.hpp>
      
class GameWindow : public Gosu::Window
{
public:
    GameWindow()
    :   Window(1000, 1000, false)
    {
        setCaption(L"Gosu Tutorial Game");
    }

    void update()
    {
    }

    void draw()
    {
    }
};

int main()
{
    GameWindow window;
    window.show();
}