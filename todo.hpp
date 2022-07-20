#pragma once

//TODO
    //mouse release anywhere, or entering a menu, stops shooting
        //this has been added, but:
            //CONFIRM THIS WHEN UI IS ADDED
            //input handling in general needs to be refactored, it's a goddamn mess.

    //class Collision
        //add 'bool player' to Projectile class
        //pass refs to Projectile_Manager, Enemy_Manager, Player, and World
            //for all projectiles: check against World::walls
            //for player projectiles: check against Enemy_Manager
            //for non-player projectiles: check against Player

        //check between projectiles and enemies/walls
            //delete projectile when it hits something, and then damage the appropriate enemy if so
            //bool player in Projectile?

        //move Game::getPlayerCollideMap() to World and genericize it for projectile checking

        //there was a segfault once :/

    //weapon handling and stats are still hardcoded.
    //melee weapons dont exist yet
