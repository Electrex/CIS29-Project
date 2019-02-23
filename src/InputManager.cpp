#include "InputManager.hpp"

InputManager::InputManager(Actor& player, sf::Sprite& sprite, sf::View& view, sf::RenderWindow& window) : mPlayer(player), mSprite(sprite), mView(view), mWindow(window), mAngle(0)
{
    kbmActive = true;
    mLastMousePos = sf::Mouse::getPosition(window);

    cAttack = new AttackCommand;
    cThrowWeapon = new ThrowCommand;
    cDropWeapon = new DropCommand;
    cPickup = new PickupCommand;

    initKeys();
    initActions();
}

InputManager::~InputManager()
{
    for (auto& itr : mActionBinding)
        itr.second = nullptr;

    delete cAttack;
    delete cThrowWeapon;
    delete cDropWeapon;
    delete cPickup;
}

//Initialize keys bound to actions
void InputManager::initKeys()
{
    mMouseBinding[sf::Mouse::Left] = Action::Attack;
    mMouseBinding[sf::Mouse::Right] = Action::Pickup;
    mMouseBinding[sf::Mouse::Middle] = Action::Throw;
    mKeyBinding[sf::Keyboard::Space] = Action::Attack;
    mKeyBinding[sf::Keyboard::E] = Action::Throw;
    mKeyBinding[sf::Keyboard::F] = Action::Drop;
    mKeyBinding[sf::Keyboard::Q] = Action::Pickup;
    mJoystickBinding[JoyButtons::Button_X] = Action::Pickup;
    mJoystickBinding[JoyButtons::Button_Y] = Action::Drop;
}

//Initialize binding actions to commands
void InputManager::initActions()
{
	mActionBinding[Action::Attack] = cAttack;
	mActionBinding[Action::Throw] = cThrowWeapon;
	mActionBinding[Action::Drop] = cDropWeapon;
	mActionBinding[Action::Pickup] = cPickup;
}

//Manage Inputs and perform commands
void InputManager::manageInput(const sf::Event& event)
{
    mDeltaTime = mClock.restart();
    mSpritePosition = mView.getSize() / 2.f;

    if(kbmActive || isKBMActive())
    {
        trackMouse(event);
    }

    joystick(event);
    keyboard(event);
    mSprite.setPosition(mView.getCenter());
}

//Track mouse movement and location
void InputManager::trackMouse(const sf::Event& event)
{
    mMouse = sf::Mouse::getPosition(mWindow);
    mAngle = atan2( mMouse.y - mSpritePosition.y , mMouse.x - mSpritePosition.x) * 180 / 3.14;
    mSprite.setRotation(mAngle);

    if (event.type == sf::Event::MouseButtonPressed)
	{
		auto found = mMouseBinding.find(event.mouseButton.button);
		if (found != mMouseBinding.end())
			mActionBinding[found->second]->execute(mPlayer);
	}
}

//Track joystick movements
void InputManager::joystick(const sf::Event& event)
{
    sf::Vector2f movement(sf::Joystick::getAxisPosition(0, sf::Joystick::X), sf::Joystick::getAxisPosition(0, sf::Joystick::Y));
    if(magnitude(movement) < mDeadzone)
        movement = sf::Vector2f(0.f, 0.f);
    else
        kbmDisable();

    mPlayer.move(movement * mDeltaTime.asSeconds() * 10.f);

    movement = sf::Vector2f(sf::Joystick::getAxisPosition(0, sf::Joystick::U), sf::Joystick::getAxisPosition(0, sf::Joystick::V));
    if(magnitude(movement) > mDeadzone)
    {
        kbmDisable();
        mAngle = atan2 (movement.y, movement.x) * 180 / 3.14;
        mSprite.setRotation(mAngle);
    }

    if (event.type == sf::Event::JoystickButtonPressed)
	{
		auto found = mJoystickBinding.find(static_cast<JoyButtons>(event.joystickButton.button));
		if (found != mJoystickBinding.end())
			mActionBinding[found->second]->execute(mPlayer);
	}
}

//Check keyboard movements
void InputManager::keyboard(const sf::Event& event)
{
    sf::Vector2f movement(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        --movement.y;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        ++movement.y;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        --movement.x;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        ++movement.x;
    if (movement.x != 0.f && movement.y != 0.f)
        movement *= 0.707f;
    mPlayer.move(movement * mDeltaTime.asSeconds() * 500.f);

    if (event.type == sf::Event::KeyPressed)
	{
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end())
			mActionBinding[found->second]->execute(mPlayer);
	}
}

//Check if KBM is currently active and if mouse needs to be reactivated
bool InputManager::isKBMActive()
{
    mMouse = sf::Mouse::getPosition(mWindow);

    if(mMouse != mLastMousePos)
    {
        mWindow.setMouseCursorVisible(true);
        kbmActive = true;
        return true;
    }
    else
    {
        return false;
    }
}

//Use squared instead of sqrt for magnitude for less overhead
float InputManager::magnitude(sf::Vector2f value) const
{
    return (value.x * value.x + value.y * value.y);
}

//Disable mouse cursor and tracking
void InputManager::kbmDisable()
{
    if(kbmActive)
    {
        mLastMousePos.x = mMouse.x;
        mLastMousePos.y = mMouse.y;
        kbmActive = false;
        mWindow.setMouseCursorVisible(false);
    }
}
