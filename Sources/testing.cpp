#include "indie.hpp"
#include <irrlicht.h>
#include "Command.hpp"
using namespace irr;

 int main()
 {
    // start up the engine
    std::cout << "???" << std::endl;
    MyEventReceiver command;
    IrrlichtDevice *device = createDevice(video::EDT_OPENGL,
        core::dimension2d<u32>(640,480), 16, false, false, false, &command);

    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* scenemgr = device->getSceneManager();

    device->setWindowCaption(L"Hello World!");

    // add a first person shooter style user controlled camera

    scene::IAnimatedMeshSceneNode *sydney = scenemgr->addAnimatedMeshSceneNode(scenemgr->getMesh("../graphs/sydney.md2"));
    sydney->setMaterialFlag(video::EMF_LIGHTING, false);
    sydney->setMD2Animation(scene::EMAT_STAND);
    sydney->setMaterialTexture(0, driver->getTexture("../graphs/sydney.bmp"));

    SKeyMap keyMap[5];                             // re-assigne les commandes
    keyMap[0].Action = irr::EKA_MOVE_FORWARD;           // avancer
    keyMap[0].KeyCode = irr::KEY_UP;                 // w
    keyMap[1].Action = irr::EKA_MOVE_BACKWARD;          // reculer
    keyMap[1].KeyCode = irr::KEY_DOWN;                 // s
    keyMap[2].Action = irr::EKA_STRAFE_LEFT;            // a gauche
    keyMap[2].KeyCode = irr::KEY_LEFT;                 // a
    keyMap[3].Action = irr::EKA_STRAFE_RIGHT;           // a droite
    keyMap[3].KeyCode = irr::KEY_RIGHT;                 // d
    keyMap[4].Action = irr::EKA_JUMP_UP;                // saut
    keyMap[4].KeyCode = irr::KEY_SPACE;

    scenemgr->addCameraSceneNodeFPS(0, 100.0f, 0.1f, -1, keyMap, 5);

    u32 then = device->getTimer()->getTime();
    const f32 MOVEMENT_SPEED = 10.f;

    // draw everything
    while(device->run() && driver)
    {
        const u32 now = device->getTimer()->getTime();
        const f32 frameDeltaTime = (f32)(now - then) / 1000.f;
        then = now;
        core::vector3df nodePosition = sydney->getPosition();
        if(command.IsKeyDown(KEY_KEY_Z)) {
            nodePosition.X += MOVEMENT_SPEED * frameDeltaTime;
            sydney->setMD2Animation(scene::EMAT_RUN);
        }
        else if(command.IsKeyDown(KEY_KEY_S))
            nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime;

        if(command.IsKeyDown(KEY_KEY_D))
            nodePosition.Z -= MOVEMENT_SPEED * frameDeltaTime;
        else if(command.IsKeyDown(KEY_KEY_Q))
            nodePosition.Z += MOVEMENT_SPEED * frameDeltaTime;
        sydney->setPosition(nodePosition);
        driver->beginScene(true, true, video::SColor(255,0,0,255));
        scenemgr->drawAll();
        driver->endScene();
    }

    // delete device
    device->drop();
    return 0;
 }