/*
    This is a simple messagebus. It can be used to send messages and objects from any part of the system
    and capture this messages in any other part of program.


    Originally written by: Rafael Tonello (tonello.rafinha@gmail.com)



*/

#ifndef MESSAGEBUS_H
#define MESSAGEBUS_H

#include <functional>
#include <vector>
#include "Libs/KwWebServer/Cpp/ThreadPool.h"

namespace Shared{
    using namespace std;
	class __MessageItem{
		public:
			function<void(string, void*params)> event;

	};

	class MessageBus{
		private:
            vector<__MessageItem*> observers;
		public:
            MessageBus(){

            }

			void observate(function<void(string, void* params)> onNewMessage)
			{
                __MessageItem *messageItem = new __MessageItem();
                messageItem->event =onNewMessage;

                this->observers.push_back(messageItem);
			}

			void message(string title, void* params)
			{
                for (auto &curr: this->observers)
                {
                    curr->event(title, params);
                }
			}

			static MessageBus def;
	};

	//MessageBus *dmb = &MessageBus::def;
}

#endif // MESSAGEBUS_H
