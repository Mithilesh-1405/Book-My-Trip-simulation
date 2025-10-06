# Travel-app-simulation

Book My Trip Simulation
=======================

Problem Statement
-----------------

Travel booking apps like _Make My Trip_ allow users to search, select, and book transportation tickets efficiently. The challenge is to simulate the key functionalities of such an app in a C++ project, while applying core Object-Oriented Programming (OOP) concepts. The app should allow users to register, log in, view available travel options (bus, train, flight), and book tickets from various sources to destinations, providing a realistic simulation of the booking experience.

Solution
--------

The project is a C++ simulation of a travel booking application. The app follows this flow:

1.  **User Interaction**
    
    *   Users can download the app (instantiate the MakeMyTrip class), register with details (name, age, phone number, Aadhar number, password), log in, and log out.
        
    *   Once logged in, users can view all available transportation options, search by source and destination, and book tickets.
        
2.  **Core Classes**The application consists of 8 main classes:
    
    *   UserLogin – Handles user authentication.
        
    *   Registration – Inherits UserLogin to register new users.
        
    *   Transportation – Abstract class defining standard interface for all transport modes.
        
    *   Bus, Train, Flight – Subclasses of Transportation, overriding methods to display transportation-specific details.
        
    *   City – Contains city details and manages transportation options.
        
    *   MakeMyTrip – Main class controlling app flow and serving as the home page.
        
3.  **Functionality Overview**
    
    *   Users can view all available tickets or filter by transportation mode.
        
    *   Tickets contain details like source, destination, cost, duration, date, and a unique identifier.
        
    *   Users can book tickets and view their bookings later.
        
    *   Cities and travel routes are pre-defined in the system for realistic simulation.
        
4.  **OOP Concepts Implemented**
    
    *   **Inheritance:** Registration inherits from UserLogin; Bus, Train, Flight inherit from Transportation.
        
    *   **Polymorphism:** Subclasses override getDetails() from Transportation.
        
    *   **Abstraction:** Transportation defines an abstract interface, implemented by subclasses.
        
    *   **Encapsulation:** User credentials in UserLogin are protected, with public methods to access them safely.
        

Technologies Used
-----------------

*   **Language:** C++
    
*   **Concepts:** Object-Oriented Programming (Inheritance, Polymorphism, Abstraction, Encapsulation)
    
*   **Development Tools:** Any standard C++ compiler
