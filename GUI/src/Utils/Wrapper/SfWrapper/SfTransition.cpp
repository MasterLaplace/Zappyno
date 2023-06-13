/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** sfTransition
*/

#include "../../../../includes/SfTransition.hpp"

namespace Sf_transition {
    template<typename T, typename U, typename V>
    inline U map(T value, T start1, T end1, U start2, U end2) {
        return start2 + (end2 - start2) * ((value - start1) / (end1 - start1));
    }

    Star::Star() {
        _x = RANDINT(-WIN_X / 2, WIN_X / 2);
        _y = RANDINT(-WIN_Y / 2, WIN_Y / 2);
        _z = RANDINT(0, WIN_X);
        _pz = _z;
    }

    void Star::update(int speed) {
        _z -= speed;
        if (_z < 1) {
            _x = RANDINT(-WIN_X / 2, WIN_X / 2);
            _y = RANDINT(-WIN_Y / 2, WIN_Y / 2);
            _z = WIN_X;
            _pz = _z;
        }
    }

    void Star::show(sf::RenderWindow &_window) {
        float sx = map<float, float, float>(_x / _z, 0.0, 1.0, 0.0, WIN_X);
        float sy = map<float, float, float>(_y / _z, 0.0, 1.0, 0.0, WIN_Y);

        float _px = map<float, float, float>(_x / _pz, 0.0, 1.0, 0.0, WIN_X);
        float _py = map<float, float, float>(_y / _pz, 0.0, 1.0, 0.0, WIN_Y);

        _pz = _z;

        Sf_primitive::Line_s line(sf::Vector2f(_px + (WIN_X / 2), _py + (WIN_Y / 2)), sf::Vector2f(sx + (WIN_X / 2), sy + (WIN_Y / 2)));
        Sf_primitive::drawLine(_window, line);
    }


    Transition::Transition(Transition::TransitionType type, int timeout) : _type(type), _timeout(timeout) {
        switch (type) {
            case Transition::STARFIELD:
                _stars = new Star[400];
                for (int i = 0; i < 400; i++) {
                    _stars[i] = Star();
                }
                break;
            default:
                break;
        }
        _start = std::chrono::high_resolution_clock::now();
    }
    Transition::~Transition() {
        switch (_type) {
            case Transition::STARFIELD:
                delete[] _stars;
                break;
            default:
                break;
        }
    }

    bool Transition::isFinished() {
        auto _now = std::chrono::high_resolution_clock::now();
        auto _elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(_now - _start).count();

        if (_elapsed >= _timeout)
            return true;
        return false;
    }

    void Transition::reset(Transition::TransitionType type, int timeout) {
        _type = type;
        _timeout = timeout;
        _start = std::chrono::high_resolution_clock::now();
    }

    void Transition::DoTransition(sf::RenderWindow &_window) {
        auto _now = std::chrono::high_resolution_clock::now();
        auto _elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(_now - _start).count();
        auto timeRemaining = _timeout - _elapsed;
        auto limit_to_dicrease = _timeout - ( 30 * _timeout / 100 );
        int speed = 50;
        int decelerationFactor = 100;

        if (_elapsed > limit_to_dicrease) { // decelerate the speed
            speed = speed * decelerationFactor / timeRemaining;
        }

        switch (_type) {
            case Transition::STARFIELD:
                for (int i = 0; i < 400; i++) {
                    _stars[i].update(speed);
                    _stars[i].show(_window);
                }
                break;
            default:
                break;
        }
    }
}
