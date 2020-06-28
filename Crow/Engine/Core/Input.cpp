//
// Created by Igli milaqi on 01/04/2020.
//

#include "Input.h"
#include "../Rendering/Window.h"
#include "GLFW/glfw3.h"

int Input::InternalGetKey(int key)
{
   return glfwGetKey(window->m_internalWindow,key);
}


bool Input::InternalGetKeyUp(int key)
{
   auto keyIterator = Input::m_keyMap.find(key);

   if(keyIterator == Input::m_keyMap.end())
   {
      return false;
   }
   else
   {
      if(keyIterator->second == KeyState::RELEASED)
      {
         m_keyMap.erase(keyIterator);
         return true;
      }
      else return false;
   }
}



bool Input::InternalGetKeyDown(int key)
{
   auto keyIterator = Input::m_keyMap.find(key);

   if(keyIterator == Input::m_keyMap.end()) return false;

   else
   {
      if(keyIterator->second == KeyState::PRESSED)
      {
         keyIterator->second = KeyState::ACTIVE;
         return true;
      }
      else return false;
   }
}

bool Input::GetKey(int key)
{
   int state = instance->InternalGetKey(key);
   return state == (GLFW_PRESS);
}

bool Input::GetKeyDown(int key)
{
   return instance->InternalGetKeyDown(key);
}

bool Input::GetKeyUp(int key)
{
   return instance->InternalGetKeyUp(key);
}
