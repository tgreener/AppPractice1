Practice at building an application layer for a game. May actually become a game at some point.

The purpose is to implement features that any game would need and some additional things just to practice doing them. Here's a list:

Necessary Things:

1) Application Run Loop - I accomplish this by registering timed notifications with the OS. The run loop waits on these events, and so the program is basically a giant event pump.

2) Communication Services - I'm implementing a messaging and event handling service in order to facilitate communications between game systems.

3) Service Locator - This practice app uses a service locator to determine the visibility and lifespan of various services.


Extra Things:

1) Support for multithreaded applications. I have been trying to build all services with multithreaded behavior in mind. This has been the most unfamiliar ground for me to cover.
