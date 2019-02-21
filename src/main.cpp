#include <sfml\Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <ctime>
#include "Gun.h"
#include "Explosion.h"
#include "Bullet.h"
#include "Invaders.h"
#include "Saucer.h"
#include "Bomb.h"
#include "HighScores.h"

const std::string InvaderImageFilename = "../invaders2.png";
const std::string BombImageFilename = "../bombs.png";
const std::string saucerImageFilename = "../saucer.png";

sf::Texture GunTexture;
sf::Texture BombTexture;
sf::Texture InvaderTexture;
sf::Texture SaucerTexture;

const sf::Vector2u NumInvaders{5,12};

std::string welcome(sf::RenderWindow& window, const HighScores&, Invaders& invaders);
std::string getWelcomeText();
char getKey();


int main()
{
    sf::RenderWindow window(sf::VideoMode(MainWindowWidth, MainWindowHeight), "Space Invaders", sf::Style::Close);
    bool pauseFlag = false;
    bool gameOver = false;
    int invaderHit = 0;
    sf::Vector2u invaderHitByBulletLocation;
    Score score;
  //  int score = 0;
    srand(time(0));

    /////// Background //////
    sf::RectangleShape background(sf::Vector2f(MainWindowWidth, MainWindowHeight));
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("../background.png");
    background.setTexture(&backgroundTexture);

    // Invaders
    InvaderTexture.loadFromFile(InvaderImageFilename);
    Invaders invaders;

    // The Guns
    const std::string GunImageFilename = "../gun.png";
    GunTexture.loadFromFile(GunImageFilename);

    int gunInPlay = 0;
    const int numGuns = 3;
    Gun gun[numGuns];

    // position the spare guns
    gun[1].moveToPosition(sf::Vector2f(760.0f+75.0f,30.0f));
    gun[2].moveToPosition(sf::Vector2f(760.0f+150.0f,30.0f));

    Explosion explosion("../explosion.png");

    // Bullets
    std::list<Bullet*> bulletsInFlight;

    // Bombs
    BombTexture.loadFromFile(BombImageFilename);
    Bomb* bombPtr = nullptr;

    // The Saucer
    Saucer* saucerPtr = nullptr;
    SaucerTexture.loadFromFile(saucerImageFilename);

    //////////// Sound effects /////////////
    sf::SoundBuffer invaderBuffer;
    invaderBuffer.loadFromFile("../frogs.wav");
    sf::Sound invaderSound;
    invaderSound.setBuffer(invaderBuffer);
    invaderSound.setLoop(true);

    sf::SoundBuffer bulletBuffer;
    bulletBuffer.loadFromFile("../bullet.wav");
    sf::Sound bulletSound;
    bulletSound.setBuffer(bulletBuffer);
    bulletSound.setVolume(25.0f);

    sf::SoundBuffer explosionBuffer;
    explosionBuffer.loadFromFile("../explosion.wav");
    sf::Sound explosionSound;
    explosionSound.setBuffer(explosionBuffer);

    sf::SoundBuffer saucerBuffer;
    saucerBuffer.loadFromFile("../saucer.wav");
    sf::Sound saucerSound;
    saucerSound.setBuffer(saucerBuffer);
    saucerSound.setLoop(true);
    saucerSound.setVolume(10.0f);

    sf::SoundBuffer bombBuffer;
    bombBuffer.loadFromFile("../bomb.wav");
    sf::Sound bombSound;
    bombSound.setBuffer(bombBuffer);
    bombSound.setVolume(8.0f);

    sf::SoundBuffer bombExplosionBuffer;
    bombExplosionBuffer.loadFromFile("../bomb_explosion.wav");
    sf::Sound bombExplosionSound;
    bombExplosionSound.setBuffer(bombExplosionBuffer);

    // Declare and load a font
    sf::Font font;
    font.loadFromFile("../arial.ttf");
    // Create a text
    sf::Text text(sf::String(""), font);
    text.setCharacterSize(24);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color(10,250,50));
    text.setPosition(80.0f,20.0f);

    // Game Speed controls
    float deltaTime = .2f;
    float switchTime = .2f;
    float totalTime = 0.0f;
    sf::Clock clock;

    unsigned loopCount = 0;

    HighScores highScores;

    std::string name = welcome(window, highScores, invaders);
    invaders.moveInvadersToStartPosition();
    window.setTitle(sf::String(name + "\'s Space Invaders"));

    while (window.isOpen())
    {
        while (gunInPlay < numGuns && !gameOver)
        {
            deltaTime = clock.restart().asSeconds();
            sf::Event evnt;
            while (window.pollEvent(evnt))
            {
                switch (evnt.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))  // pause
                        pauseFlag = !pauseFlag;
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))  // move to the right
                        if (!pauseFlag)
                            gun[0].move(Gun::Right);
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  // move to the left
                        if (!pauseFlag)
                            gun[0].move(Gun::Left);
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))  // shoot the gun
                    {
                        if (!pauseFlag)
                        {
                            bulletsInFlight.push_back(gun[0].shoot());
                            score += -1;  // subtract one point for each bullet
                            bulletSound.play();
                        }
                    }
                default:
                    ;
                }
            }
            if (!pauseFlag && loopCount > 3000 && rand()%100 > 96 && saucerPtr == nullptr)
            {
                saucerPtr = new Saucer;
                saucerSound.play();
                loopCount = 0;
            }
            if (!pauseFlag && loopCount > 3000 && rand()%100 < 3 && bombPtr == nullptr)
            {
                bombSound.play();
                bombPtr = new Bomb();
                bombPtr -> moveBombToStartPosition(invaders);
                loopCount = 0;
            }
            window.clear();
            window.draw(background);
            if (pauseFlag)
                invaderSound.stop();
            if (!pauseFlag)
            {
                totalTime += deltaTime;
                if(totalTime >= switchTime)
                {
                    totalTime -= switchTime;
                    if (saucerSound.getStatus() == sf::SoundSource::Stopped)
                    {
                        if (invaderSound.getStatus() == sf::SoundSource::Stopped)
                            invaderSound.play();
                    }
                    else
                    {
                        invaderSound.stop();
                    }
                    invaders.move();
                }

                if(saucerPtr)
                {
                    if (!saucerPtr->move())
                    {
                        saucerSound.stop();
                        delete saucerPtr;
                        saucerPtr = nullptr;
                    }
                }
                if (bombPtr)
                {
                    if (!bombPtr->move())
                    {
                        bombSound.stop();
                        delete bombPtr;
                        bombPtr = nullptr;
                    }
                    else
                    {
                        if (gun[0].hitByBomb(*bombPtr))
                        {
                            std::cout << "Gun hit by bomb\n";
                            bombSound.stop();
                            bombExplosionSound.play();

                            delete bombPtr;
                            bombPtr = nullptr;
                            explosion.startExplosion(gun[0].getPosition());
                        }
                    }
                }

                // move and display the bullets in flight
                for (auto it = bulletsInFlight.begin(); it!= bulletsInFlight.end(); ++it)
                {
                    if (!(*it)->move())
                    {
                        delete (*it);
                        *it = nullptr;
                        bulletsInFlight.erase(it);
                        break;
                    }
                    invaderHit = invaders.invaderHitByBullet(**it);
                    if (invaderHit)
                    {
                        score += invaderHit;
                        explosionSound.play();
                        delete (*it);
                        *it = nullptr;
                        bulletsInFlight.erase(it);
                        break;
                    }
                    else if (bombPtr && bombPtr->hitByBullet(**it))
                    {
                        std::cout << "** Bomb hit by bullet" << std::endl;
                        score += 20;  // 20 points for hitting a bomb
                        bombSound.stop();
                        explosionSound.play();
                        explosion.startExplosion(bombPtr->getPosition());

                        // remove bullet
                        delete (*it);
                        *it = nullptr;
                        bulletsInFlight.erase(it);

                        // remove the bomb
                        delete bombPtr;
                        bombPtr = nullptr;
                        break;
                    }
                    else if (saucerPtr && saucerPtr->hitByBullet(**it))
                    {
                        std::cout << "** Saucer hit by bullet" << std::endl;
                        score += 10;  // 10 points for hitting a saucer
                        saucerSound.stop();
                        explosionSound.play();
                        explosion.startExplosion(saucerPtr->getPosition());

                        // remove bullet
                        delete (*it);
                        *it = nullptr;
                        bulletsInFlight.erase(it);

                        // remove the bomb
                        delete saucerPtr;
                        saucerPtr = nullptr;
                        break;
                    }
                    else
                        window.draw(**it);
                }

                // check for explosion
                if (explosion.isExploding())
                {
                    explosion.update();
                    // explosion end
                    if (!explosion.isExploding())
                    {
                        explosionSound.stop();
                        invaderSound.play();

                        // is it a gun explosion
                        if (std::fabs(explosion.getPosition().y - gun[0].getPosition().y) < 20.0f)
                        {
                            if (gunInPlay == 2)
                            {
                                gameOver = true;
                                break;
                            }
                            gun[2-gunInPlay].setInvisible();
                            gun[0].setVisible();
                           // gun[0].moveToStartPosition();
                            gun[0].moveToPosition();
                            gunInPlay++;
                            sf::sleep(sf::Time(sf::seconds(2.0f)));
                        }
                    }
                }
            }
            // Draw guns
            if (gun[0].isVisible())
                window.draw(gun[0].getGun());
            if (gun[2].isVisible())
                window.draw(gun[2].getGun());
            if (gun[1].isVisible())
                window.draw(gun[1].getGun());
            invaders.updateStatus();

            if (bombPtr)
                window.draw(*bombPtr);
            if (saucerPtr)
                window.draw(*saucerPtr);
            if (explosion.isExploding())
                window.draw(explosion.getExplosion());

            invaders.draw(window);
            text.setString(sf::String("Score ")+std::to_string(score)+ std::string(66,' ') +"Lives");
            window.draw(text);
            window.display();
            invaderHit = false;
            loopCount++;
            if (gameOver)
                break;
        }                          // while (gunInPlay < numGuns)
        if (gameOver)
        {
            sf::SoundBuffer applauseBuffer;
            applauseBuffer.loadFromFile("../applause.wav");
            sf::Sound applauseSound;
            applauseSound.setBuffer(applauseBuffer);
            if (!explosion.isExploding())
                // stop sounds
                if (invaderSound.getStatus() == sf::SoundSource::Playing)
                    invaderSound.stop();
            if (saucerSound.getStatus() == sf::SoundSource::Playing)
                saucerSound.stop();
            if (explosionSound.getStatus() == sf::SoundSource::Playing)
                explosionSound.stop();
            applauseSound.play();
            highScores.updateHighScores(Score(name.c_str(),score,time(0)));
            highScores.WriteHighScoresFile();
            sf::sleep(sf::Time(sf::seconds(5.0f)));
            window.close();
        }
    }                              // while (window.isOpen())
    return 0;
}

std::string welcome(sf::RenderWindow& window, const HighScores& highScores, Invaders& invaders)
{
    std::string text, buffer,name;

    // Text
    sf::Font font;
    if (!font.loadFromFile("../CourierNew.ttf"))
    {
        std::cout << "Can't find font" << std::endl;
    }
    text = getWelcomeText();
    sf::Text instructions;
    instructions.setString(text.c_str());
    instructions.setFont(font);
    instructions.setCharacterSize(20); // in pixels, not points!
    instructions.setFillColor(sf::Color::Cyan);
    instructions.setPosition(90.0f,20.0f);

    // Create High Scores text
    sf::Text highScoresText;
    highScoresText.setFont(font);
    highScoresText.setCharacterSize(20); // in pixels, not points!
    highScoresText.setFillColor(sf::Color::Green);
    highScoresText.setPosition(480.0f,210.0f);
    // Write High Scores
    std::ostringstream sout;
    sout << highScores << std::endl;
    highScoresText.setString(sout.str());

    sf::Event evnt;
    char input = ' ';

    // Create and position a gun
    Gun gun;
    gun.moveToPosition(sf::Vector2f(56.0f,264.0f));

    // Position 5 invaders
    for (auto i = 0; i < 5; i++)
    {
        invaders.getInvader(i,0).setPosition(sf::Vector2f(55.0f,313.0f + i * 45.0f));
    }

    // create and position a saucer
    Saucer* saucerPtr = new Saucer;
    saucerPtr->setPosition(sf::Vector2f(50.0f,544.0f));

    // create and position 3 bombs
    Bomb bomb[3] = {0,1,2};
    for (auto i = 0; i < 3; i++)
    {
        bomb[i].setPosition(34.0f+ i*16.0f, 584.0f);
    }

    while (window.isOpen())
    {
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                input = getKey();
                if ((input >= 'a' && input <= 'z')||(input >= 'A' && input <= 'Z')||input == ' ')
                {
                    name += input;
                }
                if (input == '\b') // backspace
                {
                    name = "";
                    text = getWelcomeText();
                }
                break;
            default:
                ;
            }
        }
        window.clear();
        instructions.setString((text+name+'_').c_str());
        window.draw(instructions);
        window.draw(highScoresText);

        window.draw(gun.getGun());

        for (auto i = 0; i < 5; i++)
        {
            window.draw(invaders.getInvader(i,0));
        }
        window.draw(*saucerPtr);
        for (auto i = 0; i < 3; i++)
        {
            window.draw(bomb[i]);
        }

        window.display();
        if (isspace(name[0]))
            name = name.substr(1);  // remove leading space from name
        name[0] = toupper(name[0]);

        if (input == '\n')
        {
            delete saucerPtr;
            return name;
        }
    }
    delete saucerPtr;
    return "";
}

std::string getWelcomeText()
{
    std::ifstream fin("../welcome.txt");
    std::string text, buffer;
    if (!fin)
    {
        std::cout << "Cannot open welcome file." << std::endl;
        return "";
    }

    while (getline(fin, buffer))
    {
        text += buffer += '\n';
    }

    text += "\n          Please type your name and press Enter ===> ";

    fin.close();
    return text;
}

// Determine what key is pressed
char getKey()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        return  'a';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
        return  'b';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
        return  'c';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        return  'd';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        return  'e';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
        return  'f';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
        return  'g';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
        return  'h';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
        return  'i';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
        return  'j';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
        return  'k';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
        return  'l';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
        return  'm';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
        return  'n';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
        return  'o';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        return  'p';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        return  'q';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        return  'r';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        return  's';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
        return  't';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
        return  'u';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
        return  'v';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        return  'w';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        return  'x';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
        return  'y';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        return  'z';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        return  ' ';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        return  '\n';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace))
        return  '\b';
    return ' ';
}

