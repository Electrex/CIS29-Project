/*
    InputManager class to handle inputs, linking inputs to actions, and linking actions to commands.
    Updates the sprite and view based on inputs.
    Automatically enables and disables depending on if joystick is active or mouse is active.

    Created By: Dale Armstrong
*/
#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP
#include <SFML/Graphics.hpp>
#include "Actor.hpp"
#include "Command.hpp"
#include "AttackCommand.hpp"
#include "DropCommand.hpp"
#include "PickupCommand.hpp"
#include "ThrowCommand.hpp"

namespace PlayerAction
{
    enum ID
    {
        Attack,
        Throw,
        Drop,
        Pickup
    };
}

namespace JoyButtons
{
    enum ID
    {
        Button_A,
        Button_B,
        Button_X,
        Button_Y,
        RightBumper,
        LeftBumper,
        LeftThumbStickClick,
        RightThumbStickClick,
        Start,
        Back,
        XboxButton,
        DpadUp,
        DpadDown,
        DpadLeft,
        DpadRight
    };
}
class InputManager
{
    public:
        InputManager(Actor& player, sf::Sprite& sprite, sf::View& view, sf::RenderWindow& window);
        ~InputManager();

        typedef PlayerAction::ID Action;
        typedef JoyButtons::ID JoyButtons;

        void manageInput(const sf::Event& event);     //Check inputs and perform related commands
        float getAngle() const { return mAngle; } //Returns direction that the player is facing

    private:
        void initKeys();    //Initialize keys bound to action
        void initActions(); //Initialize actions bound to commands
        void trackMouse(const sf::Event& event);  //find angle and rotate character
        void joystick(const sf::Event& event);    //Check joystick movement
        void keyboard(const sf::Event& event);    //Check keyboard movement
        float magnitude(sf::Vector2f value) const;  //Squared function to adjust for deadzone
        bool isKBMActive(); //Check if the mouse was moved to now follow mouse instead of joystick
        void kbmDisable();  //Disable mouse and remember last position to allow the use of joystick

        Actor& mPlayer;
        sf::Sprite& mSprite;
        sf::View& mView;
        sf::RenderWindow& mWindow;
        sf::Time mDeltaTime;
        sf::Vector2i mMouse;
        sf::Vector2i mLastMousePos;
        sf::Clock mClock;
        sf::Vector2f mSpritePosition;
        sf::Vector2f movement;

        bool kbmActive;
        float mAngle;
        const float mDeadzone = 5000.0f; //Adjust deadzone of joystick

        Command* cAttack;
        Command* cThrowWeapon;
        Command* cPickup;
        Command* cDropWeapon;

        std::map<sf::Keyboard::Key, Action> mKeyBinding;    //map keyboard keys to an action
        std::map<sf::Mouse::Button, Action> mMouseBinding;  //map mouse keys to an action
        std::map<JoyButtons, Action> mJoystickBinding;      //map joystick buttons to an action
        std::map<Action, Command*> mActionBinding;          //map action to a command
};

#endif // INPUTMANAGER_HPP
