#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class CustomRectangleShape : public sf::RectangleShape {
public:
    CustomRectangleShape(const sf::Vector2f &size, const sf::Vector2f &position) : sf::RectangleShape(size)
    {
        setPosition(position);
    }

    void setSpeed(const int &x_speed, const int &y_speed, const int &ro_speed) {
        x_speed_ = x_speed;
        y_speed_ = y_speed;
        ro_speed_ = ro_speed;
    }

    void setBounds(const float &l_bound, const float &r_bound, const float &u_bound, const float d_bound) {
        l_bound_ = l_bound;
        r_bound_ = r_bound;
        u_bound_ = u_bound;
        d_bound_ = d_bound;
    }

    void animate(const sf::Time &elapsed) {
        bounce();
        float dt = elapsed.asSeconds();
        move(x_speed_*dt,y_speed_*dt);
        move(x_speed_*dt,y_speed_*dt);
    }

    void setSelected(bool is_selected)
    {
        isSelected_ = is_selected;
    }

    bool getSelected()
    {
        return isSelected_;
    }

    void moveInDirection(const sf::Time &elapsed, const sf::Keyboard:: Key &key) {
        sf::FloatRect bounds = getGlobalBounds();
        if(key == sf::Keyboard::Up && !(bounds.top <= 0.0))
        {
            move(0, -y_speed_ * elapsed.asSeconds());
        }
        else if(key == sf::Keyboard::Right && !(bounds.left >= r_bound_ - bounds.width))
        {
            move(x_speed_ * elapsed.asSeconds(), 0);
        }
        else if(key == sf::Keyboard::Down && !(bounds.top >= d_bound_ - bounds.height))
        {
            move(0, y_speed_ * elapsed.asSeconds());
        }
        else if(key == sf::Keyboard::Left && !(bounds.left <= 0.0))
        {
            move(-x_speed_ * elapsed.asSeconds(), 0);
        }

    }

    bool isClicked(sf::Vector2i &mouse_position) const {
        sf::FloatRect bounds = getGlobalBounds();
        if(mouse_position.x >= bounds.left && mouse_position.x <= bounds.left + bounds.width
                && mouse_position.y >= bounds.top && mouse_position.y <= bounds.top + bounds.height)
        {
            return true;
        }
        return false; // mouse not clicked on rectangle
    }
    void select()
        {
            if(isSelected_ == true)
            {
                setFillColor(sf::Color(255, 0, 0));
            }
            else
            {
                setFillColor(sf::Color(0, 255, 0));
            }
        }


private:
    int x_speed_ = 0 ;
    int y_speed_ = 0 ;
    int ro_speed_ = 0 ;
    float l_bound_ = 0;
    float r_bound_ = 0;
    float u_bound_ = 0;
    float d_bound_ = 0;
    bool isSelected_ = false;


    void bounce() {
        sf::FloatRect rectangle_bounds = getGlobalBounds();

        if(rectangle_bounds.top <= u_bound_){
            y_speed_ = abs(y_speed_);
        }

        if(rectangle_bounds.top + rectangle_bounds.height >= d_bound_){
            y_speed_ = abs(y_speed_) * -1;
            setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }

        if(rectangle_bounds.left <= l_bound_ ){
            x_speed_ = abs(x_speed_);
            setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }

        if(rectangle_bounds.left + rectangle_bounds.width >= r_bound_){
            x_speed_ = abs(x_speed_) * -1;
            setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }
    }
    void change_color(sf::RectangleShape  &rectangle)
    {
        rectangle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
    }

};

int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");



    //    sf::RectangleShape rectangle(sf::Vector2f(120.0, 60.0));
    //    rectangle.setPosition(500.0, 400.0);
    //    rectangle.setFillColor(sf::Color(100, 50, 250));


    sf::Clock clock;

    //   sf::Vector2f size(120.0, 60.0);
    //   sf::Vector2f position(120.0, 60.0);
    //    sf::Vector2f position(std::rand() % (window.getSize().x - 120), std::rand() % (window.getSize().y - 60));
    //    CustomRectangleShape rectangle_an(size, position);
    //    rectangle_an.setFillColor(sf::Color(150, 100, 50));
    //    rectangle_an.setSpeed(100, 150, 10);
    std::srand(std::time(nullptr));
    std::vector<CustomRectangleShape> rectangles;
    for(int i=0; i<10; i++)
    {
        sf::Vector2f size(120.0, 60.0);
        sf::Vector2f position(std::rand() % (window.getSize().x - 120), std::rand() % (window.getSize().y - 60));
        rectangles.emplace_back(CustomRectangleShape(size, position));
    }

    for(auto &rec : rectangles)
    {
        rec.setFillColor(sf::Color(0, 255, 0));
        rec.setBounds(0, window.getSize().x, 0, window.getSize().y);
        rec.setSpeed(100, 200, 10);
    }






    // run the program as long as the window is open
    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();

        //rectangle_an.animate(elapsed);


        for(auto &rec : rectangles) {
            if(rec.getSelected() == false) continue;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                rec.moveInDirection(elapsed, sf::Keyboard::Up);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                rec.moveInDirection(elapsed, sf::Keyboard::Down);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                rec.moveInDirection(elapsed, sf::Keyboard::Left);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                rec.moveInDirection(elapsed, sf::Keyboard::Right);
            }
        }

        //        rectangle_an.setBounds(0, window.getSize().x, 0, window.getSize().y);




        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {

            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }



            //            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            //            {
            //                std::cout << "Holding up button" << std::endl;
            //            }

            //            if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
            //            {
            //                std::cout << "Holding right mouse button" << std::endl;
            //            }

            //            if(event.type == sf::Event::Closed)
            //           {
            //               std::cout << "Closing Window" << std::endl;
            //               window.close();
            //           }

            //           if(event.type == sf::Event::KeyReleased)
            //           {
            //               if(event.key.code == sf::Keyboard::Space)
            //                   std::cout << "Space released" << std::endl;
            //           }

            //           if(event.type == sf::Event::MouseButtonPressed)
            //           {
            //               if(event.mouseButton.button == sf::Mouse::Left)
            //               {
            //                   sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
            //                   std::cout << "Mouse clicked: " << mouse_pos.x << ", " << mouse_pos.y << std::endl;

            //               }
            //           }
            if(event.type == sf::Event::MouseButtonPressed)
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                    std::cout << "Mouse clicked: " << mouse_pos.x << ", " << mouse_pos.y << std::endl;
                    for(auto &rec : rectangles){
                        {
                            if(rec.isClicked(mouse_pos))
                            {
                                rec.setSelected(true);
                            }
                            else
                            {
                                rec.setSelected(false);
                            }
                            rec.select();

                    }
                }
            }
        }
    }



    // clear the window with black color
    window.clear(sf::Color::Black);

    // draw everything here...
    //        window.draw(rectangle);
    //        window.draw(rectangle_an);

    for(auto &rec : rectangles)
    {
        window.draw(rec);
    }

    // end the current frame
    window.display();
}

return 0;
}
