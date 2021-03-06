/**
 * Title: StarCombat galactic force
 * Author: Jujube
 * Version: 0.1.0
 * Cophright: Jujube@2021
 */

//includes
#include <gb/gb.h>
#include <gb/console.h>
#include <gb/drawing.h>
#include <stdio.h>

//imports
#include "../projects/StarCombat/Characters/flight.c"
#include "../projects/StarCombat/Characters/enemy.c"
#include "../projects/StarCombat/Characters/fire.c"

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

int enemy[2];
const int initialX = 80;
const int initialY = 120;
int cntrl, firePositionX, firePositionY, enemyPosX, enemyPosY, enemyMinusX, enemyMinusY, lives;

struct alien {
	int posicionx, posiciony, visible, class;
};

struct alien aliens[23];

struct starShip {
	int posicionx, posiciony, visible, class, fired;
} player;

void main() {
	/*
	for(int i=0;i<23;i++){
		aliens[i].posiciony=0;
		aliens[i].posicionx=0;
		aliens[i].visible=1;
	}*/
	init();
	//struct starship player;
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

void setSprites(){
	int i;

	// Load the the 'sprites' tiles into sprite memory
	set_sprite_data(0, 0, flight);
	set_sprite_data(1, 1, enemyTile);
	set_sprite_data(2, 2, fire);
	set_sprite_data(1, 3, enemyTile);

	// Set the first movable sprite (0) to be the first tile in the sprite memory (0)
	//player
	set_sprite_tile(0,0);
	
	//lives
	for(i=1; i<4; i++){
		set_sprite_tile(i,0);
	}
	
	//enemies
	for(i=10; i<40; i++){//40
		set_sprite_tile(i,1);
	}

	//fire
	set_sprite_tile(8,2);
}

void firstLevel(){
	plot_background_image(firstLevelBackground_tile_data,firstLevelBackground_map_data);
	player.posicionx = initialX;
	player.posiciony = initialY;
	player.visible = 0;
	player.class = 0;
	player.fired = 0;

	enemy[0] = 100;
	enemy[1] = 70; 
	setSprites();
}

void updateSwitches() {
	HIDE_WIN;
	SHOW_SPRITES;
	SHOW_BKG;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void checkInput() {
	// START
    if (joypad() & J_START) {
		lives=3;
		firstLevel();
		cntrl=0;
    }

	// B
    if (joypad() & J_B) {
		if(player.fired==0){
			firePositionX = player.posicionx;
			firePositionY = player.posiciony-8;
			move_sprite(8, firePositionX, firePositionY);
			player.fired=1;
		}
    }
	
	// LEFT
	if (joypad() & J_LEFT){
		if (player.posicionx>9){
			player.posicionx--;
		}
	}	
	
	// RIGHT
	if (joypad() & J_RIGHT & player.posicionx<160){
		player.posicionx++;
	}
	
	// Move the sprite in the first movable sprite list (0)
	//  the the position of X (player.posicionx) and y (player.posiciony)
	move_sprite(0, player.posicionx, player.posiciony);
/*	
	if(player.fired==1){
		//fire velocity
		for(int fireVelocity = 0;fireVelocity<4;fireVelocity++){
			firePositionY--;
		}
		
		move_sprite(8, firePositionX, firePositionY);

		//the fire position it's screen off then hidden rocket sprite
		if(firePositionY<-10){
			hide_sprite(8);
			player.fired=0;
		}
	}
*/

	//enemy move
	
	enemyMinusY=0;
	enemyMinusX=0;
	int alienVectorPosition=0;
	for(int i=10 ; i<33 ; i++){//34
		enemyMinusY=enemyMinusY+10;
		enemyPosX = enemy[0];
		enemyPosY = enemy[1];
		alienVectorPosition=i-10;

		aliens[alienVectorPosition].posicionx = enemyPosX-enemyMinusX;
		aliens[alienVectorPosition].posiciony = enemyPosY-enemyMinusY;

		move_sprite(i, aliens[i-10].posicionx, enemyPosY-enemyMinusY);

		if(enemyMinusY==40){
			enemyMinusY=0;
			enemyMinusX= enemyMinusX+15;
		}
	}
	/*

	if(cntrl == 0){
		enemy[0]--;
		if(enemy[0]==90){
			cntrl = 1;
		}
	}else {
		if(cntrl == 1){
			enemy[0]++;
			if(enemy[0]==150){
				cntrl = 0;
				enemy[1]++;
				enemy[1]++;enemy[1]++;enemy[1]++;enemy[1]++;enemy[1]++;enemy[1]++;
				enemy[1]++;enemy[1]++;enemy[1]++;enemy[1]++;enemy[1]++;enemy[1]++;
			}
		}
	}

	//lives

	if(lives>2){move_sprite(1, 130, 145);}
	if(lives>1){move_sprite(2, 140, 145);}
	if(lives>0){move_sprite(3, 150, 145);}

	if(collisionCheck(player.posicionx, player.posiciony, 8, 8, enemy[0], enemy[1], 8, 8) == 1) {
		lives--;
		player.posicionx = initialX;
		player.posiciony = initialY;

		enemy[0] = 100;
		enemy[1] = 70;

		move_sprite(0, player.posicionx, player.posiciony);

		if(lives<3){hide_sprite(1);}
		if(lives<2){hide_sprite(2);}
		if(lives<1){hide_sprite(3);}
		
		if(lives==0){
			printf("game over");
		}
		delay(2000);
	} */

/*
	//it's end of the screen?
	for(int i=0;i<24;i++){
		if(aliens[i].posiciony<=10){
			printf("has llegado a final de pantallaaaaa\n");
			printf("%d\n",aliens[i].posiciony);
			printf("%d\n",i);
			delay(500);
		}
	}*/
}