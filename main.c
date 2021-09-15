/**
 * Title: StarCombat galactic force
 * Author: Jujube
 * Version: 0.1.0
 * Cophright: Jujube@2021
 */

//includes
#include <gb/gb.h>
#include <stdio.h>
#include <ctype.h>
#include <rand.h>
#include <gb/console.h>
#include <gb/drawing.h>

//imports
#include "../projects/StarCombat/Characters/flight.c"
#include "../projects/StarCombat/Characters/enemigo.c"

#include "../projects/StarCombat/Libreries/collisions.h"
#include "../projects/StarCombat/Libreries/backgrounds.h"

//backgrounds
#include "../projects/StarCombat/BackGrounds/startScreen.c"
#include "../projects/StarCombat/BackGrounds/firstLevelBackground.c"
#include "../projects/StarCombat/BackGrounds/jujube.c"

void init();
void firstLevel();
void checkInput();
void updateSwitches();

// The player
// array will hold the player's position as X ([0]) and Y ([1])
int player[2];
int enemy[2];

void main() {

	init();
	
	while(1) {
		
		checkInput();				// Check for user input (and act on it)
		updateSwitches();			// Make sure the SHOW_SPRITES and SHOW_BKG switches are on each loop
		wait_vbl_done();			// Wait until VBLANK to avoid corrupting memory
	}
	
}

void init() {
	
	DISPLAY_ON;						// Turn on the display
	plot_intro_image(jujube_tile_data,jujube_map_data);
	plot_background_image(startScreen_tile_data,startScreen_map_data);
	
}

void firstLevel(){
	plot_intro_image(firstLevelBackground_tile_data,firstLevelBackground_map_data);

	// Load the the 'sprites' tiles into sprite memory
	set_sprite_data(0, 2, flight);
	
	// Set the first movable sprite (0) to be the first tile in the sprite memory (0)
	set_sprite_tile(0,0);

	player[0] = 80;
	player[1] = 72;


	// enemy
	//set_sprite_data(2, 4, enemyTile);
	//set_sprite_tile(3,4);

	enemy[0] = 100;
	enemy[1] = 92;
}

void updateSwitches() {
	
	HIDE_WIN;
	SHOW_SPRITES;
	SHOW_BKG;
	
}

void checkInput() {
	

	// START
    if (joypad() & J_START) {
		firstLevel();
    }

	// B
    if (joypad() & J_B) {
	
    }
	
	// UP
	if (joypad() & J_UP) {
		if(player[1]>19){
			player[1]--;
		}
	}

	// DOWN
	if (joypad() & J_DOWN ) {
		if(player[1]<150){
			player[1]++;
		}
	}

	// LEFT
	if (joypad() & J_LEFT) {
		if(player[0]>9){
			player[0]--;
		}
	}	
	
	// RIGHT
	if (joypad() & J_RIGHT) {
		if(player[0]<160){
			player[0]++;
		}
	}
	
	// Move the sprite in the first movable sprite list (0)
	//  the the position of X (player[0]) and y (player[1])
	move_sprite(0, player[0], player[1]);
	move_sprite(1, enemy[0], enemy[1]);

	if(collisionCheck(player[0], player[1], 8, 8, enemy[0], enemy[1], 8, 8) == 1) {
		
	} 

}

