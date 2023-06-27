/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** Core
*/

#include "../../includes/Core.hpp"
#include "../../includes/SfSprite.hpp"
#include <algorithm>
#include <list>

Core::Core(const unsigned ac, const char *av[])
{
    if (ac == 2 && (std::string(av[1]) == "-h" || std::string(av[1]) == "-help")) {
        this->showUsage(std::cout);
        return;
    }
    if (!this->parseArgs(ac, av))
        throw std::invalid_argument("Core: Invalid arguments, run with -h or -help for more informations");
    auto client = std::make_shared<Manager::Client>(std::string(av[4]), std::stoi(av[2]));
    _window = std::make_shared<sf::RenderWindow>();
    _protocol = std::make_shared<Manager::Protocol>(_window, client);
    _window->create(sf::VideoMode(WIN_X, WIN_Y), "GUI", sf::Style::Default);
    _window->setFramerateLimit(client->getFramerate());
    _window->setVerticalSyncEnabled(true);

    /* LOAD SCENES */
    _scene = _sceneManager.create_scene<sf::RenderWindow, Sf_sprite::SfSprite>(Scene_Manager::SceneType::MENU, _window);

    /* RUN */
    this->run();
}

void Core::run()
{
    std::cout << "Core: Running..." << std::endl;

    // // SOUTH
    // Engine::Triangle tri(Math::Vector(0.0f, 0.0f, 0.0f), Math::Vector(0.0f, 1.0f, 0.0f), Math::Vector(1.0f, 1.0f, 0.0f));
    // cube.add(std::make_shared<Engine::Triangle>(tri));
    // auto tri2 = Engine::Triangle(Math::Vector(0.0f, 0.0f, 0.0f), Math::Vector(1.0f, 1.0f, 0.0f), Math::Vector(1.0f, 0.0f, 0.0f));
    // cube.add(std::make_shared<Engine::Triangle>(tri2));
    // // EAST
    // auto tri3 = Engine::Triangle(Math::Vector(1.0f, 0.0f, 0.0f), Math::Vector(1.0f, 1.0f, 0.0f), Math::Vector(1.0f, 1.0f, 1.0f));
    // cube.add(std::make_shared<Engine::Triangle>(tri3));
    // auto tri4 = Engine::Triangle(Math::Vector(1.0f, 0.0f, 0.0f), Math::Vector(1.0f, 1.0f, 1.0f), Math::Vector(1.0f, 0.0f, 1.0f));
    // cube.add(std::make_shared<Engine::Triangle>(tri4));
    // // NORTH
    // auto tri5 = Engine::Triangle(Math::Vector(1.0f, 0.0f, 1.0f), Math::Vector(1.0f, 1.0f, 1.0f), Math::Vector(0.0f, 1.0f, 1.0f));
    // cube.add(std::make_shared<Engine::Triangle>(tri5));
    // auto tri6 = Engine::Triangle(Math::Vector(1.0f, 0.0f, 1.0f), Math::Vector(0.0f, 1.0f, 1.0f), Math::Vector(0.0f, 0.0f, 1.0f));
    // cube.add(std::make_shared<Engine::Triangle>(tri6));
    // // WEST
    // auto tri7 = Engine::Triangle(Math::Vector(0.0f, 0.0f, 1.0f), Math::Vector(0.0f, 1.0f, 1.0f), Math::Vector(0.0f, 1.0f, 0.0f));
    // cube.add(std::make_shared<Engine::Triangle>(tri7));
    // auto tri8 = Engine::Triangle(Math::Vector(0.0f, 0.0f, 1.0f), Math::Vector(0.0f, 1.0f, 0.0f), Math::Vector(0.0f, 0.0f, 0.0f));
    // cube.add(std::make_shared<Engine::Triangle>(tri8));
    // // TOP
    // auto tri9 = Engine::Triangle(Math::Vector(0.0f, 1.0f, 0.0f), Math::Vector(0.0f, 1.0f, 1.0f), Math::Vector(1.0f, 1.0f, 1.0f));
    // cube.add(std::make_shared<Engine::Triangle>(tri9));
    // auto tri10 = Engine::Triangle(Math::Vector(0.0f, 1.0f, 0.0f), Math::Vector(1.0f, 1.0f, 1.0f), Math::Vector(1.0f, 1.0f, 0.0f));
    // cube.add(std::make_shared<Engine::Triangle>(tri10));
    // // BOTTOM
    // auto tri11 = Engine::Triangle(Math::Vector(1.0f, 0.0f, 1.0f), Math::Vector(0.0f, 0.0f, 1.0f), Math::Vector(0.0f, 0.0f, 0.0f));
    // cube.add(std::make_shared<Engine::Triangle>(tri11));
    // auto tri12 = Engine::Triangle(Math::Vector(1.0f, 0.0f, 1.0f), Math::Vector(0.0f, 0.0f, 0.0f), Math::Vector(1.0f, 0.0f, 0.0f));
    // cube.add(std::make_shared<Engine::Triangle>(tri12));

    // auto teapot = Parser::Obj::loadFile("teapot.obj");
    // std::cout << "Teapot loaded: " << teapot.getShapes().size() << std::endl;

    // Triangle to Raster (T2R)
    // Engine::Mesh cucu;
    std::chrono::steady_clock::time_point clockProtocol;
    std::chrono::seconds interval(1); // intervalle de 1 seconde
    sf::Event event;
    std::string message;

    while (_window->isOpen()) {

        try {
            if (_scene->getSceneType() == Scene_Manager::SceneType::GAME) {
                if ((message = _protocol->_client->receiveFromServer()) != "") {
                    // std::cout << "Message received: " << message;
                    _protocol->parseCommand(message);
                }
                if (std::chrono::steady_clock::now() - clockProtocol >= interval) {
                    _protocol->_client->sendToServer("mct\n");
                    auto MapSize = _protocol->getMapSize();
                    for (int j = 0; j < int(MapSize.y()); j++) {
                        for (int i = 0; i < int(MapSize.x()); i++)
                            _protocol->sendTileToServer(i, j);
                    }
                    clockProtocol = std::chrono::steady_clock::now();
                }
            }
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window->close();
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::F1) {
                    auto &now = _sceneManager.getMusic();
                    if (now.getStatus() == sf::Music::Status::Paused)
                        now.play();
                    else
                        now.pause();
                }
            }
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0) {
                    _protocol->setScaleTile(_protocol->getScaleTile() + 0.1f);
                    _protocol->updatePosition();
                } else if (event.mouseWheelScroll.delta < 0) {
                    _protocol->setScaleTile(_protocol->getScaleTile() - 0.1f);
                    _protocol->updatePosition();
                }
            }
        }
            // Math::Vector vForward = camera.getForward(0.1);
            // switch (event.key.code) {
                // in AZERTY
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            _protocol->move_map({0, 5});
                //     camera.moveForward(0.1f);
                //     // break;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            _protocol->move_map({0, -5});
                //     camera.moveForward(-0.1f);
                //     // break;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            _protocol->move_map({5, 0});
                //     camera.moveRight(vForward)
                //     // break;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            _protocol->move_map({-5, 0});
                //     camera.moveRight(-vForward);
                //     // break;
                // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                //     camera.moveUp(0.1f);
                //     // break;
                // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                //     camera.moveUp(-0.1f);
                    // break;
                // case sf::Keyboard::Left:
                //     camera.rotateY(-0.1f);
                    // break;
                // case sf::Keyboard::Right:
                //     camera.rotateY(0.1f);
                    // break;
            // }
        if (_scene->getSceneType() != Scene_Manager::GAME && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            _window->close();
            break;
        }

        _window->clear();

        // get the mouse position in the window
        sf::Vector2i pixelPos = sf::Mouse::getPosition(*_window);
        Math::Vector mousePos = {double(pixelPos.x), double(pixelPos.y)};

        try {
            if (event.type == sf::Event::KeyReleased) {
                _scene->updateScene(mousePos, event.key.code, sf::Mouse::isButtonPressed(sf::Mouse::Left));
            } else {
                _scene->updateScene(mousePos, sf::Mouse::isButtonPressed(sf::Mouse::Left));
            }
            if (_scene->getSceneType() == Scene_Manager::SceneType::GAME) {
                _protocol->updateProtocol(mousePos, sf::Mouse::isButtonPressed(sf::Mouse::Left));
                _protocol->animationProtocol();
            }
            _sceneManager.switchScene<sf::RenderWindow, Sf_sprite::SfSprite>(_window, _scene, _protocol);
            if (!_window->isOpen())
                break;
            _scene->drawScene<sf::RenderWindow, Sf_primitive::Triangle_s>(_window, _protocol);

            if (!star.isFinished() && _scene->getSceneType() == Scene_Manager::SceneType::MENU)
                star.DoTransition(*_window);
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        _window->display();
    }
    // // Set up "World Tranmsform" though not updating theta
    // // makes this a bit redundant
    // Math::Matrix matRotZ, matRotX;
    // float fTheta = 1.0f * _clock.getElapsedTime().asSeconds(); // Uncomment to spin me right round baby right round
    // matRotZ.SetRotateZMatrix(fTheta * 0.5f);
    // matRotX.SetRotateXMatrix(fTheta);

    // Math::Matrix matTrans;
    // matTrans.SetTranslateMatrix(0.0f, 0.0f, 5.0f);

    // Math::Matrix matWorld; // Form World Matrix
    // matWorld.Multiply(matRotZ, matRotX); // Transform by rotation
    // matWorld.Multiply(matWorld, matTrans); // Transform by translation

    // // Create "Point At" Matrix for camera
    // Math::Vector vUp = { 0, 1 };
    // Math::Vector vTarget = { 0, 0, 1 };
    // Math::Matrix matCameraRot;
    // matCameraRot.SetRotateYMatrix(camera.getFawY());
    // matCameraRot.MultiplyVector(camera.getDir(), vTarget);
    // Math::Matrix matCamera;
    // vTarget = (camera.getPos() + camera.getDir());
    // matCamera.SetViewMatrix(camera.getPos(), vTarget, vUp);

    // // Make view matrix from camera
    // Math::Matrix matView = matCamera.QuickInverse();

    // // Store triagles for rastering later
    // std::vector<Engine::Triangle> vecTrianglesToRaster;

    // // Draw Triangles
    // for (auto tri : teapot.getShapes())
    // {
    //     Engine::Triangle triProjected, triTransformed, triViewed;

    //     // World Matrix Transform
    //     matWorld.MultiplyVector(triTransformed[0], tri->operator[](0));
    //     matWorld.MultiplyVector(triTransformed[1], tri->operator[](1));
    //     matWorld.MultiplyVector(triTransformed[2], tri->operator[](2));

    //     // Calculate triangle Normal
    //     Math::Vector normal, line1, line2;

    //     // Get lines either side of triangle
    //     line1 = (triTransformed[1] - triTransformed[0]);
    //     line2 = (triTransformed[2] - triTransformed[0]);

    //     // Take cross product of lines to get normal to triangle surface
    //     normal = Math::cross(line1, line2);

    //     // You normally need to normalise a normal!
    //     normal.normalise();

    //     // Get Ray from triangle to camera
    //     Math::Vector vCameraRay = (triTransformed[0] - camera.getPos());

    //     // If ray is aligned with normal, then triangle is visible
    //     if (Math::dot(normal, vCameraRay) >= 0.0f)
    //         continue;
    //     // Illumination
    //     Math::Vector light_direction = { 0.0f, 1.0f, -1.0f };
    //     light_direction.normalise();

    //     // How "aligned" are light direction and triangle surface normal ?
    //     triTransformed.SetDp(fmax(0.1f, Math::dot(light_direction, normal)));

    //     // Convert World Space --> View Space
    //     matView.MultiplyVector(triViewed[0], triTransformed[0]);
    //     matView.MultiplyVector(triViewed[1], triTransformed[1]);
    //     matView.MultiplyVector(triViewed[2], triTransformed[2]);
    //     triViewed.SetDp(triTransformed.GetDp());

    //     // Clip Viewed Triangle against near plane, this could form two additional
    //     // additional triangles.
    //     unsigned nClippedTriangles = 0;
    //     Engine::Triangle clipped[2];
    //     nClippedTriangles = triViewed.ClipAgainstPlane({ 0.0f, 0.0f, 0.1f }, { 0.0f, 0.0f, 1.0f }, clipped[0], clipped[1]);

    //     // We may end up with multiple triangles form the clip, so project as
    //     // required
    //     for (unsigned n = 0; n < nClippedTriangles; n++)
    //     {
    //         // Project triangles from 3D --> 2D
    //         ViewtoProjection.MultiplyVector(triProjected[0], clipped[n][0]);
    //         ViewtoProjection.MultiplyVector(triProjected[1], clipped[n][1]);
    //         ViewtoProjection.MultiplyVector(triProjected[2], clipped[n][2]);
    //         triProjected.SetDp(clipped[n].GetDp());

    //         // Scale into view, we moved the normalising into cartesian space
    //         // out of the matrix.vector function from the previous videos, so
    //         // do this manually
    //         triProjected[0] = (triProjected[0] / triProjected[0].w());
    //         triProjected[1] = (triProjected[1] / triProjected[1].w());
    //         triProjected[2] = (triProjected[2] / triProjected[2].w());

    //         // X/Y are inverted so put them back {-1.0f, -1.0f, 1.0f}
    //         triProjected[0].x(triProjected[0].x() * -1.0f);
    //         triProjected[1].x(triProjected[1].x() * -1.0f);
    //         triProjected[2].x(triProjected[2].x() * -1.0f);
    //         triProjected[0].y(triProjected[0].y() * -1.0f);
    //         triProjected[1].y(triProjected[1].y() * -1.0f);
    //         triProjected[2].y(triProjected[2].y() * -1.0f);

    //         // Offset verts into visible normalised space
    //         Math::Vector vOffsetView = { 1,1,0 };

    //         triProjected[0] = (triProjected[0] + vOffsetView);
    //         triProjected[1] = (triProjected[1] + vOffsetView);
    //         triProjected[2] = (triProjected[2] + vOffsetView);
    //         triProjected[0].x(triProjected[0].x() * (0.5f * float(WIN_X)));
    //         triProjected[0].y(triProjected[0].y() * (0.5f * float(WIN_Y)));
    //         triProjected[1].x(triProjected[1].x() * (0.5f * float(WIN_X)));
    //         triProjected[1].y(triProjected[1].y() * (0.5f * float(WIN_Y)));
    //         triProjected[2].x(triProjected[2].x() * (0.5f * float(WIN_X)));
    //         triProjected[2].y(triProjected[2].y() * (0.5f * float(WIN_Y)));

    //         // Store triangle for sorting
    //         vecTrianglesToRaster.push_back(triProjected);
    //     }
    // }

    // // Sort triangles from back to front
    // sort(vecTrianglesToRaster.begin(), vecTrianglesToRaster.end(), [](Engine::Triangle &t1, Engine::Triangle &t2)
    // {
    //     float z1 = (t1[0].z() + t1[1].z() + t1[2].z()) / 3.0f;
    //     float z2 = (t2[0].z() + t2[1].z() + t2[2].z()) / 3.0f;
    //     return z1 > z2;
    // });

    // // Clear Screen
    // // _window->clear();

    // // Loop through all transformed, viewed, projected, and sorted triangles
    // for (auto &triToRaster : vecTrianglesToRaster)
    // {
    //     // Clip triangles against all four screen edges, this could yield
    //     // a bunch of triangles, so create a queue that we traverse to
    //     //  ensure we only test new triangles generated against planes
    //     Engine::Triangle clipped[2];
    //     std::list<Engine::Triangle> listTriangles;

    //     // Add initial triangle
    //     listTriangles.push_back(triToRaster);
    //     unsigned nNewTriangles = 1;

    //     for (unsigned p = 0; p < 4; p++)
    //     {
    //         unsigned nTrisToAdd = 0;
    //         while (nNewTriangles > 0)
    //         {
    //             // Take triangle from front of queue
    //             Engine::Triangle test = listTriangles.front();
    //             listTriangles.pop_front();
    //             nNewTriangles--;

    //             // Clip it against a plane. We only need to test each
    //             // subsequent plane, against subsequent new triangles
    //             // as all triangles after a plane clip are guaranteed
    //             // to lie on the inside of the plane. I like how this
    //             // comment is almost completely and utterly justified
    //             switch (p)
    //             {
    //             case 0:	nTrisToAdd = test.ClipAgainstPlane({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, clipped[0], clipped[1]); break;
    //             case 1:	nTrisToAdd = test.ClipAgainstPlane({ 0.0f, float(WIN_Y) - 1, 0.0f }, { 0.0f, -1.0f, 0.0f }, clipped[0], clipped[1]); break;
    //             case 2:	nTrisToAdd = test.ClipAgainstPlane({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, clipped[0], clipped[1]); break;
    //             case 3:	nTrisToAdd = test.ClipAgainstPlane({ float(WIN_X) - 1, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, clipped[0], clipped[1]); break;
    //             }

    //             // Clipping may yield a variable number of triangles, so
    //             // add these new ones to the back of the queue for subsequent
    //             // clipping against next planes
    //             for (unsigned w = 0; w < nTrisToAdd; w++)
    //                 listTriangles.push_back(clipped[w]);
    //         }
    //         nNewTriangles = listTriangles.size();
    //     }


    //     // Draw the transformed, viewed, clipped, projected, sorted, clipped triangles
    //     for (auto &t : listTriangles)
    //     {
    //         Sf_primitive::Triangle_s triangle(t);
    //         t.drawTriangle<sf::RenderWindow, Sf_primitive::Triangle_s>(Sf_primitive::drawTriangleNotFill, *_window, triangle);
    //     }
    // }
    // _window->display();
    // }
}

void Core::showUsage(std::ostream &output)
{
    output << "Usage: ./zappy_ai -p port -h machine" << std::endl;
    output << "\tport\tis the port number" << std::endl;
    output << "\tmachine\tis the name of the machine; localhost by default" << std::endl;
}

bool Core::parseArgs(const unsigned ac, const char *av[])
{
    auto port = 0;
    auto machine = "localhost";
    (void) machine;

    if (ac < 3)
        return showUsage(std::cerr), false;
    try {
        if (std::string(av[1]) != "-p")
            throw std::invalid_argument("Error: args<" + std::string(av[1]) + "> is invalid, read the usage. (" + __FILE__ + ":" + std::to_string(__LINE__) + ")");
        port = atoi(av[2]);
        if (port > MAX_PORT || port < MIN_PORT)
            throw std::invalid_argument("Error: args<" + std::to_string(port) + "> is invalid, read the usage. (" + __FILE__ + ":" + std::to_string(__LINE__) + ")");
        if (ac == 5) {
            if (std::string(av[3]) != "-h")
                throw std::invalid_argument("Error: args<" + std::string(av[3]) + "> is invalid, read the usage. (" + __FILE__ + ":" + std::to_string(__LINE__) + ")");
            machine = av[4];
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return showUsage(std::cerr), false;
    }

    /* RUN */
    return true;
}
