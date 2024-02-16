#include <iostream>


#include "games.h"

#include "Memory.h"

#include "WallBreaker.h"
#include "Flappy.h"

#include "Particle.h"

#include "Spirograph.h"
#include "MsPacman.h"
#include "Snake.h"

using namespace std;


void cpp();


int main()
{

    Snake snake;
    snake.Main();



   // cpp();

    Spirograph spiro;
    //spiro.Main();

    Flappy flappy;
    // flappy.Main();


    MsPacman msPacman;
    // msPacman.Main();


    WallBreaker wallBreaker;
    //wallBreaker.Main();


    // bouncingBall_012();


    // make an instance of Memory class
    Particle particles;
    //particles.Main();


    Memory memory;
    // memory.Main();

    //ui_button_011();
    //collisions_008();

    //triangle_corners_007();

    //draw_polygone_006();

    //mouse_drag_005();

    //draw_image_004();

    //inputs_003();

    //drawing_002();

    //ball_001();

    //simple_draw_000();

    //test_000();


    return 0;

}



struct Person
{
    string name;
};

void cpp()
{
/*
    Person* person1 = new Person();

    person1->name = "Amir";

    Person person2;
    person2.name = "Steve";




    string food = "Pizza"; // A food variable of type string

    cout << food << endl;  // Outputs the value of food (Pizza)
    cout << &food << endl; // Outputs the memory address of food (0x6dfed4)



    string* ptr = &food;    // A pointer variable, with the name ptr, that stores the address of food

    // Output the value of food (Pizza)
    cout << food << "\n";

    // Output the memory address of food (0x6dfed4)
    cout << &food << "\n";

    // Output the memory address of food with the pointer (0x6dfed4)
    cout << ptr << "\n";

    */

    // Auto
    std::vector<Person> vec;

    Person a, b, c;

    for (auto& person : vec)
    {
        person.name = "test";
    }

    // To verify the change
    for (const auto& person : vec)
    {
        cout << person.name << endl;
    }
}