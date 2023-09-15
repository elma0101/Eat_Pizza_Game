#include<iostream>
#include<time.h>
#include<vector>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>




int main()
{
    sf::RenderWindow window(sf::VideoMode(612,376), "SFML works !");

   
    sf::Texture texture,luffy,food_texture;
    sf::Sprite sprite,sprite_luffy;
    sf::Font font;
   
    
    font.loadFromFile("game_over.ttf");
  
    sf::Text text,text_score;
    std::vector<sf::Sprite> foods;
    
    char score_string[30];

    float velocityX = 0.0f;
    float velocityY=0.0f;
    float jumpforce=-8.0f;
    float gravity = 0.5f;

    int score=0,value,food_value=0;
    int prev_direc = 0;
    bool isjumping = false;

   


    srand(time(NULL));

  

    if (!texture.loadFromFile("background.jpg"))
    {
        std::cout << "error on loading the photo ";
    }
    if (!luffy.loadFromFile("1234.png"))
    {
        std::cout << "error on loading the photo ";
    }
    if (!food_texture.loadFromFile("pizza.png"))
    {
        std::cout << "error on loading the photo ";
    }

    sprite_luffy.setTexture(luffy);
    sprite_luffy.setTextureRect(sf::IntRect(0,0,52,51));
    sprite.setTexture(texture);
    sprite_luffy.setPosition(100,233);
    sprite_luffy.setScale(1,1);

    
    while (window.isOpen())
    {
        sf::Event event;

        

        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space && !isjumping) {
                    velocityY = jumpforce;
                    isjumping = true;
                }

            }
         }
  
      //GENERATE FOOD + DRAW THE BACKGROUND

      value = rand() % 600 +1;
      if(food_value!=1)
      { 
        if (value < 5) {
           
            
           
           sf::Sprite food_sprite;
           food_sprite.setTexture(food_texture);
           food_sprite.setPosition(rand() % 500, 0);
           foods.push_back(food_sprite);
        }

        
        window.clear();
        window.draw(sprite);
        window.draw(sprite_luffy);

        for (size_t i = 0; i < foods.size(); ++i)
        {
            sf::Sprite& food = foods[i];
            window.draw(food);
            food.move(0, 5);
           

           if ((food.getPosition().x >= sprite_luffy.getPosition().x - 50 && food.getPosition().x <= sprite_luffy.getPosition().x + 50) && (food.getPosition().y >= sprite_luffy.getPosition().y - 2 && food.getPosition().y <= sprite_luffy.getPosition().y + 2))
           {
               
                foods.erase(foods.begin() + i);
                --i;
                score += 10;
                
               /* sound.play();*/
                sprintf_s(score_string, "score : %d", score);
                text_score.setString(score_string);
                text_score.setFont(font);
                text_score.setCharacterSize(50);
                text_score.setPosition(500, 5);
                text_score.setFillColor(sf::Color::Red);
           }

           //GAME OVER

           if (food.getPosition().y > 300)
           {
               food_value = 1;
               foods.erase(foods.begin() + i);

           }
               
       }

      }
       
        
      if (food_value == 1)
      {
          window.clear();
          text.setString("GAME OVER !");
          text.setFont(font);
          text.setCharacterSize(60);
          text.setPosition(230,130);
          text.setFillColor(sf::Color::Red);
          text_score.setPosition(250, 180);

      }
      
      int Xtexture = 0;

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)   ) {
          
          Xtexture = (int)sprite_luffy.getPosition().x / 33 % 7;
          std::cout << Xtexture << "\n";
          Xtexture *= 52;
          if(! isjumping)
          sprite_luffy.setTextureRect(sf::IntRect(Xtexture, 88, 52, 51));
          prev_direc = -1;
          velocityX = -8.0f;

      }
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
           
          Xtexture = (int)sprite_luffy.getPosition().x / 33 % 7;
          std::cout << Xtexture << "\n";
          Xtexture *= 52;
          if (! isjumping)
          sprite_luffy.setTextureRect(sf::IntRect(Xtexture, 0, 52, 51));
          prev_direc = 1;
          velocityX = 8.0f;

      }
      else {
          if (!isjumping)
          {
              if(prev_direc==1) sprite_luffy.setTextureRect(sf::IntRect(0, 0, 52, 51));
              else if(prev_direc==-1)sprite_luffy.setTextureRect(sf::IntRect(0,88,52,51));
          }
         

          velocityX = 0.0f;

      }
            
            
            
        
        

        //JUMP MOVEMENT

        if (isjumping)
        {
            Xtexture = (int)sprite_luffy.getPosition().x / 50% 7;
            Xtexture *= 51;
            velocityY += gravity;
            sprite_luffy.setTextureRect(sf::IntRect(Xtexture,176, 52, 51));
            sprite_luffy.move(0, velocityY);

        }
         

        if (sprite_luffy.getPosition().y >= 233)
        {
            isjumping = false;
            sprite_luffy.setPosition(sprite_luffy.getPosition().x, 233);
            velocityY = 0;
        }

        sprite_luffy.move(velocityX, 0);
        
        //COLLISION

        if ((sprite_luffy.getPosition().x ) <= 0)
            sprite_luffy.setPosition(0, sprite_luffy.getPosition().y);
        else if((sprite_luffy.getPosition().x )>=590)
            sprite_luffy.setPosition(590, sprite_luffy.getPosition().y);





      
       
      
        
        window.draw(text);
        window.draw(text_score);

        window.display();
    }
    
    return 0;
}


