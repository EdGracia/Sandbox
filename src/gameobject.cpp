#include "gameObject.h"

GameObject::GameObject(Vector3 p, Vector3 s, Vector3 r)
    : position(p),
      size(s),
      rotation(r) {}

Vector3 GameObject::getPosition() { return position; }
Vector3 GameObject::getSize() { return size; }
Vector3 GameObject::getRotation() { return rotation; }
void GameObject::setPosition(Vector3 p) { position = p; }
void GameObject::setSize(Vector3 s) { size = s; }
void GameObject::setRotation(Vector3 r) { rotation = r; }
